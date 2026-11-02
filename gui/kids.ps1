Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class W2 {
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr p, EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct RECT { public int L,T,R,B; }
 public static List<string> Kids(long parent){
   var r=new List<string>();
   EnumChildWindows((IntPtr)parent, delegate(IntPtr h, IntPtr l){
       var sb=new StringBuilder(256); GetWindowText(h,sb,256);
       var cb=new StringBuilder(256); GetClassName(h,cb,256);
       RECT rc; GetWindowRect(h, out rc);
       r.Add(h.ToInt64()+" | "+cb+" | "+rc.L+","+rc.T+","+rc.R+","+rc.B+" | "+sb.ToString());
       return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
[W2]::Kids(2294906) | Select-Object -First 60
