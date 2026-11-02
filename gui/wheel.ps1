param([int]$x=100,[int]$y=700,[int]$notches=-3,[string]$out="gui/pw.png")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WH1 {
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
Add-Type -AssemblyName System.Drawing
$h = [WH1]::Find("Nextion Editor")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
[WH1]::ShowWindow($h, 3) | Out-Null
[WH1]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 700
[WH1]::SetCursorPos($x,$y) | Out-Null
Start-Sleep -Milliseconds 150
for($i=0; $i -lt [Math]::Abs($notches); $i++){
  [WH1]::mouse_event(0x0800,0,0,($(if($notches -lt 0){-120}else{120})),[UIntPtr]::Zero)
  Start-Sleep -Milliseconds 120
}
Start-Sleep -Milliseconds 500
$r = New-Object WH1+RECT
[WH1]::GetWindowRect($h, [ref]$r) | Out-Null
$w = $r.right - $r.left; $hgt = $r.bottom - $r.top
$bmp = New-Object System.Drawing.Bitmap($w, $hgt)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$hdc = $g.GetHdc()
[WH1]::PrintWindow($h, $hdc, 2) | Out-Null
$g.ReleaseHdc($hdc)
$g.Dispose()
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"shot $out"
