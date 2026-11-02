param([int]$x=1133,[int]$y=232,[string]$out="gui/msgshot.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class CM {
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern IntPtr PostMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
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
}
"@
foreach($h in [CM]::All("Qoder")){ [CM]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 700
foreach($h in [CM]::All("Nextion Editor")){ [CM]::ShowWindow($h,3) | Out-Null; [CM]::SetForegroundWindow($h) | Out-Null }
Start-Sleep -Milliseconds 900
$pt = New-Object CM+POINT; $pt.X=$x; $pt.Y=$y
$t = [CM]::WindowFromPoint($pt)
$c = New-Object System.Text.StringBuilder 256; [CM]::GetClassName($t,$c,256) | Out-Null
$tt = New-Object System.Text.StringBuilder 256; [CM]::GetWindowText($t,$tt,256) | Out-Null
"target=$t class=$c text=$tt"
$cp = New-Object CM+POINT; $cp.X=$x; $cp.Y=$y
[CM]::ScreenToClient($t,[ref]$cp) | Out-Null
"client=$($cp.X),$($cp.Y)"
$lp = [IntPtr](($cp.Y -shl 16) -bor ($cp.X -band 0xFFFF))
[CM]::PostMessage($t,0x0200,[IntPtr]::Zero,$lp) | Out-Null
[CM]::PostMessage($t,0x0201,[IntPtr]1,$lp) | Out-Null
Start-Sleep -Milliseconds 100
[CM]::PostMessage($t,0x0202,[IntPtr]::Zero,$lp) | Out-Null
Start-Sleep -Milliseconds 800
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
foreach($h in [CM]::All("Qoder")){ [CM]::ShowWindow($h,9) | Out-Null }
"shot $out"
