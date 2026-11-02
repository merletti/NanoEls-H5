param([string]$items = "")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class SM {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static List<string> FindByTitle(string prefix){
   var r = new List<string>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(IsWindowVisible(h)){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       string t = sb.ToString();
       if(t.StartsWith(prefix)) r.Add(h.ToInt64()+"|"+t);
     }
     return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

$qw = [SM]::FindByTitle("Qoder")
foreach($w in $qw){ $h = [long]($w -split '\|')[0]; [SM]::ShowWindow([IntPtr]$h, 6) | Out-Null }
Start-Sleep -Milliseconds 800

$rx = 240; $ry = 174; $rw = 800; $rh = 480

function Grab(){
  $bmp = New-Object System.Drawing.Bitmap($rw, $rh)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen($rx, $ry, 0, 0, (New-Object System.Drawing.Size($rw, $rh)))
  $g.Dispose()
  return $bmp
}
function ImgDiff($a, $b){
  $n = 0
  for($y = 0; $y -lt $rh; $y += 2){
    for($x = 0; $x -lt $rw; $x += 2){
      $ca = $a.GetPixel($x, $y); $cb = $b.GetPixel($x, $y)
      if([Math]::Abs($ca.R - $cb.R) -gt 26 -or [Math]::Abs($ca.G - $cb.G) -gt 26 -or [Math]::Abs($ca.B - $cb.B) -gt 26){ $n++ }
    }
  }
  return $n
}
function ClickAt($x,$y){
  [SM]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [SM]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 60
  [SM]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250
}

function Act(){ ClickAt 600 94; Start-Sleep -Milliseconds 350 }

Act
ClickAt 985 216
Start-Sleep -Milliseconds 900
Act
ClickAt 640 629
Start-Sleep -Milliseconds 700
[SM]::SetCursorPos(1200, 940) | Out-Null
Start-Sleep -Milliseconds 500
$base = Grab
$base.Save((Join-Path (Get-Location) "sim_base.png"), [System.Drawing.Imaging.ImageFormat]::Png)

foreach ($it in ($items -split ';')) {
  $it = $it.Trim(); if ($it -eq '') { continue }
  $p = $it -split ','
  $name = $p[0]; $cx = [int]$p[1]; $cy = [int]$p[2]
  Act
  ClickAt $cx $cy
  Start-Sleep -Milliseconds 900
  [SM]::SetCursorPos(1200, 940) | Out-Null
  Start-Sleep -Milliseconds 250
  $open = Grab
  $open.Save((Join-Path (Get-Location) ("sim_" + $name + "_open.png")), [System.Drawing.Imaging.ImageFormat]::Png)
  $dOpen = ImgDiff $base $open
  Act
  ClickAt 985 216
  Start-Sleep -Milliseconds 900
  [SM]::SetCursorPos(1200, 940) | Out-Null
  Start-Sleep -Milliseconds 250
  $back = Grab
  $back.Save((Join-Path (Get-Location) ("sim_" + $name + "_back.png")), [System.Drawing.Imaging.ImageFormat]::Png)
  $dBack = ImgDiff $base $back
  $ok = if ($dBack -lt 400 -and $dOpen -gt 2000) { "PASS" } else { "FAIL" }
  Write-Output ("{0,-14} open={1,-6} back={2,-6} {3}" -f $name, $dOpen, $dBack, $ok)
  $open.Dispose(); $back.Dispose()
}
$base.Dispose()
foreach($w in $qw){ $h = [long]($w -split '\|')[0]; [SM]::ShowWindow([IntPtr]$h, 9) | Out-Null }
"done"
