Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class WN2 {
 [DllImport("user32.dll")] static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] static extern bool IsWindowEnabled(IntPtr h);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static List<string> Go(uint want){
   var r=new List<string>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     uint wp; GetWindowThreadProcessId(h, out wp);
     if(wp==want){
       var t=new StringBuilder(256); GetWindowText(h,t,256);
       var c=new StringBuilder(256); GetClassName(h,c,256);
       r.Add(h+"|vis="+IsWindowVisible(h)+"|en="+IsWindowEnabled(h)+"|"+c+"|"+t);
     }
     return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
[WN2]::Go(12124)
