Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class FG { [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern IntPtr GetFocus(); }
"@
$h=[FG]::GetForegroundWindow(); $sb=New-Object System.Text.StringBuilder 256; [FG]::GetWindowText($h,$sb,256) | Out-Null
"fg=$h $($sb.ToString())"
