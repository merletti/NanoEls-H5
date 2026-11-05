param([string]$root = (Split-Path $PSScriptRoot -Parent))
Add-Type -AssemblyName System.Drawing
$ids = Get-Content (Join-Path $root "mockup-tft\card_clean\order.txt")
foreach ($id in $ids) {
  $bmp = [System.Drawing.Bitmap]::FromFile((Join-Path $root ("screen-it\card_clean_" + $id + ".png")))
  $ox0 = 9999; $ox1 = -1; $oy0 = 9999; $oy1 = -1
  $rows = @()
  for ($y = 0; $y -lt $bmp.Height; $y++) {
    $c = 0
    for ($x = 0; $x -lt $bmp.Width; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ($p.R -gt 150 -and $p.G -gt 90 -and $p.B -lt 120) {
        if ($x -lt $ox0) { $ox0 = $x }; if ($x -gt $ox1) { $ox1 = $x }
        if ($y -lt $oy0) { $oy0 = $y }; if ($y -gt $oy1) { $oy1 = $y }
      }
      if ($p.R -gt 120 -and $p.G -gt 120 -and $p.B -gt 120) { $c++ }
    }
    if ($c -gt 0 -and $y -gt 240) { $rows += $y }
  }
  $seg = @(); $s = -1; $prev = -99
  foreach ($r in $rows) { if ($r -ne $prev + 1) { if ($s -ge 0) { $seg += "$s-$prev" }; $s = $r }; $prev = $r }
  if ($s -ge 0) { $seg += "$s-$prev" }
  "{0,-12} OFF x{1}..{2} y{3}..{4}   righe: {5}" -f $id, $ox0, $ox1, $oy0, $oy1, ($seg -join ", ")
  $bmp.Dispose()
}
