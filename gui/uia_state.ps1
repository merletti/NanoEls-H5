Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
$h = (Get-Process -Id 12124).MainWindowHandle
$root = [System.Windows.Automation.AutomationElement]::FromHandle($h)
$cond = New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::ControlTypeProperty,[System.Windows.Automation.ControlType]::Button)
$btns = $root.FindAll([System.Windows.Automation.TreeScope]::Descendants,$cond)
foreach($b in $btns){
  $n = $b.Current.Name
  if($n -match 'Compile|Debug|Upload|Save|Open'){ "{0} | enabled={1}" -f $n,$b.Current.IsEnabled }
}
