param([string]$cmd = "page 0")
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class W3 {
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr p, EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 [DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern IntPtr SendMessage(IntPtr h, uint m, IntPtr w, string l);
 [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct RECT { public int L,T,R,B; }
 public static List<string> Hits = new List<string>();
 public static void Scan(long parent){
   Hits.Clear();
   EnumChildWindows((IntPtr)parent, delegate(IntPtr h, IntPtr l){
       var sb=new StringBuilder(512); GetWindowText(h,sb,512);
       var cb=new StringBuilder(128); GetClassName(h,cb,128);
       RECT rc; GetWindowRect(h, out rc);
       Hits.Add(h.ToInt64()+"|"+cb+"|"+rc.L+","+rc.T+","+rc.R+","+rc.B+"|"+sb.ToString());
       return true;
   }, IntPtr.Zero);
 }
}
"@
$kids = [W3]::Kids
[W3]::Scan(2294906)
$input = $null
foreach($k in [W3]::Hits){
  $p = $k -split '\|'
  $rc = $p[2] -split ','
  if([int]$rc[1] -ge 700 -and [int]$rc[1] -lt 810 -and [int]$rc[0] -lt 570 -and ([int]$rc[2]-[int]$rc[0]) -gt 300){
    Write-Output ("cand: " + $k)
    if($p[3] -like "*pic*" -or $p[3] -eq ""){ $input = [long]$p[0] }
  }
}
if(-not $input){ Write-Output "NO INPUT"; exit }
[W3]::SendMessage([IntPtr]$input, 0x000C, [IntPtr]::Zero, $cmd) | Out-Null
Start-Sleep -Milliseconds 250
[W3]::SendMessage([IntPtr]4261940, 0x00F5, [IntPtr]::Zero, [IntPtr]::Zero) | Out-Null
Start-Sleep -Milliseconds 600
"sent: $cmd to $input"
