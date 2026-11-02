param([string]$root = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5")
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile((Join-Path $root "screen-it\card_clean_ingranaggi.png"))
foreach ($band in @(@(265,290,"STATO"), @(292,318,"MODALITA"), @(320,345,"hint"))) {
  $y0 = $band[0]; $y1 = $band[1]; $name = $band[2]
  $minX = 9999; $maxX = -1; $minY = 9999; $maxY = -1
  for ($y = $y0; $y -le $y1; $y++) {
    for ($x = 0; $x -lt $bmp.Width; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ($p.R -gt 120 -and $p.G -gt 120 -and $p.B -gt 120) {
        if ($x -lt $minX) { $minX = $x }; if ($x -gt $maxX) { $maxX = $x }
        if ($y -lt $minY) { $minY = $y }; if ($y -gt $maxY) { $maxY = $y }
      }
    }
  }
  "$name : x$minX..$maxX y$minY..$maxY"
}
# parte destra della riga STATO (valore) e della riga MODALITA
foreach ($band in @(@(265,290,"STATO dx"), @(292,318,"MODALITA dx"))) {
  $y0 = $band[0]; $y1 = $band[1]; $name = $band[2]
  $minX = 9999; $maxX = -1
  for ($y = $y0; $y -le $y1; $y++) {
    for ($x = 150; $x -lt $bmp.Width; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ($p.R -gt 120 -and $p.G -gt 120 -and $p.B -gt 120) {
        if ($x -lt $minX) { $minX = $x }; if ($x -gt $maxX) { $maxX = $x }
      }
    }
  }
  "$name : x$minX..$maxX"
}
$bmp.Dispose()
