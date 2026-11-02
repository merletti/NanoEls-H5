Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;using System.Runtime.InteropServices;
public class CU { [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
 [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] i, int s);
 public struct POINT { public int X; public int Y; }
 [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx,dy,data; public uint flags,time; public IntPtr extra; }
 [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
}
"@
"pos start: " + [System.Windows.Forms.Cursor]::Position
$ok = [CU]::SetCursorPos(300,300); "SetCursorPos(300,300) -> $ok"
Start-Sleep -Milliseconds 300
"pos after SetCursorPos: " + [System.Windows.Forms.Cursor]::Position
$p = New-Object CU+POINT
[CU]::GetCursorPos([ref]$p) | Out-Null
"GetCursorPos api: $($p.X),$($p.Y)"
# SendInput absolute move to (500,400)
$in = New-Object CU+INPUT
$in.type = 0
$in.mi.dx = [int](500*65535/1280); $in.mi.dy = [int](400*65535/1024)
$in.mi.flags = 0x8001  # ABSOLUTE|MOVE
$arr = New-Object 'CU+INPUT[]' 1; $arr[0]=$in
$n = [CU]::SendInput(1,$arr,[Runtime.InteropServices.Marshal]::SizeOf($arr[0]))
"SendInput move -> $n"
Start-Sleep -Milliseconds 300
"pos after SendInput: " + [System.Windows.Forms.Cursor]::Position
