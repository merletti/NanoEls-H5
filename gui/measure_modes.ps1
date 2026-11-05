param([string]$root = (Split-Path $PSScriptRoot -Parent))
Add-Type -AssemblyName System.Drawing
$ids = Get-Content (Join-Path $root "mockup-tft\card_clean\order.txt")
foreach ($id in $ids) {
  $bmp = [System.Drawing.Bitmap]::FromFile((Join-Path $root ("screen-it\card_clean_" + $id + ".png")))
  $minX = 9999; $maxX = -1
  for ($y = 296; $y -le 312; $y++) {
    for ($x = 150; $x -lt $bmp.Width; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ($p.R -gt 120 -and $p.G -gt 120 -and $p.B -gt 120) {
        if ($x -lt $minX) { $minX = $x }; if ($x -gt $maxX) { $maxX = $x }
      }
    }
  }
  "{0,-12} modalita x{1}..{2} (largo {3})" -f $id, $minX, $maxX, ($maxX - $minX + 1)
  $bmp.Dispose()
}
