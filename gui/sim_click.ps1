param([int]$x=904,[int]$y=543,[string]$out="gui/sim_statobtn.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class SC4 {
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool f);
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern IntPtr ChildWindowFromPointEx(IntPtr h, POINT p, uint f);
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
     AttachThreadInput(t1,t2,true); SetForegroundWindow(h); AttachThreadInput(t1,t2,false);
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
 public static string Click(int sx,int sy){
   var sp=new POINT(); sp.X=sx; sp.Y=sy;
   SetCursorPos(sx,sy);
   IntPtr h=Deepest(WindowFromPoint(sp),sp);
   var cp=sp; ScreenToClient(h,ref cp);
   IntPtr lp=(IntPtr)((cp.Y<<16)|(cp.X & 0xFFFF));
   PostMessageW(h,0x0200,IntPtr.Zero,lp);
   System.Threading.Thread.Sleep(80);
   PostMessageW(h,0x0201,(IntPtr)1,lp);
   System.Threading.Thread.Sleep(60);
   PostMessageW(h,0x0202,IntPtr.Zero,lp);
   return "click hwnd="+h+" client("+cp.X+","+cp.Y+")";
 }
}
"@
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
foreach($h in [SC4]::Titled("Qoder")){ [SC4]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 500
$sim=[IntPtr]0
foreach($h in [SC4]::Titled("Nextion Editor")){
  $sb=New-Object System.Text.StringBuilder 400
  [void][SC4]::GetWindowText($h,$sb,400)
  if($sb.ToString() -notlike "*.HMI*"){ $sim=$h }
}
if($sim -eq [IntPtr]0){ "simulator window not found"; exit 1 }
[SC4]::Activate($sim)
Start-Sleep -Milliseconds 700
[SC4]::Click($x,$y)
Start-Sleep -Milliseconds 800
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
"shot $out"
