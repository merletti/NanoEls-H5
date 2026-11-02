param([string]$points="50,37;1130,169")
Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class WA {
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint ga);
 [DllImport("user32.dll")] public static extern int GetWindowTextW(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetClassNameW(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 public static string Info(IntPtr h){
   var t=new StringBuilder(512); GetWindowTextW(h,t,512);
   var c=new StringBuilder(256); GetClassNameW(h,c,256);
   uint pid; GetWindowThreadProcessId(h, out pid);
   return h.ToString()+" class="+c.ToString()+" pid="+pid+" title="+t.ToString();
 }
}
"@
foreach($p in ($points -split ';')){
  $p=$p.Trim(); if($p -eq ''){continue}
  $xy=$p -split ','
  $pt=New-Object WA+POINT
  $pt.X=[int]$xy[0]; $pt.Y=[int]$xy[1]
  $h=[WA]::WindowFromPoint($pt)
  $top=[WA]::GetAncestor($h,2)
  "point $p -> child: " + [WA]::Info($h)
  "point $p -> toplevel: " + [WA]::Info($top)
}
"foreground: " + [WA]::Info([WA]::GetForegroundWindow())
