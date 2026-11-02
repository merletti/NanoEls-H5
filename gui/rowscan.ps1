param([string]$src,[int]$x0=500,[int]$x1=799,[int]$y0=280,[int]$y1=440)
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile($src)
$rows = @()
for ($y = $y0; $y -le $y1; $y++) {
  $c = 0
  $minx = 9999; $maxx = -1
  for ($x = $x0; $x -le $x1; $x++) {
    $p = $bmp.GetPixel($x, $y)
    # card is #15161A, page bg #0A0A0C; ignore near-black and thin card border
    if ($p.R -gt 60 -or $p.G -gt 60 -or $p.B -gt 60) {
      $c++
      if ($x -lt $minx) { $minx = $x }
      if ($x -gt $maxx) { $maxx = $x }
    }
  }
  if ($c -gt 0) { $rows += ("{0}: {1} px  x {2}..{3}" -f $y, $c, $minx, $maxx) }
}
$rows
$bmp.Dispose()
