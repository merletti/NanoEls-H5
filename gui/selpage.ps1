param([int]$row=0,[string]$out="gui/sel.png")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class SP1 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static IntPtr Find(string prefix){
   IntPtr res = IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(res == IntPtr.Zero){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       if(sb.ToString().StartsWith(prefix)){ res = h; return false; }
     }
     return true;
   }, IntPtr.Zero);
   return res;
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$h = [SP1]::Find("Nextion Editor")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
[SP1]::ShowWindow($h, 3) | Out-Null
[SP1]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 400
function Click($x,$y){
  [SP1]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 100
  [SP1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [SP1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 220
}
Click 1120 184
Start-Sleep -Milliseconds 250
for($i=0; $i -lt 26; $i++){ [System.Windows.Forms.SendKeys]::SendWait('{UP}'); Start-Sleep -Milliseconds 70 }
for($i=0; $i -lt $row; $i++){ [System.Windows.Forms.SendKeys]::SendWait('{DOWN}'); Start-Sleep -Milliseconds 70 }
Start-Sleep -Milliseconds 500
$b = [System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp = New-Object System.Drawing.Bitmap($b.Width, $b.Height)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($b.Left, $b.Top, 0, 0, $bmp.Size)
$g.Dispose()
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"sel row $row -> $out"
