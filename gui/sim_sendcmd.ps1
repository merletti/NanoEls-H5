param([string]$cmd="page 21",[string]$out="gui/sim_cmd.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class SC {
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint f);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] i, int size);
 [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
 [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct POINT { public int X; public int Y; }
 public static List<IntPtr> All(string prefix){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(512); GetWindowText(h,sb,512);
     if(sb.ToString().StartsWith(prefix)) r.Add(h);
     return true;
   }, IntPtr.Zero);
   return r;
 }
 public static void Mouse(uint flags,int x,int y,int sx,int sy){
   var a=new INPUT[1]; a[0].type=0;
   a[0].mi.dx=(int)Math.Round(x*65535.0/(sx-1)); a[0].mi.dy=(int)Math.Round(y*65535.0/(sy-1));
   a[0].mi.dwFlags=flags;
   SendInput(1,a,Marshal.SizeOf(typeof(INPUT)));
 }
}
"@
foreach($h in [SC]::All("Qoder")){ [SC]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 600
foreach($h in [SC]::All("Nextion Editor")){ [SC]::ShowWindow($h,3) | Out-Null; [SC]::SetForegroundWindow($h) | Out-Null }
Start-Sleep -Milliseconds 800
[SC]::Mouse(0x8001,225,843,1280,1024); Start-Sleep -Milliseconds 120
[SC]::Mouse(0x0002,225,843,1280,1024); Start-Sleep -Milliseconds 60
[SC]::Mouse(0x0004,225,843,1280,1024); Start-Sleep -Milliseconds 500
$pt=New-Object SC+POINT; $pt.X=225; $pt.Y=843
$child=[SC]::WindowFromPoint($pt)
$cn=New-Object System.Text.StringBuilder 256; [SC]::GetClassName($child,$cn,256) | Out-Null
"child=$child class=$cn"
foreach($ch in $cmd.ToCharArray()){
  [SC]::PostMessage($child,0x0102,[IntPtr][int][char]$ch,[IntPtr]1) | Out-Null
  Start-Sleep -Milliseconds 30
}
[SC]::PostMessage($child,0x0100,[IntPtr]13,[IntPtr]1) | Out-Null
Start-Sleep -Milliseconds 60
[SC]::PostMessage($child,0x0101,[IntPtr]13,[IntPtr]0xC0000001) | Out-Null
Start-Sleep -Milliseconds 1500
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
foreach($h in [SC]::All("Qoder")){ [SC]::ShowWindow($h,9) | Out-Null }
"shot $out"
