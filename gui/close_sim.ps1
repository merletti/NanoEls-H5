Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class CS1 {
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static List<string> Titled(string want){
   var r = new List<string>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(IsWindowVisible(h)){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       if(sb.ToString() == want) r.Add(h.ToInt64().ToString());
     }
     return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
$hits = [CS1]::Titled("Nextion Editor")
foreach($h in $hits){
  [CS1]::PostMessage([IntPtr][long]$h, 0x0010, [IntPtr]::Zero, [IntPtr]::Zero) | Out-Null
  Write-Output "WM_CLOSE -> $h"
}
if($hits.Count -eq 0){ Write-Output "no simulator window found" }
Start-Sleep -Milliseconds 1200
