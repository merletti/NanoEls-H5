param([string]$title="Apri",[string]$keys="",[string]$paste="",[string]$out="gui/dlg.png",[int]$wait=600)
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class DG1 {
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint flags);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [StructLayout(LayoutKind.Sequential)] public struct RECT { public int left, top, right, bottom; }
 public static IntPtr FindByTitle(string t){
   IntPtr res = IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(res == IntPtr.Zero && IsWindowVisible(h)){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       if(sb.ToString() == t){ res = h; return false; }
     }
     return true;
   }, IntPtr.Zero);
   return res;
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$h = [DG1]::FindByTitle($title)
if($h -eq [IntPtr]::Zero){ "ERRORE: finestra '$title' non trovata"; exit 1 }
[DG1]::SetForegroundWindow($h) | Out-Null
[DG1]::ShowWindow($h, 5) | Out-Null
Start-Sleep -Milliseconds 500
if($paste -ne ""){
  Set-Clipboard -Value $paste
  Start-Sleep -Milliseconds 200
  [System.Windows.Forms.SendKeys]::SendWait('^a')
  Start-Sleep -Milliseconds 100
  [System.Windows.Forms.SendKeys]::SendWait('^v')
  Start-Sleep -Milliseconds 400
}
if($keys -ne ""){
  [System.Windows.Forms.SendKeys]::SendWait($keys)
  Start-Sleep -Milliseconds 300
}
Start-Sleep -Milliseconds $wait
$r = New-Object DG1+RECT
[DG1]::GetWindowRect($h, [ref]$r) | Out-Null
$w = $r.right - $r.left; $hgt = $r.bottom - $r.top
"rect $($r.left) $($r.top) $w x $hgt"
if($w -gt 0 -and $hgt -gt 0){
  $bmp = New-Object System.Drawing.Bitmap($w, $hgt)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $hdc = $g.GetHdc()
  [DG1]::PrintWindow($h, $hdc, 0) | Out-Null
  $g.ReleaseHdc($hdc)
  $g.Dispose()
  $bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
  $bmp.Dispose()
  "shot $out"
}
