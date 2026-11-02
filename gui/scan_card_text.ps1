param([string]$root = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5")
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile((Join-Path $root "screen-it\card_clean_ingranaggi.png"))
for ($y = 240; $y -lt $bmp.Height; $y++) {
  $c = 0
  for ($x = 0; $x -lt $bmp.Width; $x++) {
    $p = $bmp.GetPixel($x, $y)
    if ($p.R -gt 90 -or $p.G -gt 90 -or $p.B -gt 90) { $c++ }
  }
  if ($c -gt 0) { "y$y : $c pixel chiari" }
}
$bmp.Dispose()
