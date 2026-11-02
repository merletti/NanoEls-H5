param([string]$path = "", [string]$out = "gui/pick.png")
Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class PK {
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static IntPtr Dialog(){
   IntPtr r=IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(r==IntPtr.Zero && IsWindowVisible(h)){
       var c=new StringBuilder(64); GetClassName(h,c,64);
       var t=new StringBuilder(256); GetWindowText(h,t,256);
       var s=t.ToString();
       if(c.ToString()=="#32770" && (s.StartsWith("Apri")||s.StartsWith("Open"))){ r=h; return false; }
     }
     return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$h = [PK]::Dialog()
if($h -eq [IntPtr]::Zero){ "nessun dialogo"; exit 1 }
[PK]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 400
Set-Clipboard -Value $path
Start-Sleep -Milliseconds 250
[System.Windows.Forms.SendKeys]::SendWait('^v')
Start-Sleep -Milliseconds 400
[System.Windows.Forms.SendKeys]::SendWait('{ENTER}')
Start-Sleep -Milliseconds 1500
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
"picked -> $out"
