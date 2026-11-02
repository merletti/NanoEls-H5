param([string]$cmds="",[string]$out="gui/sim.png",[string]$out2="",[int]$after=600)
Add-Type @"
using System;using System.Text;using System.Collections.Generic;using System.Runtime.InteropServices;
public class SC1 {
 [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y);
 [DllImport("user32.dll")] public static extern void mouse_event(uint f,uint dx,uint dy,int d,UIntPtr e);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
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

function Click($x,$y){
  [SC1]::SetCursorPos($x,$y) | Out-Null; Start-Sleep -Milliseconds 120
  [SC1]::mouse_event(0x0002,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 40
  [SC1]::mouse_event(0x0004,0,0,0,[UIntPtr]::Zero); Start-Sleep -Milliseconds 200
}
function Shot($name){
  $vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
  $bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
  $g=[System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
  $bmp.Save((Join-Path (Get-Location) $name),[System.Drawing.Imaging.ImageFormat]::Png)
  $g.Dispose();$bmp.Dispose()
}

foreach($h in [SC1]::All("Qoder")){ [SC1]::ShowWindow($h,6) | Out-Null }
Start-Sleep -Milliseconds 600
foreach($h in [SC1]::All("Nextion Editor")){ [SC1]::ShowWindow($h,3) | Out-Null; [SC1]::SetForegroundWindow($h) | Out-Null }
Start-Sleep -Milliseconds 700

$i=0
foreach($c in ($cmds -split '\|')){
  $c=$c.Trim(); if($c -eq ''){ continue }
  Click 300 790
  Start-Sleep -Milliseconds 150
  Set-Clipboard -Value $c
  Start-Sleep -Milliseconds 150
  [System.Windows.Forms.SendKeys]::SendWait('^a'); Start-Sleep -Milliseconds 100
  [System.Windows.Forms.SendKeys]::SendWait('^v'); Start-Sleep -Milliseconds 250
  [System.Windows.Forms.SendKeys]::SendWait('{ENTER}'); Start-Sleep -Milliseconds $after
  $i++
}
Shot $out
if($out2 -ne ""){ Shot $out2 }
foreach($h in [SC1]::All("Qoder")){ [SC1]::ShowWindow($h,9) | Out-Null }
"done $i"
