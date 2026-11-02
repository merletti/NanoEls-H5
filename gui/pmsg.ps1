param([int]$x=1150,[int]$y=250)
Add-Type @"
using System;using System.Runtime.InteropServices;
public class PM {
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, System.Text.StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, System.Text.StringBuilder s, int n);
 public struct POINT { public int X; public int Y; }
}
"@
$pt = New-Object PM+POINT; $pt.X=$x; $pt.Y=$y
$h = [PM]::WindowFromPoint($pt)
$c = New-Object System.Text.StringBuilder 256; [PM]::GetClassName($h,$c,256) | Out-Null
$t = New-Object System.Text.StringBuilder 256; [PM]::GetWindowText($h,$t,256) | Out-Null
"target hwnd=$h class=$c text=$t"
$cp = New-Object PM+POINT; $cp.X=$x; $cp.Y=$y
[PM]::ScreenToClient($h,[ref]$cp) | Out-Null
"client=$($cp.X),$($cp.Y)"
$lp = [IntPtr](($cp.Y -shl 16) -bor ($cp.X -band 0xFFFF))
[PM]::SendMessage($h,0x0200,[IntPtr]::Zero,$lp) | Out-Null
[PM]::SendMessage($h,0x0201,[IntPtr]1,$lp) | Out-Null
Start-Sleep -Milliseconds 120
[PM]::SendMessage($h,0x0202,[IntPtr]::Zero,$lp) | Out-Null
Start-Sleep -Milliseconds 600
"sent"
