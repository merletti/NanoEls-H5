param([int]$procId, [string]$keys = "")
Add-Type @"
using System;using System.Runtime.InteropServices;
public class WN {
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
}
"@
$p = [System.Diagnostics.Process]::GetProcessById($procId)
$h = $p.MainWindowHandle
if ($h -eq [IntPtr]::Zero) { "no-window"; exit 1 }
if ([WN]::IsIconic($h)) { [WN]::ShowWindow($h, 9) | Out-Null } else { [WN]::ShowWindow($h, 5) | Out-Null }
[WN]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 500
if ($keys -ne "") {
  $w = New-Object -ComObject WScript.Shell
  $w.SendKeys($keys)
  Start-Sleep -Milliseconds 800
}
"hwnd=$h"
