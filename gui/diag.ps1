param([string]$actions = "", [string]$out = "gui/diag.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class MA3 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern IntPtr GetFocus();
 [DllImport("user32.dll")] public static extern IntPtr SetFocus(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetParent(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint f);
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(object p);
 [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
 [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
 [DllImport("user32.dll")] public static extern IntPtr GetGUIThreadInfo(uint idThread, ref GUITHREADINFO info);
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
 [StructLayout(LayoutKind.Sequential)]
 public struct GUITHREADINFO {
   public int cbSize; public uint flags; public IntPtr hwndActive; public IntPtr hwndFocus;
   public IntPtr hwndCapture; public IntPtr hwndMenuOwner; public IntPtr hwndMoveSize;
   public IntPtr hwndCaret; public RECT rcCaret;
 }
 [StructLayout(LayoutKind.Sequential)]
 public struct RECT { public int L, T, R, B; }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$qw = [MA3]::FindByTitle("Qoder")
foreach($w in $qw){ $h = [long]($w -split '\|')[0]; [MA3]::ShowWindow([IntPtr]$h, 6) | Out-Null }
Start-Sleep -Milliseconds 800

function ClickAt($x,$y){
  [MA3]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [MA3]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [MA3]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250
}
foreach ($a in ($actions -split ';')) {
  $a = $a.Trim(); if ($a -eq '') { continue }
  $p = $a -split ','
  switch ($p[0]) {
    'click' { ClickAt ([int]$p[1]) ([int]$p[2]) }
    'dclick' {
      [MA3]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null; Start-Sleep -Milliseconds 100
      [MA3]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 30
      [MA3]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 60
      [MA3]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 30
      [MA3]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250
    }
    'key'   { [System.Windows.Forms.SendKeys]::SendWait($p[1]); Start-Sleep -Milliseconds 200 }
    'type'  { [System.Windows.Forms.SendKeys]::SendWait($a.Substring(5)); Start-Sleep -Milliseconds 200 }
    'paste' { Set-Clipboard -Value $a.Substring(6); Start-Sleep -Milliseconds 150; [System.Windows.Forms.SendKeys]::SendWait('^a'); Start-Sleep -Milliseconds 120; [System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 250 }
    'move'  { [MA3]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null }
    'wheel' { [MA3]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null; for($i=0;$i -lt [int]$p[4];$i++){ [MA3]::mouse_event(0x0800,0,0,[int]$p[3],[UIntPtr]::Zero); Start-Sleep -Milliseconds 60 } }
    'drag'  { [MA3]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null; Start-Sleep -Milliseconds 150; [MA3]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 150; [MA3]::SetCursorPos([int]$p[3],[int]$p[4]) | Out-Null; Start-Sleep -Milliseconds 150; [MA3]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250 }
    'wait'  { Start-Sleep -Milliseconds ([int]$p[1]) }
  }
  $fg = [MA3]::GetForegroundWindow()
  $sb = New-Object System.Text.StringBuilder 256
  [MA3]::GetWindowText($fg, $sb, 256) | Out-Null
  $fgpid = 0
  $fgtid = [MA3]::GetWindowThreadProcessId($fg, [ref]$fgpid)
  $cur = [MA3]::GetCurrentThreadId()
  $attached = [MA3]::AttachThreadInput($cur, $fgtid, $true)
  $gi = New-Object MA3+GUITHREADINFO
  $gi.cbSize = [System.Runtime.InteropServices.Marshal]::SizeOf($gi)
  $got = [MA3]::GetGUIThreadInfo($fgtid, [ref]$gi)
  $attach2 = [MA3]::AttachThreadInput($cur, $fgtid, $false)
  $foc = $gi.hwndFocus
  $fsb = New-Object System.Text.StringBuilder 256
  $ftit = ""
  if($foc -ne [IntPtr]::Zero){ [MA3]::GetWindowText($foc, $fsb, 256) | Out-Null; $ftit = $fsb.ToString() }
  Write-Output ("after '{0}': fg='{1}' pid={2} tid={3} curTid={4} focusHwnd={5} focusTitle='{6}' attach={7} gui={8}" -f $a, $sb.ToString(), $fgpid, $fgtid, $cur, $foc, $ftit, $attached, $got)
}
$vs = [System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp = New-Object System.Drawing.Bitmap($vs.Width, $vs.Height)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left, $vs.Top, 0, 0, $bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
$qw = [MA3]::FindByTitle("Qoder")
foreach($w in $qw){ $h = [long]($w -split '\|')[0]; [MA3]::ShowWindow([IntPtr]$h, 9) | Out-Null }
"done"
