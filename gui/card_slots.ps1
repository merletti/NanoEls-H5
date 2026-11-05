param([string]$root = (Split-Path $PSScriptRoot -Parent))
Add-Type -AssemblyName System.Drawing
$ids = Get-Content (Join-Path $root "mockup-tft\card_clean\order.txt")
foreach ($id in $ids) {
  $bmp = [System.Drawing.Bitmap]::FromFile((Join-Path $root ("screen-it\card_clean_" + $id + ".png")))
  $rows = @()
  for ($y = 0; $y -lt $bmp.Height; $y++) {
    $c = 0; $x0 = 9999; $x1 = -1
    for ($x = 0; $x -lt $bmp.Width; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ($p.R -eq 0x10 -and $p.G -eq 0x11 -and $p.B -eq 0x14) { $c++; if ($x -lt $x0) { $x0 = $x }; if ($x -gt $x1) { $x1 = $x } }
    }
    $rows += ,@($y, $c, $x0, $x1)
  }
  $out = @(); $cur = $null
  foreach ($r in $rows) {
    if ($r[1] -gt 20) {
      if ($null -eq $cur) { $cur = @($r[0], $r[0], $r[2], $r[3]) }
      else { $cur[1] = $r[0]; if ($r[2] -lt $cur[2]) { $cur[2] = $r[2] }; if ($r[3] -gt $cur[3]) { $cur[3] = $r[3] } }
    } else { if ($null -ne $cur) { $out += ,$cur; $cur = $null } }
  }
  if ($null -ne $cur) { $out += ,$cur }
  $line = "$id :"
  foreach ($r in $out) { $line += "  x$($r[2])..$($r[3]) y$($r[0])..$($r[1]) (w$($r[3]-$r[2]+1) h$($r[1]-$r[0]+1))" }
  $line
  $bmp.Dispose()
}
