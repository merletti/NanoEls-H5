param([string]$file,[int]$x,[int]$y,[int]$w,[int]$h,[int]$threshold=120)
Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::FromFile((Resolve-Path $file))
$minX = 99999; $minY = 99999; $maxX = -1; $maxY = -1
for ($yy = $y; $yy -lt ($y + $h); $yy++) {
  for ($xx = $x; $xx -lt ($x + $w); $xx++) {
    $c = $img.GetPixel($xx, $yy)
    $lum = [int](0.299 * $c.R + 0.587 * $c.G + 0.114 * $c.B)
    if ($lum -ge $threshold) {
      if ($xx -lt $minX) { $minX = $xx }
      if ($xx -gt $maxX) { $maxX = $xx }
      if ($yy -lt $minY) { $minY = $yy }
      if ($yy -gt $maxY) { $maxY = $yy }
    }
  }
}
if ($maxX -lt 0) { "nessun pixel sopra soglia" } else {
  "bbox x=$minX..$maxX y=$minY..$maxY w=$($maxX-$minX+1) h=$($maxY-$minY+1) cx=$([int](($minX+$maxX)/2))"
}
$img.Dispose()
