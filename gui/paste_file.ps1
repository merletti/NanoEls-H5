param([string]$file, [string]$tab = "touch", [string]$compile = "0")
Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class PF {
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
$h = [PF]::Find("Nextion Editor(C:")
[PF]::ShowWindow($h,3) | Out-Null
[PF]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 500
function Click($x,$y){
  [PF]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [PF]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [PF]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 220
}
if($tab -eq "post"){ Click 764 772 } else { Click 845 772 }
Start-Sleep -Milliseconds 300
Click 860 890
Start-Sleep -Milliseconds 200
$txt = [System.IO.File]::ReadAllText((Join-Path (Get-Location) $file))
Set-Clipboard -Value $txt
Start-Sleep -Milliseconds 250
[System.Windows.Forms.SendKeys]::SendWait('^a'); Start-Sleep -Milliseconds 150
[System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 500
if($compile -eq "1"){
  Click 305 68
  Start-Sleep -Milliseconds 3500
}
$bmp = New-Object System.Drawing.Bitmap(700, 230)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(222, 755, 0, 0, (New-Object System.Drawing.Size(700, 215)))
$bmp.Save((Join-Path (Get-Location) "gui/pf_last.png"), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"done"
