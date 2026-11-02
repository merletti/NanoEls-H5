param([string]$seq="")
# seq: "sx,sy;..." click each point on the deepest child window
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class PC {
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern IntPtr GetParent(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr ChildWindowFromPointEx(IntPtr h, POINT p, uint f);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool f);
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
 public static List<IntPtr> Titled(string prefix){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(300); GetWindowText(h,sb,300);
     if(sb.ToString().StartsWith(prefix)) r.Add(h);
     return true;
   }, IntPtr.Zero);
   return r;
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
 public static string HoverAt(int sx,int sy){
   var sp=new POINT(); sp.X=sx; sp.Y=sy;
   SetCursorPos(sx,sy);
   IntPtr h=Deepest(WindowFromPoint(sp),sp);
   var cp=sp; ScreenToClient(h,ref cp);
   IntPtr lp=(IntPtr)((cp.Y<<16)|(cp.X & 0xFFFF));
   PostMessageW(h,0x0200,IntPtr.Zero,lp);
   return "hover hwnd="+h+" client("+cp.X+","+cp.Y+")";
 }
 public static string ClickAt(int sx,int sy,bool dbl){
   var sp=new POINT(); sp.X=sx; sp.Y=sy;
   SetCursorPos(sx,sy);
   IntPtr h=WindowFromPoint(sp);
   h=Deepest(h,sp);
   var cp=sp; ScreenToClient(h,ref cp);
   IntPtr lp=(IntPtr)((cp.Y<<16)|(cp.X & 0xFFFF));
   var sb=new StringBuilder(200); GetWindowText(h,sb,200);
   PostMessageW(h,0x0200,IntPtr.Zero,lp);
   System.Threading.Thread.Sleep(60);
   PostMessageW(h,0x0201,(IntPtr)1,lp);
   System.Threading.Thread.Sleep(40);
   PostMessageW(h,0x0202,IntPtr.Zero,lp);
   if(dbl){
     System.Threading.Thread.Sleep(120);
     PostMessageW(h,0x0203,(IntPtr)1,lp);   // WM_LBUTTONDBLCLK
     System.Threading.Thread.Sleep(40);
     PostMessageW(h,0x0202,IntPtr.Zero,lp);
   }
   return "clicked hwnd="+h+" '"+sb.ToString()+"' at client("+cp.X+","+cp.Y+")"+(dbl?" DOUBLE":"");
 }
}
"@
 $q=[PC]::Titled("Qoder")
foreach($h in $q){ [PC]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 600
$ed=[PC]::Titled("Nextion Editor")
$main=$null
foreach($h in $ed){
  $sb=New-Object System.Text.StringBuilder 300
  [void][PC]::GetWindowText($h,$sb,300)
  if($sb.ToString() -like "*.HMI*"){ $main=$h }
}
if($main -eq $null -and $ed.Count -gt 0){ $main=$ed[0] }
if($main -ne $null){ [PC]::Activate($main) }
Start-Sleep -Milliseconds 500
foreach($s in ($seq -split ';')){
  $s=$s.Trim(); if($s -eq ''){continue}
  $dbl=$false; $hov=$false
  if($s -like 'dbl *'){ $dbl=$true; $s=$s.Substring(4).Trim() }
  if($s -like 'hover *'){ $hov=$true; $s=$s.Substring(6).Trim() }
  $p=$s -split ','
  if($hov){ [PC]::HoverAt([int]$p[0],[int]$p[1]) } else { [PC]::ClickAt([int]$p[0],[int]$p[1],$dbl) }
  Start-Sleep -Milliseconds 500
}
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) "gui/pm2.png"),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
foreach($h in $q){ [PC]::ShowWindow($h,9) | Out-Null }
"shot gui/pm2.png"
