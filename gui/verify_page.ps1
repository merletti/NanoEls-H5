param([string]$downs = "0", [string]$out = "gui/ver.png")
Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class VR {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static IntPtr Find(string p){ IntPtr r=IntPtr.Zero; EnumWindows(delegate(IntPtr h, IntPtr l){ if(r==IntPtr.Zero&&IsWindowVisible(h)){ var sb=new StringBuilder(256); GetWindowText(h,sb,256); if(sb.ToString().StartsWith(p)){ r=h; return false; } } return true; }, IntPtr.Zero); return r; }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$h = [VR]::Find("Nextion Editor(C:")
[VR]::ShowWindow($h,3) | Out-Null
[VR]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 600
function Click($x,$y){
  [VR]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [VR]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [VR]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 220
}
[VR]::SetCursorPos(1110,300) | Out-Null
for($k = 0; $k -lt 12; $k++){ [VR]::mouse_event(0x0800,0,0,120,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40 }
Start-Sleep -Milliseconds 300
Click 1100 199
Start-Sleep -Milliseconds 400
for($k = 0; $k -lt [int]$downs; $k++){ [System.Windows.Forms.SendKeys]::SendWait('{DOWN}'); Start-Sleep -Milliseconds 180 }
Start-Sleep -Milliseconds 500
Click 764 772
Start-Sleep -Milliseconds 400
$bmp = New-Object System.Drawing.Bitmap(720, 230)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(585, 750, 0, 0, (New-Object System.Drawing.Size(470, 220)))
$g.CopyFromScreen(245, 180, 480, 0, (New-Object System.Drawing.Size(240, 55)))
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"done"
