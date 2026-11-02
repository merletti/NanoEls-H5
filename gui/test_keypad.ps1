Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class TK1 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

function Click($x,$y){
  [TK1]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 150
  [TK1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 60
  [TK1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 300
}
function Tap($x,$y){
  [TK1]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 150
  [TK1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 120
  [TK1]::SetCursorPos($x+2,$y+2) | Out-Null; Start-Sleep -Milliseconds 120
  [TK1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 350
}
function Shot($name){
  $bmp = New-Object System.Drawing.Bitmap(1280, 999)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(1280, 999)))
  $bmp.Save((Join-Path (Get-Location) $name), [System.Drawing.Imaging.ImageFormat]::Png)
  $g.Dispose(); $bmp.Dispose()
}
function SendCmd($text){
  Set-Clipboard -Value $text
  Start-Sleep -Milliseconds 150
  [System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 200
  [System.Windows.Forms.SendKeys]::SendWait('{ENTER}'); Start-Sleep -Milliseconds 500
}

Click 340 280
Start-Sleep -Milliseconds 1200
Shot "gui/test1_page1.png"

Tap 550 280
Start-Sleep -Milliseconds 800
Shot "gui/test2_valtap.png"

Click 225 845
Start-Sleep -Milliseconds 300
Click 250 780
Start-Sleep -Milliseconds 300
SendCmd "page 18"
Start-Sleep -Milliseconds 1200
Shot "gui/test3_keypad.png"
"done"
