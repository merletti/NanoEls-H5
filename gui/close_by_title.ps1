param([string]$title="",[switch]$Prefix)
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class CB {
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool PostMessageW(IntPtr h, uint m, IntPtr w, IntPtr l);
 public static List<IntPtr> Titled(string want,bool prefix){
   var r = new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(IsWindowVisible(h)){
       var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
       if(prefix ? sb.ToString().StartsWith(want) : sb.ToString()==want) r.Add(h);
     }
     return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
$hits=[CB]::Titled($title,$Prefix.IsPresent)
foreach($h in $hits){ [CB]::PostMessageW($h,0x0010,[IntPtr]::Zero,[IntPtr]::Zero) | Out-Null; "WM_CLOSE -> $h" }
if($hits.Count -eq 0){ "nessuna finestra '$title'" }
Start-Sleep -Milliseconds 800
