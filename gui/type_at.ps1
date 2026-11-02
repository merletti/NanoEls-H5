param([int]$x=0,[int]$y=0,[string]$text="",[switch]$enter,[string]$out="gui/typeat.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class TA {
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern IntPtr ChildWindowFromPointEx(IntPtr h, POINT p, uint f);
 [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll")] public static extern IntPtr SendMessageW(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 public static List<IntPtr> Titled(string prefix){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(300); GetWindowText(h,sb,300);
     if(sb.ToString().StartsWith(prefix)) r.Add(h);
     return true;
   }, IntPtr.Zero);
   return r;
 }
 public static IntPtr Deepest(IntPtr h, POINT sp){
   var p=sp; ScreenToClient(h, ref p);
   IntPtr child=ChildWindowFromPointEx(h,p,1);
   while(child!=IntPtr.Zero){
     var q=p; ScreenToClient(child, ref q);
     var nxt=ChildWindowFromPointEx(child,q,1);
     if(nxt==IntPtr.Zero || nxt==child) break;
     h=child; child=nxt;
   }
   return h;
 }
 public static string ClickAt(int sx,int sy){
   var sp=new POINT(); sp.X=sx; sp.Y=sy;
   SetCursorPos(sx,sy);
   IntPtr h=Deepest(WindowFromPoint(sp),sp);
   var cp=sp; ScreenToClient(h,ref cp);
   IntPtr lp=(IntPtr)((cp.Y<<16)|(cp.X & 0xFFFF));
   PostMessageW(h,0x0200,IntPtr.Zero,lp);
   System.Threading.Thread.Sleep(60);
   PostMessageW(h,0x0201,(IntPtr)1,lp);
   System.Threading.Thread.Sleep(60);
   PostMessageW(h,0x0202,IntPtr.Zero,lp);
   var c=new StringBuilder(100); GetClassName(h,c,100);
   return "click hwnd="+h+" class='"+c+"'";
 }
 public static string TypeAt(int sx,int sy,string text){
   var sp=new POINT(); sp.X=sx; sp.Y=sy;
   IntPtr h=Deepest(WindowFromPoint(sp),sp);
   var c=new StringBuilder(100); GetClassName(h,c,100);
   if(c.ToString()!="Edit") return "not an Edit: '"+c+"'";
   SendMessageW(h,0x00B1,(IntPtr)0,(IntPtr)(-1));   // EM_SETSEL select all
   System.Threading.Thread.Sleep(80);
   foreach(char ch in text){
     SendMessageW(h,0x0102,(IntPtr)ch,IntPtr.Zero); // WM_CHAR
     System.Threading.Thread.Sleep(30);
   }
   return "typed into "+h;
 }
}
"@
$q=[TA]::Titled("Qoder")
foreach($h in $q){ [TA]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 500
if($x -ne 0 -or $y -ne 0){ [TA]::ClickAt($x,$y) | Out-Null; Start-Sleep -Milliseconds 250 }
if($text -ne ""){ [TA]::TypeAt($x,$y,$text) }
if($enter){ [TA]::ClickAt($x,$y) | Out-Null; Start-Sleep -Milliseconds 150; [TA]::ClickAt($x,$y) | Out-Null }
Start-Sleep -Milliseconds 500
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
foreach($h in $q){ [TA]::ShowWindow($h,9) | Out-Null }
"shot $out"
