param([string]$pairs="223:49,246:50,269:51,314:52,337:53,360:54",[int]$px=1183,[int]$py=678,[string]$out="gui/apply_pics.png")
Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class AP1 {
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode, EntryPoint="SendMessageW")] public static extern IntPtr SendMessageS(IntPtr h, uint m, IntPtr w, StringBuilder l);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] i, int size);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct POINT { public int X; public int Y; }
 [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
 [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
 public static string Text(IntPtr h){ var sb=new StringBuilder(256); SendMessageS(h,0x000D,(IntPtr)256,sb); return sb.ToString(); }
 public static void Click(int x,int y,int sx,int sy){
   var m=new INPUT[1]; m[0].type=0;
   m[0].mi.dx=(int)System.Math.Round(x*65535.0/(sx-1));
   m[0].mi.dy=(int)System.Math.Round(y*65535.0/(sy-1));
   m[0].mi.dwFlags=0x8001; SendInput(1,m,Marshal.SizeOf(typeof(INPUT)));
   var d=new INPUT[1]; d[0].type=0;
   d[0].mi.dx=m[0].mi.dx; d[0].mi.dy=m[0].mi.dy;
   d[0].mi.dwFlags=0x0002; SendInput(1,d,Marshal.SizeOf(typeof(INPUT)));
   var u=new INPUT[1]; u[0].type=0;
   u[0].mi.dx=m[0].mi.dx; u[0].mi.dy=m[0].mi.dy;
   u[0].mi.dwFlags=0x0004; SendInput(1,u,Marshal.SizeOf(typeof(INPUT)));
 }
 public static IntPtr Find(string prefix){
   IntPtr res=IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(res==IntPtr.Zero && IsWindowVisible(h)){
       var sb=new StringBuilder(256); GetWindowText(h,sb,256);
       if(sb.ToString().StartsWith(prefix)){ res=h; return false; }
     }
     return true;
   }, IntPtr.Zero);
   return res;
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$ed = [AP1]::Find("Nextion Editor(C:")
if($ed -eq [IntPtr]::Zero){ "editor non trovato"; exit 1 }
[AP1]::ShowWindow($ed,3) | Out-Null
[AP1]::SetForegroundWindow($ed) | Out-Null
Start-Sleep -Milliseconds 800
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$pt = New-Object AP1+POINT
foreach($pair in ($pairs -split ',')){
  $pp = $pair -split ':'
  $rowY = [int]$pp[0]; $val = $pp[1]
  [AP1]::Click(1120,$rowY,$vs.Width,$vs.Height)
  Start-Sleep -Milliseconds 800
  [AP1]::Click($px,$py,$vs.Width,$vs.Height)
  Start-Sleep -Milliseconds 700
  $pt.X=$px; $pt.Y=$py
  $child = [AP1]::WindowFromPoint($pt)
  if($child -eq [IntPtr]::Zero){ Write-Host "row $rowY : nessun edit"; continue }
  $before = [AP1]::Text($child)
  [AP1]::SendMessage($child,0x00B1,[IntPtr]0,[IntPtr](-1)) | Out-Null
  Start-Sleep -Milliseconds 200
  foreach($ch in $val.ToCharArray()){
    [AP1]::PostMessage($child,0x0102,[IntPtr][int][char]$ch,[IntPtr]1) | Out-Null
    Start-Sleep -Milliseconds 90
  }
  Start-Sleep -Milliseconds 250
  $typed = [AP1]::Text($child)
  [System.Windows.Forms.SendKeys]::SendWait("{ENTER}")
  Start-Sleep -Milliseconds 900
  Write-Host ("row {0}: '{1}' -> '{2}' = {3}" -f $rowY,$before,$typed,$val)
}
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
"done -> $out"
