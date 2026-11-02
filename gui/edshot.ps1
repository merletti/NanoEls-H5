param([string]$actions="",[string]$out="gui/ed.png",[switch]$NoRestore)
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class ED1 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] i, int size);
 [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
 [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
 public static void Input(uint flags, int x, int y, int sx, int sy){
   var a=new INPUT[1];
   a[0].type=0;
   a[0].mi.dx=(int)System.Math.Round(x*65535.0/(sx-1));
   a[0].mi.dy=(int)System.Math.Round(y*65535.0/(sy-1));
   a[0].mi.dwFlags=flags;
   SendInput(1,a,Marshal.SizeOf(typeof(INPUT)));
 }
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public static List<IntPtr> All(string prefix){
   var r=new List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(512); GetWindowText(h,sb,512);
     if(sb.ToString().StartsWith(prefix)) r.Add(h);
     return true;
   }, IntPtr.Zero);
   return r;
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

$vsScreen=[System.Windows.Forms.SystemInformation]::VirtualScreen
$script:sx=$vsScreen.Width; $script:sy=$vsScreen.Height

function Click($x,$y){
  [ED1]::Input(0x8001,$x,$y,$script:sx,$script:sy); Start-Sleep -Milliseconds 80
  [ED1]::Input(0x0002,$x,$y,$script:sx,$script:sy); Start-Sleep -Milliseconds 50
  [ED1]::Input(0x0004,$x,$y,$script:sx,$script:sy); Start-Sleep -Milliseconds 250
}

$qod = [ED1]::All("Qoder")
foreach($h in $qod){ [ED1]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 700
$ed = [ED1]::All("Nextion Editor")
foreach($h in $ed){ [ED1]::ShowWindow($h,3) | Out-Null; [ED1]::BringWindowToTop($h) | Out-Null; [ED1]::SetForegroundWindow($h) | Out-Null }
Start-Sleep -Milliseconds 900
if([ED1]::GetForegroundWindow() -ne $ed[0]){
  $fg=[ED1]::GetForegroundWindow()
  $p0=[uint32]0
  $t1=[ED1]::GetWindowThreadProcessId($fg,[ref]$p0)
  $t2=[ED1]::GetWindowThreadProcessId($ed[0],[ref]$p0)
  [ED1]::AttachThreadInput($t1,$t2,$true) | Out-Null
  [ED1]::SetForegroundWindow($ed[0]) | Out-Null
  [ED1]::AttachThreadInput($t1,$t2,$false) | Out-Null
  Start-Sleep -Milliseconds 400
}
"fg=" + [ED1]::GetForegroundWindow() + " editor=" + $ed[0]

foreach($a in ($actions -split ';')){
  $a=$a.Trim(); if($a -eq ''){ continue }
  $p=$a -split ','
  switch($p[0]){
    'click' { Click ([int]$p[1]) ([int]$p[2]) }
    'drag'  {
      $x1=[int]$p[1]; $y1=[int]$p[2]; $x2=[int]$p[3]; $y2=[int]$p[4]
      [ED1]::Input(0x8001,$x1,$y1,$script:sx,$script:sy) | Out-Null; Start-Sleep -Milliseconds 150
      [ED1]::Input(0x0002,$x1,$y1,$script:sx,$script:sy) | Out-Null; Start-Sleep -Milliseconds 120
      for($s=1;$s -le 10;$s++){
        [ED1]::Input(0x8001,[int]($x1+($x2-$x1)*$s/10),[int]($y1+($y2-$y1)*$s/10),$script:sx,$script:sy) | Out-Null
        Start-Sleep -Milliseconds 60
      }
      [ED1]::Input(0x0004,$x2,$y2,$script:sx,$script:sy) | Out-Null; Start-Sleep -Milliseconds 300
    }
    'move'  { [ED1]::SetCursorPos([int]$p[1],[int]$p[2]) | Out-Null; Start-Sleep -Milliseconds 200 }
    'wait'  { Start-Sleep -Milliseconds ([int]$p[1]) }
    'key'   { [System.Windows.Forms.SendKeys]::SendWait($p[1]); Start-Sleep -Milliseconds 200 }
    'wheel' { [ED1]::mouse_event(0x0800,0,0,[int]$p[1],[UIntPtr]::Zero); Start-Sleep -Milliseconds 300 }
  }
}
Start-Sleep -Milliseconds 400
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
$bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
$g=[System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
$bmp.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$bmp.Dispose()
if(-not $NoRestore){ foreach($h in [ED1]::All("Qoder")){ [ED1]::ShowWindow($h,9) | Out-Null } }
"shot $out"
