Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class DG {
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] i, int size);
 [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
 [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
 public static void Abs(int x,int y,int sx,int sy){
   var a=new INPUT[1]; a[0].type=0;
   a[0].mi.dx=(int)Math.Round(x*65535.0/(sx-1));
   a[0].mi.dy=(int)Math.Round(y*65535.0/(sy-1));
   a[0].mi.dwFlags=0x8001;
   SendInput(1,a,Marshal.SizeOf(typeof(INPUT)));
 }
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 public static string Info(IntPtr h){
   var t=new StringBuilder(300); GetWindowText(h,t,300);
   var c=new StringBuilder(300); GetClassName(h,c,300);
   return h+" '"+c+"' '"+t+"'";
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
"virtual screen: L=$($vs.Left) T=$($vs.Top) W=$($vs.Width) H=$($vs.Height)"
[DG]::SetCursorPos(50,37) | Out-Null
Start-Sleep -Milliseconds 200
$p=New-Object DG+POINT
[DG]::GetCursorPos([ref]$p) | Out-Null
"after SetCursorPos(50,37): X=$($p.X) Y=$($p.Y)"
$pt=New-Object DG+POINT; $pt.X=$p.X; $pt.Y=$p.Y
"WindowFromPoint: " + [DG]::Info([DG]::WindowFromPoint($pt))
[DG]::Abs(50,37,$vs.Width,$vs.Height)
Start-Sleep -Milliseconds 200
[DG]::GetCursorPos([ref]$p) | Out-Null
"after Abs(50,37,..): X=$($p.X) Y=$($p.Y)"
$pt.X=$p.X; $pt.Y=$p.Y
"WindowFromPoint: " + [DG]::Info([DG]::WindowFromPoint($pt))
[DG]::Abs(1130,169,$vs.Width,$vs.Height)
Start-Sleep -Milliseconds 200
[DG]::GetCursorPos([ref]$p) | Out-Null
"after Abs(1130,169,..): X=$($p.X) Y=$($p.Y)"
$pt.X=$p.X; $pt.Y=$p.Y
"WindowFromPoint: " + [DG]::Info([DG]::WindowFromPoint($pt))
