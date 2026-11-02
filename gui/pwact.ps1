param([string]$actions="",[string]$out="gui/pw.png")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class PA1 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint flags);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [StructLayout(LayoutKind.Sequential)] public struct RECT { public int left, top, right, bottom; }
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
$h = [PA1]::Find("Nextion Editor")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
[PA1]::ShowWindow($h, 3) | Out-Null
[PA1]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 800
function Click($x,$y){
  [PA1]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [PA1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [PA1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250
}
foreach($a in ($actions -split ';')){
  $a=$a.Trim(); if($a -eq ''){ continue }
  $p=$a -split ','
  switch($p[0]){
    'click' { Click ([int]$p[1]) ([int]$p[2]) }
    'rclick' {
      [PA1]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null; Start-Sleep -Milliseconds 150
      [PA1]::mouse_event(0x0008,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 60
      [PA1]::mouse_event(0x0010,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 400
    }
    'wait'  { Start-Sleep -Milliseconds ([int]$p[1]) }
    'key'   { [System.Windows.Forms.SendKeys]::SendWait($p[1]); Start-Sleep -Milliseconds 200 }
    'type'  { [System.Windows.Forms.SendKeys]::SendWait($p[1]); Start-Sleep -Milliseconds 200 }
    'paste' { Set-Clipboard -Value $p[1]; Start-Sleep -Milliseconds 150; [System.Windows.Forms.SendKeys]::SendWait('^a'); Start-Sleep -Milliseconds 100; [System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 300 }
  }
}
Start-Sleep -Milliseconds 500
$r = New-Object PA1+RECT
[PA1]::GetWindowRect($h, [ref]$r) | Out-Null
$w = $r.right - $r.left; $hgt = $r.bottom - $r.top
$bmp = New-Object System.Drawing.Bitmap($w, $hgt)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$hdc = $g.GetHdc()
[PA1]::PrintWindow($h, $hdc, 2) | Out-Null
$g.ReleaseHdc($hdc)
$g.Dispose()
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"shot $out"
