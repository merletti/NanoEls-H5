Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class HD {
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumThreadWindows(uint t, EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr p, EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern int GetWindowLong(IntPtr h, int i);
 [DllImport("user32.dll")] public static extern bool IsWindowEnabled(IntPtr h);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool IsHungAppWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr SendMessageTimeout(IntPtr h,uint m,IntPtr w,IntPtr l,uint f,uint t,out IntPtr r);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr FindWindow(string c, string t);
 public delegate bool EnumProc2(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc2 cb, IntPtr l);
 public static IntPtr Find(string prefix){
   IntPtr found=IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(512); GetWindowText(h,sb,512);
     if(found==IntPtr.Zero && sb.ToString().StartsWith(prefix)) found=h;
     return true;
   }, IntPtr.Zero);
   return found;
 }
 public static string Info(IntPtr h){
   var t=new StringBuilder(300); GetWindowText(h,t,300);
   var c=new StringBuilder(300); GetClassName(h,c,300);
   return String.Format("hwnd={0} vis={1} en={2} class='{3}' title='{4}' style=0x{5:X8}", h, IsWindowVisible(h), IsWindowEnabled(h), c.ToString(), t.ToString(), GetWindowLong(h,-16));
 }
}
"@
$h=[HD]::Find("Nextion Editor")
"main: " + [HD]::Info($h)
"hung: " + [HD]::IsHungAppWindow($h)
$p0=[uint32]0
$tid=[HD]::GetWindowThreadProcessId($h,[ref]$p0)
"tid=$tid pid=$p0"
$r=New-Object IntPtr
$ok=[HD]::SendMessageTimeout($h,0,[IntPtr]::Zero,[IntPtr]::Zero,2,3000,[ref]$r)
"WM_NULL timeout result: $ok"
"--- thread top-level windows ---"
$cb=[HD+EnumProc]{ param($w,$l) "TL " + [HD]::Info($w); return $true }
[HD]::EnumThreadWindows($tid,$cb,[IntPtr]::Zero) | Out-Null
"--- all descendants ---"
$cb2=[HD+EnumProc]{ param($w,$l) "CH " + [HD]::Info($w); return $true }
[HD]::EnumChildWindows($h,$cb2,[IntPtr]::Zero) | Out-Null
