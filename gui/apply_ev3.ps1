param([string]$items = "")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class AE3 {
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

$h = [AE3]::Find("Nextion Editor(C:")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
[AE3]::ShowWindow($h, 3) | Out-Null
[AE3]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 700

function Click($x,$y){
  [AE3]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [AE3]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [AE3]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 220
}
function PasteText($file){
  $txt = [System.IO.File]::ReadAllText($file).TrimEnd()
  Set-Clipboard -Value $txt
  Start-Sleep -Milliseconds 250
  [System.Windows.Forms.SendKeys]::SendWait('^a'); Start-Sleep -Milliseconds 150
  [System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 400
}

$base = Join-Path (Get-Location) "gui/ev"
foreach($item in ($items -split ';')){
  $item = $item.Trim(); if($item -eq ''){ continue }
  $p = $item -split ':'
  $idx = [int]$p[0]; $downs = [int]$p[1]
  "pagina $idx (downs=$downs)"
  for($k = 0; $k -lt 7; $k++){ Click 1271 179; Start-Sleep -Milliseconds 120 }
  Start-Sleep -Milliseconds 400
  Click 1100 199                 # riga 1: page3 (id 1)
  Start-Sleep -Milliseconds 400
  for($k = 0; $k -lt $downs; $k++){
    [System.Windows.Forms.SendKeys]::SendWait('{DOWN}')
    Start-Sleep -Milliseconds 150
  }
  Start-Sleep -Milliseconds 400
  Click 764 772
  Start-Sleep -Milliseconds 250
  Click 860 890
  Start-Sleep -Milliseconds 150
  PasteText (Join-Path $base ("{0}_post.txt" -f $idx))
  Click 845 772
  Start-Sleep -Milliseconds 250
  Click 860 890
  Start-Sleep -Milliseconds 150
  PasteText (Join-Path $base ("{0}_touch.txt" -f $idx))
  Start-Sleep -Milliseconds 300
  $bmp = New-Object System.Drawing.Bitmap(720, 230)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen(585, 750, 0, 0, (New-Object System.Drawing.Size(470, 220)))
  $g.CopyFromScreen(245, 180, 480, 0, (New-Object System.Drawing.Size(240, 55)))
  $bmp.Save((Join-Path (Get-Location) ("gui/evok3_{0}.png" -f $idx)), [System.Drawing.Imaging.ImageFormat]::Png)
  $g.Dispose(); $bmp.Dispose()
}
"done"
