param([string]$pages="3",[string]$outdir="gui/pages")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class SP3 {
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool f);
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern IntPtr ChildWindowFromPointEx(IntPtr h, POINT p, uint f);
 [DllImport("user32.dll")] public static extern IntPtr SendMessageW(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h,uint m,IntPtr w,IntPtr l);
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct POINT { public int X; public int Y; }
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
     AttachThreadInput(t1,t2,true);
     SetForegroundWindow(h);
     AttachThreadInput(t1,t2,false);
   }
 }
 public static IntPtr Deepest(IntPtr h, POINT screenPt){
   while(true){
     var q=screenPt; ScreenToClient(h, ref q);
     IntPtr c=ChildWindowFromPointEx(h,q,1);
     if(c==IntPtr.Zero || c==h) break;
     h=c;
   }
   return h;
 }
 public static IntPtr InputAt(int sx,int sy){
   var sp=new POINT(); sp.X=sx; sp.Y=sy;
   return Deepest(WindowFromPoint(sp),sp);
 }
}
"@
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
foreach($h in [SP3]::Titled("Qoder")){ [SP3]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 500
# simulator = the Nextion Editor top-level window that is not the HMI editor
$sim=[IntPtr]0
foreach($h in [SP3]::Titled("Nextion Editor")){
  $sb=New-Object System.Text.StringBuilder 400
  [void][SP3]::GetWindowText($h,$sb,400)
  if($sb.ToString() -notlike "*.HMI*"){ $sim=$h }
}
if($sim -eq [IntPtr]0){ "simulator window not found"; exit 1 }
[SP3]::Activate($sim)
Start-Sleep -Milliseconds 700
$child=[SP3]::InputAt(225,843)
"sim=$sim input=$child"
if($child -eq [IntPtr]0){ "input control not found"; exit 1 }
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
foreach($p in ($pages -split ',')){
  $p=$p.Trim(); if($p -eq ''){continue}
  [void][SP3]::SendMessageW($child,0x00B1,[IntPtr]0,[IntPtr](-1))
  [void][SP3]::PostMessageW($child,0x0303,[IntPtr]0,[IntPtr]0)
  Start-Sleep -Milliseconds 100
  $cmd="page $p"
  foreach($ch in $cmd.ToCharArray()){
    [void][SP3]::PostMessageW($child,0x0102,[IntPtr][int][char]$ch,[IntPtr]1)
    Start-Sleep -Milliseconds 15
  }
  [void][SP3]::PostMessageW($child,0x0100,[IntPtr]13,[IntPtr]1)
  Start-Sleep -Milliseconds 50
  [void][SP3]::PostMessageW($child,0x0101,[IntPtr]13,[IntPtr]0xC0000001)
  Start-Sleep -Milliseconds 900
  $bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
  $g=[System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
  $rect=New-Object System.Drawing.Rectangle(240,170,800,480)
  $crop=$bmp.Clone($rect,$bmp.PixelFormat)
  $file="$outdir/page{0:00}.png" -f [int]$p
  $crop.Save((Join-Path (Get-Location) $file),[System.Drawing.Imaging.ImageFormat]::Png)
  $crop.Dispose(); $g.Dispose(); $bmp.Dispose()
  "captured $file"
}
