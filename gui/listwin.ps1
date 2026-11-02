Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class LW1 {
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct RECT { public int L, T, R, B; }
 public static void Dump(){
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(IsWindowVisible(h)){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       string t = sb.ToString();
       if(t.Length > 0){
         RECT r; GetWindowRect(h, out r);
         uint pid; GetWindowThreadProcessId(h, out pid);
         Console.WriteLine("{0,6} {1,5} [{2},{3} {4}x{5}] {6}", pid, h.ToInt64(), r.L, r.T, r.R-r.L, r.B-r.T, t);
       }
     }
     return true;
   }, IntPtr.Zero);
 }
}
"@
[LW1]::Dump()
