Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class EW {
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern int GetWindowLong(IntPtr h, int i);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 [DllImport("user32.dll")] public static extern bool GetLayeredWindowAttributes(IntPtr h, out uint key, out byte alpha, out uint flags);
 [DllImport("user32.dll")] public static extern IntPtr GetWindow(IntPtr h, uint cmd);
 [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L,T,R,B; }
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 public static List<IntPtr> List(){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){ r.Add(h); return true; }, IntPtr.Zero);
   return r;
 }
 public static string Describe(IntPtr h){
   var t=new StringBuilder(512); GetWindowText(h,t,512);
   var c=new StringBuilder(256); GetClassName(h,c,256);
   uint pid; GetWindowThreadProcessId(h, out pid);
   RECT rc; GetWindowRect(h, out rc);
   int ex=GetWindowLong(h,-20);
   uint key=0; byte alpha=0; uint fl=0;
   bool ok=GetLayeredWindowAttributes(h, out key, out alpha, out fl);
   string lay = ok ? (" layered alpha="+alpha+" flags="+fl) : "";
   string owner = GetWindow(h,4).ToString();
   return String.Format("hwnd={0} pid={1} vis={2} icon={3} class='{4}' title='{5}' rect={6},{7},{8},{9} ex=0x{10:X} owner={11}{12}",
     h, pid, IsWindowVisible(h), IsIconic(h), c.ToString(), t.ToString(), rc.L, rc.T, rc.R, rc.B, ex, owner, lay);
 }
}
"@
$procs=@{}; Get-Process | ForEach-Object { $procs[[uint32]$_.Id]=$_.ProcessName }
"foreground " + [EW]::GetForegroundWindow()
foreach($h in [EW]::List()){
  $d=[EW]::Describe($h)
  if($d -match "vis=True"){ "$d  proc=" + $procs[[uint32](($d -split 'pid=')[1].Split(' ')[0])] }
}
