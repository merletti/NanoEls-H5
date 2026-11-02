param([string]$root = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5")
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile((Join-Path $root "screen-it\card_clean_ingranaggi.png"))
$minX = 9999; $maxX = -1; $minY = 9999; $maxY = -1
for ($y = 0; $y -lt $bmp.Height; $y++) {
  for ($x = 0; $x -lt $bmp.Width; $x++) {
    $p = $bmp.GetPixel($x, $y)
    if ($p.R -gt 150 -and $p.G -gt 90 -and $p.B -lt 120 -and ($y -gt 150)) {
      if ($x -lt $minX) { $minX = $x }; if ($x -gt $maxX) { $maxX = $x }
      if ($y -lt $minY) { $minY = $y }; if ($y -gt $maxY) { $maxY = $y }
    }
  }
}
"arancione: x$minX..$maxX y$minY..$maxY"
$bmp.Dispose()
