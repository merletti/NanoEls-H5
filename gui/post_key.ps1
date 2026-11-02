param([int]$x=0,[int]$y=0,[int]$vk=13,[string]$out="gui/key.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class PK {
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern IntPtr ChildWindowFromPointEx(IntPtr h, POINT p, uint f);
 [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
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
 public static string Key(int sx,int sy,int vk){
   var sp=new POINT(); sp.X=sx; sp.Y=sy;
   IntPtr h=Deepest(WindowFromPoint(sp),sp);
   IntPtr lp=(IntPtr)(1 | (vk<<16));
   PostMessageW(h,0x0100,(IntPtr)vk,lp);       // WM_KEYDOWN
   System.Threading.Thread.Sleep(80);
   PostMessageW(h,0x0101,(IntPtr)vk,(IntPtr)(0xC0000001)); // WM_KEYUP
   System.Threading.Thread.Sleep(80);
   PostMessageW(h,0x0102,(IntPtr)13,IntPtr.Zero); // WM_CHAR CR
   return "key vk="+vk+" to "+h;
 }
}
"@
$q=[PK]::Titled("Qoder")
$e=[PK]::Titled("Nextion Editor")
foreach($h in $q){ [PK]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 500
if($e.Count -gt 0){ [PK]::ShowWindow($e[0],9) | Out-Null }
Start-Sleep -Milliseconds 300
[PK]::Key($x,$y,$vk)
Start-Sleep -Milliseconds 1500
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
foreach($h in $q){ [PK]::ShowWindow($h,9) | Out-Null }
"shot $out"
