Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class WN {
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool IsWindowEnabled(IntPtr h);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
}
"@
[WN]::EnumWindows({ param($h,$l)
  $sb=New-Object System.Text.StringBuilder 512
  [WN]::GetWindowText($h,$sb,512) | Out-Null
  $t=$sb.ToString()
  $wpid=0; [WN]::GetWindowThreadProcessId($h,[ref]$wpid) | Out-Null
  if($wpid -eq 12124 -and $t -ne ''){ "{0}|vis={1}|en={2}|{3}" -f $h,[WN]::IsWindowVisible($h),[WN]::IsWindowEnabled($h),$t }
  $true
}, [IntPtr]::Zero) | Out-Null
