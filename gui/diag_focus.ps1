Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class QZ {
 [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X; public int Y; }
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint ga);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public static string Info(IntPtr h){
   var t=new StringBuilder(300); GetWindowText(h,t,300);
   var c=new StringBuilder(300); GetClassName(h,c,300);
   uint pid; GetWindowThreadProcessId(h,out pid);
   return h+" pid="+pid+" '"+c+"' '"+t+"'";
 }
 public static List<IntPtr> Titled(string prefix){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(512); GetWindowText(h,sb,512);
     if(sb.ToString().StartsWith(prefix)) r.Add(h);
     return true;
   }, IntPtr.Zero);
   return r;
 }
 public static string At(int x,int y){
   var p=new POINT(); p.X=x; p.Y=y;
   var h=WindowFromPoint(p);
   var top=GetAncestor(h,2);
   return "at("+x+","+y+") hit="+Info(h)+" | top="+Info(top);
 }
}
"@
$q=[QZ]::Titled("Qoder")
foreach($h in $q){ [QZ]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 800
$e=[QZ]::Titled("Nextion Editor")
"editor list: " + ($e -join ',')
[QZ]::ShowWindow($e[0],3) | Out-Null
[QZ]::SetForegroundWindow($e[0]) | Out-Null
Start-Sleep -Milliseconds 800
"fg=" + [QZ]::Info([QZ]::GetForegroundWindow()) + " iconic(qoder=" + [QZ]::IsIconic($q[0]) + ")"
[QZ]::At(50,37)
[QZ]::At(1130,169)
[QZ]::At(640,400)
