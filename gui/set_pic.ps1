param([string]$value="48",[int]$x=1183,[int]$y=678,[string]$out="gui/setpic.png")
Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class SP4 {
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
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
 public static string Text(IntPtr h){
   var sb=new StringBuilder(256); SendMessageS(h,0x000D,(IntPtr)256,sb); return sb.ToString();
 }
 public static void Click(int x,int y,int sx,int sy){
   var d=new INPUT[1]; d[0].type=0;
   d[0].mi.dx=(int)System.Math.Round(x*65535.0/(sx-1));
   d[0].mi.dy=(int)System.Math.Round(y*65535.0/(sy-1));
   d[0].mi.dwFlags=0x8001; SendInput(1,d,Marshal.SizeOf(typeof(INPUT)));
   var dn=new INPUT[1]; dn[0].type=0;
   dn[0].mi.dx=d[0].mi.dx; dn[0].mi.dy=d[0].mi.dy;
   dn[0].mi.dwFlags=0x0002; SendInput(1,dn,Marshal.SizeOf(typeof(INPUT)));
   var u=new INPUT[1]; u[0].type=0;
   u[0].mi.dx=d[0].mi.dx; u[0].mi.dy=d[0].mi.dy;
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
$ed = [SP4]::Find("Nextion Editor(C:")
if($ed -eq [IntPtr]::Zero){ "editor non trovato"; exit 1 }
[SP4]::ShowWindow($ed,3) | Out-Null
[SP4]::SetForegroundWindow($ed) | Out-Null
Start-Sleep -Milliseconds 700
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
[SP4]::Click($x,$y,$vs.Width,$vs.Height)
Start-Sleep -Milliseconds 700
$p = New-Object SP4+POINT; $p.X=$x; $p.Y=$y
$child = [SP4]::WindowFromPoint($p)
$sb = New-Object System.Text.StringBuilder 256
[SP4]::GetClassName($child,$sb,256) | Out-Null
Write-Host ("target hwnd={0} class={1} text='{2}'" -f $child, $sb.ToString(), [SP4]::Text($child))
[SP4]::SendMessage($child,0x00B1,[IntPtr]0,[IntPtr](-1)) | Out-Null
Start-Sleep -Milliseconds 200
$sel = [SP4]::SendMessage($child,0x00B0,[IntPtr]0,[IntPtr]0)
Write-Host ("selsel: " + $sel)
foreach($ch in $value.ToCharArray()){
  [SP4]::PostMessage($child,0x0102,[IntPtr][int][char]$ch,[IntPtr]1) | Out-Null
  Start-Sleep -Milliseconds 90
}
Start-Sleep -Milliseconds 300
Write-Host ("text after type='" + [SP4]::Text($child) + "'")
[System.Windows.Forms.SendKeys]::SendWait("{ENTER}")
Start-Sleep -Milliseconds 1200
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
"set pic $value -> $out"
