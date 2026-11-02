Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class SV1 {
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
$h = [SV1]::Find("Nextion Editor(C:")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
[SV1]::ShowWindow($h, 3) | Out-Null
[SV1]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 900
[System.Windows.Forms.SendKeys]::SendWait('^s')
Start-Sleep -Milliseconds 2500
$bmp = New-Object System.Drawing.Bitmap(900, 60)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(900, 60)))
$bmp.Save((Join-Path (Get-Location) "gui/save1.png"), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"saved"
