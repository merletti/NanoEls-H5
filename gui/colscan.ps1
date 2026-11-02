param([string]$src="gui/screen.png",[int]$x0=0,[int]$x1=1279,[int]$y0=0,[int]$y1=0,[int]$thr=120,[int]$gap=6)
Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::FromFile((Resolve-Path $src))
$hit = New-Object int[] ($x1 - $x0 + 1)
for($y=$y0; $y -le $y1; $y++){
  for($x=$x0; $x -le $x1; $x++){
    $c = $img.GetPixel($x,$y)
    $lum = 0.299*$c.R + 0.587*$c.G + 0.114*$c.B
    if($lum -lt $thr){ $hit[$x-$x0]++ }
  }
}
$img.Dispose()
$start = -1; $last = -1
for($i=0; $i -le ($x1-$x0); $i++){
  if($hit[$i] -gt 0){
    if($start -lt 0){ $start = $i }
    elseif(($i - $last) -gt $gap){ "run " + ($x0+$start) + ".." + ($x0+$last) + " center " + [int](($x0+$start+$x0+$last)/2); $start = $i }
    $last = $i
  }
}
if($start -ge 0){ "run " + ($x0+$start) + ".." + ($x0+$last) + " center " + [int](($x0+$start+$x0+$last)/2) }
