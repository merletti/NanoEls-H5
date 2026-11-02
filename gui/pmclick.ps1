param([int]$sx=50,[int]$sy=37,[string]$out="gui/pm_click.png")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class PM {
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern bool ScreenToClient(IntPtr h, ref POINT p);
 [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 public static IntPtr FindByTitle(string prefix){
   IntPtr found=IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(512); GetWindowText(h,sb,512);
     if(found==IntPtr.Zero && sb.ToString().StartsWith(prefix)) found=h;
     return true;
   }, IntPtr.Zero);
   return found;
 }
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 public static void Click(IntPtr h,int sx,int sy){
   var p=new POINT(); p.X=sx; p.Y=sy;
   ScreenToClient(h,ref p);
   IntPtr lp=(IntPtr)((p.Y<<16)|(p.X & 0xFFFF));
   SetCursorPos(sx,sy);
   PostMessageW(h,0x0200,IntPtr.Zero,lp);            // WM_MOUSEMOVE
   System.Threading.Thread.Sleep(60);
   PostMessageW(h,0x0201,(IntPtr)1,lp);              // WM_LBUTTONDOWN
   System.Threading.Thread.Sleep(60);
   PostMessageW(h,0x0202,IntPtr.Zero,lp);            // WM_LBUTTONUP
 }
}
"@
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$ed=[PM]::FindByTitle("Nextion Editor")
"editor hwnd=$ed fg=" + [PM]::GetForegroundWindow()
[PM]::SetForegroundWindow($ed) | Out-Null
Start-Sleep -Milliseconds 300
[PM]::Click($ed,$sx,$sy)
Start-Sleep -Milliseconds 600
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
"shot $out"
