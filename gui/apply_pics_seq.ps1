param([string]$out="gui/pics_seq.png")
Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class SQ1 {
 [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
 [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
 [DllImport("user32.dll", CharSet=CharSet.Unicode, EntryPoint="SendMessageW")] public static extern IntPtr SendMessageS(IntPtr h, uint m, IntPtr w, StringBuilder l);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] i, int size);
 [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 public struct POINT { public int X; public int Y; }
 [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
 [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public MOUSEINPUT mi; }
 public static string Text(IntPtr h){ var sb=new StringBuilder(256); SendMessageS(h,0x000D,(IntPtr)256,sb); return sb.ToString(); }
 public static void Click(int x,int y,int sx,int sy){
   var m=new INPUT[1]; m[0].type=0;
   m[0].mi.dx=(int)System.Math.Round(x*65535.0/(sx-1));
   m[0].mi.dy=(int)System.Math.Round(y*65535.0/(sy-1));
   m[0].mi.dwFlags=0x8001; SendInput(1,m,Marshal.SizeOf(typeof(INPUT)));
   var d=new INPUT[1]; d[0].type=0;
   d[0].mi.dx=m[0].mi.dx; d[0].mi.dy=m[0].mi.dy;
   d[0].mi.dwFlags=0x0002; SendInput(1,d,Marshal.SizeOf(typeof(INPUT)));
   var u=new INPUT[1]; u[0].type=0;
   u[0].mi.dx=m[0].mi.dx; u[0].mi.dy=m[0].mi.dy;
   u[0].mi.dwFlags=0x0004; SendInput(1,u,Marshal.SizeOf(typeof(INPUT)));
 }
 public static IntPtr Find(string prefix){
   IntPtr res=IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(res==IntPtr.Zero && IsWindowVisible(h)){
       var sb=new StringBuilder(256); GetWindowText(h,sb,256);
       if(sb.ToString().StartsWith(prefix)){ res=h; return false; }
     }
     return true;
   }, IntPtr.Zero);
   return res;
 }
 public static IntPtr FindAll(string prefix, int idx){
   var r=new System.Collections.Generic.List<IntPtr>();
   EnumWindows(delegate(IntPtr h, IntPtr l){
     if(IsWindowVisible(h)){
       var sb=new StringBuilder(256); GetWindowText(h,sb,256);
       if(sb.ToString().StartsWith(prefix)) r.Add(h);
     }
     return true;
   }, IntPtr.Zero);
   if(idx < r.Count) return r[idx];
   return IntPtr.Zero;
 }
}
"@
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$ed = [SQ1]::Find("Nextion Editor(C:")
if($ed -eq [IntPtr]::Zero){ "editor non trovato"; exit 1 }
$q = [SQ1]::FindAll("Qoder",0)
if($q -ne [IntPtr]::Zero){ [SQ1]::ShowWindow($q,6) | Out-Null }
[SQ1]::ShowWindow($ed,3) | Out-Null
[SQ1]::SetForegroundWindow($ed) | Out-Null
Start-Sleep -Milliseconds 900
$vs=[System.Windows.Forms.SystemInformation]::VirtualScreen
function Shot(){
  $bmp=New-Object System.Drawing.Bitmap($vs.Width,$vs.Height)
  $g=[System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen($vs.Left,$vs.Top,0,0,$bmp.Size)
  $g.Dispose()
  return $bmp
}
function SelRowY(){
  $b=Shot
  $ys=@()
  for($y=160;$y -lt 820;$y++){
    $n=0
    for($x=1095;$x -lt 1250;$x+=5){
      $c=$b.GetPixel($x,$y)
      if($c.R -eq 0 -and $c.G -eq 0 -and $c.B -eq 255){ $n++ }
    }
    if($n -ge 20){ $ys += $y }
  }
  $b.Dispose()
  if($ys.Count -eq 0){ return -1 }
  return [int]($ys[0] + ($ys[$ys.Count-1]-$ys[0])/2)
}
$plan = @(
  @{steps=0; old='37'; new='57'; label='page14 X-INGRANAGGI'},
  @{steps=5; old='25'; new='58'; label='page19 SCANALATURA'}
)
foreach($it in $plan){
  $y = SelRowY
  if($y -lt 0){ Write-Host "STOP: riga selezionata non trovata ($($it.label))"; break }
  [SQ1]::Click(1120,$y,$vs.Width,$vs.Height)
  Start-Sleep -Milliseconds 500
  for($i=0;$i -lt $it.steps;$i++){ [System.Windows.Forms.SendKeys]::SendWait("{DOWN}"); Start-Sleep -Milliseconds 250 }
  Start-Sleep -Milliseconds 600
  [SQ1]::Click(1183,678,$vs.Width,$vs.Height)
  Start-Sleep -Milliseconds 700
  $pt = New-Object SQ1+POINT; $pt.X=1183; $pt.Y=678
  $child = [SQ1]::WindowFromPoint($pt)
  if($child -eq [IntPtr]::Zero){ Write-Host "STOP: campo pic non trovato ($($it.label))"; break }
  $before = [SQ1]::Text($child)
  if($before -ne $it.old){
    Write-Host ("STOP {0}: atteso {1}, trovato {2}" -f $it.label,$it.old,$before)
    [System.Windows.Forms.SendKeys]::SendWait("{ESC}")
    Start-Sleep -Milliseconds 400
    break
  }
  [SQ1]::SendMessage($child,0x00B1,[IntPtr]0,[IntPtr](-1)) | Out-Null
  Start-Sleep -Milliseconds 180
  foreach($ch in $it.new.ToCharArray()){
    [SQ1]::PostMessage($child,0x0102,[IntPtr][int][char]$ch,[IntPtr]1) | Out-Null
    Start-Sleep -Milliseconds 90
  }
  Start-Sleep -Milliseconds 220
  $typed = [SQ1]::Text($child)
  [System.Windows.Forms.SendKeys]::SendWait("{ENTER}")
  Start-Sleep -Milliseconds 900
  Write-Host ("{0}: '{1}' -> {2} (digitato {3})" -f $it.label,$before,$it.new,$typed)
}
$b=Shot
$b.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$b.Dispose()
"done -> $out"
