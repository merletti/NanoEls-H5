Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class UIAF {
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
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
}
"@
$h = [UIAF]::Find("Nextion Editor(C:")
if($h -eq [IntPtr]::Zero){ "ERRORE: editor non trovato"; exit 1 }
$root = [System.Windows.Automation.AutomationElement]::FromHandle($h)
$all = $root.FindAll([System.Windows.Automation.TreeScope]::Descendants, [System.Windows.Automation.Condition]::TrueCondition)
foreach($e in $all){
  $n = $e.Current.Name
  if($n -ne ''){
    $r = $e.Current.BoundingRectangle
    "{0} | {1} | {2},{3} {4}x{5}" -f $e.Current.ControlType.ProgrammaticName, $n, [int]$r.X, [int]$r.Y, [int]$r.Width, [int]$r.Height
  }
}
"totale elementi: " + $all.Count
