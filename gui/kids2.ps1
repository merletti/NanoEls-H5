Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class KW1 {
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr p, EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct RECT { public int L, T, R, B; }
 public static IntPtr Find(string prefix){
   IntPtr res = IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(res == IntPtr.Zero && IsWindowVisible(h)){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       if(sb.ToString().StartsWith(prefix)){ res = h; return false; }
     }
     return true;
   }, IntPtr.Zero);
   return res;
 }
 public static void Kids(IntPtr h, int depth){
   var sb = new StringBuilder(256); var cn = new StringBuilder(256);
   GetWindowText(h, sb, 256); GetClassName(h, cn, 256);
   RECT r; GetWindowRect(h, out r);
   Console.WriteLine("{0}{1} [{2},{3} {4}x{5}] '{6}' class={7}", new string(' ', depth*2), h.ToInt64(), r.L, r.T, r.R-r.L, r.B-r.T, sb.ToString(), cn.ToString());
   EnumChildWindows(h, delegate(IntPtr c, IntPtr l){ Kids(c, depth+1); return true; }, IntPtr.Zero);
 }
}
"@
$h = [KW1]::Find("Nextion Editor")
"main: $($h.ToInt64())"
[KW1]::Kids($h, 0)
