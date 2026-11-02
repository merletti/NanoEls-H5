Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class SI {
 [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
 [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
 [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] i, int size);
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct POINT { public int X; public int Y; }
 public static List<IntPtr> All(string prefix){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(512); GetWindowText(h,sb,512);
     if(sb.ToString().StartsWith(prefix)) r.Add(h);
     return true;
   }, IntPtr.Zero);
   return r;
 }
 public static string MoveAbs(int x,int y,int sx,int sy){
   var a=new INPUT[1];
   a[0].type=0;
   a[0].mi.dx=(int)Math.Round(x*65535.0/(sx-1));
   a[0].mi.dy=(int)Math.Round(y*65535.0/(sy-1));
   a[0].mi.dwFlags=0x8001;
   uint n=SendInput(1,a,Marshal.SizeOf(typeof(INPUT)));
   int err=Marshal.GetLastWin32Error();
   POINT p; GetCursorPos(out p);
   return "SendInput="+n+" err="+err+" cursor="+p.X+","+p.Y;
 }
 public static string Click(int x,int y,int sx,int sy){
   var a=new INPUT[1];
   a[0].type=0; a[0].mi.dx=(int)Math.Round(x*65535.0/(sx-1)); a[0].mi.dy=(int)Math.Round(y*65535.0/(sy-1));
   a[0].mi.dwFlags=0x8001;
   SendInput(1,a,Marshal.SizeOf(typeof(INPUT)));
   var b=new INPUT[6];
   b[0].type=0; b[0].mi.dwFlags=0x0002; b[1].type=0; b[1].mi.dwFlags=0x0004;
   b[2].type=0; b[2].mi.dx=(int)Math.Round(x*65535.0/(sx-1)); b[2].mi.dy=(int)Math.Round(y*65535.0/(sy-1)); b[2].mi.dwFlags=0x8001;
   b[3].type=0; b[3].mi.dwFlags=0x0002;
   b[4].type=0; b[4].mi.dwFlags=0x0004;
   b[5].type=0; b[5].mi.dx=(int)Math.Round(x*65535.0/(sx-1)); b[5].mi.dy=(int)Math.Round(y*65535.0/(sy-1)); b[5].mi.dwFlags=0x8001;
   uint n=SendInput(6,b,Marshal.SizeOf(typeof(INPUT)));
   int err=Marshal.GetLastWin32Error();
   POINT p; GetCursorPos(out p);
   return "SendInput click n="+n+" err="+err+" cursor="+p.X+","+p.Y;
 }
}
"@
"1) test move con Qoder in primo piano: " + [SI]::MoveAbs(600,500,1280,1024)
Start-Sleep -Milliseconds 300
$n=[System.Text.StringBuilder]::new(256)
"2) move a 900,700: " + [SI]::MoveAbs(900,700,1280,1024)
Start-Sleep -Milliseconds 300
foreach($h in [SI]::All("Qoder")){ [SI]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 700
foreach($h in [SI]::All("Nextion Editor")){ [SI]::ShowWindow($h,3) | Out-Null; [SI]::SetForegroundWindow($h) | Out-Null }
Start-Sleep -Milliseconds 1000
$fg=[SI]::GetForegroundWindow(); [SI]::GetWindowText($fg,$n,256) | Out-Null
"3) fg dopo attivazione editor: $fg $($n.ToString())"
"4) click page7: " + [SI]::Click(1133,234,1280,1024)
Start-Sleep -Milliseconds 800
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) 'gui/si_click.png'),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
foreach($h in [SI]::All("Qoder")){ [SI]::ShowWindow($h,9) | Out-Null }
"shot gui/si_click.png"
