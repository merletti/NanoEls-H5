param([string]$src,[int]$x=300,[int]$y0=170,[int]$y1=650,[string]$out="gui/vruns.txt")
Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::FromFile((Resolve-Path $src))
$bg = $img.GetPixel($x,$y0+1)
$runs = New-Object System.Collections.ArrayList
$inrun = $false; $start = 0
for($y=$y0; $y -le $y1; $y++){
  $c = $img.GetPixel($x,$y)
  $diff = [Math]::Abs($c.R-$bg.R) + [Math]::Abs($c.G-$bg.G) + [Math]::Abs($c.B-$bg.B)
  if($diff -gt 30){
    if(-not $inrun){ $inrun = $true; $start = $y }
  } else {
    if($inrun){ $inrun = $false; [void]$runs.Add("$start-$($y-1) h=$($y-$start)") }
  }
}
if($inrun){ [void]$runs.Add("$start-$y1") }
$lines = "bg=($($bg.R),$($bg.G),$($bg.B)) x=$x y0=$y0 y1=$y1"; $lines += "`n" + ($runs -join "`n")
Set-Content -Path (Join-Path (Get-Location) $out) -Value $lines
$img.Dispose()
$lines
