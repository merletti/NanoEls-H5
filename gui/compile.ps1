Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class CP1 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
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
$h = [CP1]::Find("Nextion Editor(C:")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
[CP1]::ShowWindow($h, 3) | Out-Null
[CP1]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 800
function Click($x,$y){
  [CP1]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [CP1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [CP1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 250
}
function Shot($name){
  $vs = [System.Windows.Forms.SystemInformation]::VirtualScreen
  $bmp = New-Object System.Drawing.Bitmap($vs.Width, $vs.Height)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen($vs.Left, $vs.Top, 0, 0, $bmp.Size)
  $bmp.Save((Join-Path (Get-Location) $name), [System.Drawing.Imaging.ImageFormat]::Png)
  $g.Dispose(); $bmp.Dispose()
}
Click 305 68
Start-Sleep -Milliseconds 2000
Shot "gui/compile1.png"
Start-Sleep -Milliseconds 8000
Shot "gui/compile2.png"
"done"
