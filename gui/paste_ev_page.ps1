param([int]$idx = 21)
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class PEV {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static IntPtr Find(string prefix){
   IntPtr res = IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(res == IntPtr.Zero && IsWindowVisible(h)){
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

$h = [PEV]::Find("Nextion Editor(C:")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
[PEV]::ShowWindow($h, 3) | Out-Null
[PEV]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 700

function Click($x,$y){
  [PEV]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [PEV]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [PEV]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 220
}
function PasteText($file){
  $txt = [System.IO.File]::ReadAllText($file).TrimEnd()
  Set-Clipboard -Value $txt
  Start-Sleep -Milliseconds 250
  [System.Windows.Forms.SendKeys]::SendWait('^a'); Start-Sleep -Milliseconds 150
  [System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 500
}

$base = Join-Path (Get-Location) "gui/ev"
# Preinitialize: svuota
Click 677 753; Start-Sleep -Milliseconds 350
Click 860 890; Start-Sleep -Milliseconds 200
[System.Windows.Forms.SendKeys]::SendWait('^a'); Start-Sleep -Milliseconds 150
[System.Windows.Forms.SendKeys]::SendWait('{DEL}'); Start-Sleep -Milliseconds 300
# Postinitialize
Click 766 753; Start-Sleep -Milliseconds 350
Click 860 890; Start-Sleep -Milliseconds 200
PasteText (Join-Path $base ("{0}_post.txt" -f $idx))
# Touch Press
Click 847 753; Start-Sleep -Milliseconds 350
Click 860 890; Start-Sleep -Milliseconds 200
PasteText (Join-Path $base ("{0}_touch.txt" -f $idx))
# Touch Release
Click 927 753; Start-Sleep -Milliseconds 350
Click 860 890; Start-Sleep -Milliseconds 200
PasteText (Join-Path $base ("{0}_release.txt" -f $idx))

Start-Sleep -Milliseconds 400
$bmp = New-Object System.Drawing.Bitmap(760, 260)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(585, 750, 0, 0, (New-Object System.Drawing.Size(560, 250)))
$bmp.Save((Join-Path (Get-Location) ("gui/evok4_{0}.png" -f $idx)), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"done"
