param([string]$src,[int]$y=560,[int]$x0=235,[int]$x1=1045,[string]$out="gui/runs.txt")
Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::FromFile((Resolve-Path $src))
$bg = $img.GetPixel($x0+1,$y)
$runs = New-Object System.Collections.ArrayList
$inrun = $false; $start = 0
for($x=$x0; $x -le $x1; $x++){
  $c = $img.GetPixel($x,$y)
  $diff = [Math]::Abs($c.R-$bg.R) + [Math]::Abs($c.G-$bg.G) + [Math]::Abs($c.B-$bg.B)
  if($diff -gt 30){
    if(-not $inrun){ $inrun = $true; $start = $x }
  } else {
    if($inrun){ $inrun = $false; [void]$runs.Add("$start-$($x-1) w=$($x-$start)") }
  }
}
if($inrun){ [void]$runs.Add("$start-$x1") }
$lines = "bg=($($bg.R),$($bg.G),$($bg.B)) y=$y x0=$x0 x1=$x1"; $lines += "`n" + ($runs -join "`n")
Set-Content -Path (Join-Path (Get-Location) $out) -Value $lines
$img.Dispose()
$lines
