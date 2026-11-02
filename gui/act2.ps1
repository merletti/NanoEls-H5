param([string]$actions = "", [string]$out = "gui/act2.png", [int]$minQoder = 1)
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class MA2 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
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
 public static List<string> Find(uint pid, string prefix){
   var r = new List<string>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     uint p; GetWindowThreadProcessId(h, out p);
     if(p==pid && IsWindowVisible(h)){
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
if($minQoder -eq 1){
  $qw = [MA2]::FindByTitle("Qoder")
  foreach($w in $qw){ $h = [long]($w -split '\|')[0]; [MA2]::ShowWindow([IntPtr]$h, 6) | Out-Null }
  $iw = [MA2]::FindByTitle("screen-it - Esplora file")
  foreach($w in $iw){ $h = [long]($w -split '\|')[0]; [MA2]::ShowWindow([IntPtr]$h, 6) | Out-Null }
  Start-Sleep -Milliseconds 800
}
$nx = Get-Process -Name "Nextion Editor" -ErrorAction SilentlyContinue | Select-Object -First 1
if($nx){
  $ws = [MA2]::Find([uint32]$nx.Id, "Nextion Editor")
  foreach($w in $ws){
    $h = [IntPtr][long](($w -split '\|')[0])
    [MA2]::ShowWindow($h, 3) | Out-Null
    [MA2]::BringWindowToTop($h) | Out-Null
    [MA2]::SetForegroundWindow($h) | Out-Null
  }
  Start-Sleep -Milliseconds 600
}
function ClickAt($x,$y){
  [MA2]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 90
  [MA2]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 30
  [MA2]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 160
}
function K($s){ [System.Windows.Forms.SendKeys]::SendWait($s); Start-Sleep -Milliseconds 120 }
foreach ($a in ($actions -split ';')) {
  $a = $a.Trim(); if ($a -eq '') { continue }
  $p = $a -split ','
  switch ($p[0]) {
    'click' { ClickAt ([int]$p[1]) ([int]$p[2]) }
    'dbl'   { ClickAt ([int]$p[1]) ([int]$p[2]); Start-Sleep -Milliseconds 80; [MA2]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 30; [MA2]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 200 }
    'key'   { K $p[1] }
    'move'  { [MA2]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null }
    'wait'  { Start-Sleep -Milliseconds ([int]$p[1]) }
    'wheel' { [MA2]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null; for($i=0;$i -lt [int]$p[4];$i++){ [MA2]::mouse_event(0x0800,0,0,[int]$p[3],[UIntPtr]::Zero); Start-Sleep -Milliseconds 60 } }
  }
}
$vs = [System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp = New-Object System.Drawing.Bitmap($vs.Width, $vs.Height)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left, $vs.Top, 0, 0, $bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
if($minQoder -eq 1){
  $qw = [MA2]::FindByTitle("Qoder")
  foreach($w in $qw){ $h = [long]($w -split '\|')[0]; [MA2]::ShowWindow([IntPtr]$h, 9) | Out-Null }
}
"done"
