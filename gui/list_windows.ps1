Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class W5 {
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct RECT { public int L,T,R,B; }
 public static List<string> List(){
   var r=new List<string>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(400); GetWindowText(h,sb,400);
     string t=sb.ToString();
     if(t.Contains("Nextion") || t.StartsWith("Qoder")){
       RECT q; GetWindowRect(h, out q);
       r.Add(h+" | "+t+" | "+q.L+","+q.T+" "+q.R+","+q.B);
     }
     return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
[W5]::List()