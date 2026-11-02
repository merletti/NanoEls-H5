Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class CL {
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h, int attr, out int val, int size);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern int GetWindowLong(IntPtr h, int i);
 public static void Dump(IntPtr h){
   var t=new StringBuilder(300); GetWindowText(h,t,300);
   int c=0; int hr=DwmGetWindowAttribute(h,14,out c,4);
   uint pid; GetWindowThreadProcessId(h,out pid);
   Console.WriteLine("hwnd="+h+" pid="+pid+" vis="+IsWindowVisible(h)+" topmost="+((GetWindowLong(h,-20)&8)!=0)+" cloaked="+c+" (hr=0x"+hr.ToString("X")+") '"+t+"'");
 }
}
"@
$list=New-Object System.Collections.ArrayList
$cb=[CL+EnumProc]{ param($h,$l) [void]$list.Add($h); return $true }
[CL]::EnumWindows($cb,[IntPtr]::Zero) | Out-Null
foreach($h in $list){ [CL]::Dump($h) }
