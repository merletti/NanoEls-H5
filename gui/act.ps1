param([string]$actions="",[string]$out="gui/act.png",[int]$wait=350,[string]$hide="")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class AC1 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr a, int x,int y,int w,int ht,uint f);
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
$h = [AC1]::Find("Nextion Editor")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
if($hide -ne ''){
  $hh = [AC1]::Find($hide)
  if($hh -ne [IntPtr]::Zero){ [AC1]::ShowWindow($hh, 6) | Out-Null; "minimizzato: $hide" }
}
[AC1]::ShowWindow($h, 3) | Out-Null
[AC1]::BringWindowToTop($h) | Out-Null
[AC1]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 500
if([AC1]::Find("Nextion Editor") -ne [IntPtr]::Zero){
  Start-Sleep -Milliseconds 300
}
function Click($x,$y){
  [AC1]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 110
  [AC1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [AC1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250
}
foreach($a in ($actions -split ';')){
  $t = $a.Trim()
  if($t -eq ''){ continue }
  $p = $t -split '\s+',2
  switch($p[0]){
    'click' { $xy = $p[1] -split '\s+'; Click ([int]$xy[0]) ([int]$xy[1]); "click $($xy[0]),$($xy[1])" }
    'dclick' {
      $xy = $p[1] -split '\s+'
      Click ([int]$xy[0]) ([int]$xy[1])
      [AC1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
      [AC1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250
      "dclick $($xy[0]),$($xy[1])"
    }
    'drag' {
      $xy = $p[1] -split '\s+'
      $x1=[int]$xy[0]; $y1=[int]$xy[1]; $x2=[int]$xy[2]; $y2=[int]$xy[3]
      [AC1]::SetCursorPos($x1,$y1) | Out-Null; Start-Sleep -Milliseconds 150
      [AC1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 120
      for($i=1; $i -le 20; $i++){
        [AC1]::SetCursorPos([int]($x1+($x2-$x1)*$i/20), [int]($y1+($y2-$y1)*$i/20)) | Out-Null
        Start-Sleep -Milliseconds 40
      }
      [AC1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 300
      "drag $x1,$y1 -> $x2,$y2"
    }
    'rclick' {
      $xy = $p[1] -split '\s+'
      [AC1]::SetCursorPos([int]$xy[0],[int]$xy[1]) | Out-Null; Start-Sleep -Milliseconds 120
      [AC1]::mouse_event(0x0008,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 60
      [AC1]::mouse_event(0x0010,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 400
      "rclick $($xy[0]),$($xy[1])"
    }
    'move' {
      $xy = $p[1] -split '\s+'
      [AC1]::SetCursorPos([int]$xy[0],[int]$xy[1]) | Out-Null
      "move $($xy[0]),$($xy[1])"
    }
    'key' { [System.Windows.Forms.SendKeys]::SendWait($p[1]); Start-Sleep -Milliseconds 300; "key $($p[1])" }
    'type' { [System.Windows.Forms.SendKeys]::SendWait($p[1]); Start-Sleep -Milliseconds 250; "type $($p[1])" }
    'paste' { Set-Clipboard -Value $p[1]; Start-Sleep -Milliseconds 200; [System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 350; "paste" }
    'wait' { Start-Sleep -Milliseconds ([int]$p[1]); "wait $($p[1])" }
    'wheel' {
      $xy = $p[1] -split '\s+'
      [AC1]::SetCursorPos([int]$xy[0],[int]$xy[1]) | Out-Null; Start-Sleep -Milliseconds 120
      $n = [int]$xy[2]
      for($i=0; $i -lt [Math]::Abs($n); $i++){
        [AC1]::mouse_event(0x0800,0,0,($(if($n -lt 0){-120}else{120})),[UIntPtr]::Zero); Start-Sleep -Milliseconds 120
      }
      "wheel $($xy[0]),$($xy[1]) $n"
    }
    default { "IGNORO: $t" }
  }
  Start-Sleep -Milliseconds $wait
}
Start-Sleep -Milliseconds 300
$b = [System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp = New-Object System.Drawing.Bitmap($b.Width, $b.Height)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($b.Left, $b.Top, 0, 0, $bmp.Size)
$g.Dispose()
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"shot $out"
