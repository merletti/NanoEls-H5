param([string]$out="gui/pagelist_bottom.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class PL {
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool f);
 [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static List<IntPtr> Titled(string prefix){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(300); GetWindowText(h,sb,300);
     if(sb.ToString().StartsWith(prefix)) r.Add(h);
     return true;
   }, IntPtr.Zero);
   return r;
 }
 public static void Activate(IntPtr h){
   ShowWindow(h,3); BringWindowToTop(h);
   if(GetForegroundWindow()!=h){
     uint p0=0; uint t1=GetWindowThreadProcessId(GetForegroundWindow(), out p0);
     uint t2=GetWindowThreadProcessId(h, out p0);
     AttachThreadInput(t1,t2,true); SetForegroundWindow(h); AttachThreadInput(t1,t2,false);
   }
 }
}
"@
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
foreach($h in [PL]::Titled("Qoder")){ [PL]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 500
[PL]::Activate([IntPtr]197842)
Start-Sleep -Milliseconds 500
for($i=0;$i -lt 60;$i++){
  [void][PL]::PostMessageW([IntPtr]721966,0x0115,[IntPtr]1,[IntPtr]0)  # WM_VSCROLL SB_LINEDOWN
  Start-Sleep -Milliseconds 20
}
Start-Sleep -Milliseconds 700
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
"shot $out"
