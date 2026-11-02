param([string]$invoke="")
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class AU {
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 public static IntPtr Find(string prefix){
   IntPtr found=IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(512); GetWindowText(h,sb,512);
     if(found==IntPtr.Zero && sb.ToString().StartsWith(prefix)) found=h;
     return true;
   }, IntPtr.Zero);
   return found;
 }
}
"@
$h=[AU]::Find("Nextion Editor")
$root=[System.Windows.Automation.AutomationElement]::FromHandle($h)
$cond=New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::ControlTypeProperty,[System.Windows.Automation.ControlType]::MenuItem)
$items=$root.FindAll([System.Windows.Automation.TreeScope]::Descendants,$cond)
"menu items: " + $items.Count
foreach($it in $items){
  $n=$it.Current.Name
  $p=""
  try{ $pa=$it.Current.GetCurrentPattern([System.Windows.Automation.InvokePattern]::Pattern); $p="invoke" }catch{ $p="noinvoke" }
  " - '$n' [$p]"
}
if($invoke -ne ""){
  foreach($it in $items){
    if($it.Current.Name -eq $invoke){
      "invoking '$invoke'"
      $pat=$it.GetCurrentPattern([System.Windows.Automation.InvokePattern]::Pattern)
      $pat.Invoke()
      break
    }
  }
  Start-Sleep -Milliseconds 800
  $cond2=New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::ControlTypeProperty,[System.Windows.Automation.ControlType]::MenuItem)
  $items2=$root.FindAll([System.Windows.Automation.TreeScope]::Descendants,$cond2)
  "after invoke: " + $items2.Count
  foreach($it in $items2){ " - '" + $it.Current.Name + "'" }
}
