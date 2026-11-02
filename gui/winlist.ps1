param([long]$close = 0)
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class EW {
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static System.Collections.Generic.List<string> List(){
   var res = new System.Collections.Generic.List<string>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(IsWindowVisible(h)){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       if(sb.Length > 0){ res.Add(h.ToInt64().ToString() + "|" + sb.ToString()); }
     }
     return true;
   }, IntPtr.Zero);
   return res;
 }
 public static void Close(long h){ PostMessage(new IntPtr(h), 0x10, IntPtr.Zero, IntPtr.Zero); }
}
"@
if($close -ne 0){ [EW]::Close($close); "closed $close"; exit 0 }
foreach($s in [EW]::List()){ $s }
