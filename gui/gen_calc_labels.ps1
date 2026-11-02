param([string]$out = "screen-it/calc_labels.png", [string]$preview)
Add-Type -AssemblyName System.Drawing

$W = 284
$ROWH = 26
$ROWS = 18
$H = $ROWH * $ROWS
$card = [System.Drawing.Color]::FromArgb(255, 0x15, 0x16, 0x1A)
$muted = [System.Drawing.Color]::FromArgb(255, 0x9A, 0xA0, 0xA8)

$labels = @{}
$labels[1]  = "AVANZ. mm/giro"
$labels[2]  = "AVANZ. mm/giro"
$labels[3]  = "AVANZ. mm/giro"
$labels[4]  = "AVANZ. mm/giro"
$labels[6]  = "AVANZ. mm/giro"
$labels[7]  = "AVANZ. mm/giro"
$labels[8]  = "VELOC. mm/min"
$labels[10] = "AVANZ. mm/giro"
$labels[11] = "VEL. MAX mm/min"
$labels[12] = "AVANZ. mm/giro"
$labels[17] = "RIDUZ. TOTALE mm"

$bmp = New-Object System.Drawing.Bitmap -ArgumentList $W, $H
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.Clear($card)
$g.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::AntiAliasGridFit
$font = New-Object System.Drawing.Font -ArgumentList "Arial", 9.375, ([System.Drawing.FontStyle]::Regular), ([System.Drawing.GraphicsUnit]::Point)
$brush = New-Object System.Drawing.SolidBrush -ArgumentList $muted
foreach ($k in ($labels.Keys | Sort-Object)) {
  $y = $k * $ROWH + 3
  $g.DrawString($labels[$k], $font, $brush, 18, $y)
}
$g.Dispose()
$bmp.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
$font.Dispose(); $brush.Dispose()
"ok $out"

if ($preview) {
  # Compose the strip row for page 2 onto the real FILETTO background and paint
  # a sample value with the real glyph sprite, to check the final alignment.
  $bgPath = "screen-it/filetto_bg.png"
  $bg = [System.Drawing.Bitmap]::FromFile((Join-Path (Get-Location) $bgPath))
  $strip = [System.Drawing.Bitmap]::FromFile((Join-Path (Get-Location) $out))
  $sprite = [System.Drawing.Bitmap]::FromFile((Join-Path (Get-Location) "screen-it/sprite_values_card.png"))
  $g2 = [System.Drawing.Graphics]::FromImage($bg)
  $dst = [System.Drawing.Rectangle]::new(502, 364, 284, 26)
  $src = [System.Drawing.Rectangle]::new(0, 2 * $ROWH, 284, 26)
  $g2.DrawImage($strip, $dst, $src, [System.Drawing.GraphicsUnit]::Pixel)
  $value = "3.500"
  $right = 768
  $x = $right - $value.Length * 16
  for ($i = 0; $i -lt $value.Length; $i++) {
    $code = [int][char]$value[$i] - 32
    $sx = ($code % 50) * 16
    $sy = [int][math]::Floor($code / 50) * 26
    $dg = [System.Drawing.Rectangle]::new(($x + $i * 16), 364, 16, 26)
    $sg = [System.Drawing.Rectangle]::new($sx, $sy, 16, 26)
    $g2.DrawImage($sprite, $dg, $sg, [System.Drawing.GraphicsUnit]::Pixel)
  }
  $g2.Dispose()
  $bg.Save((Join-Path (Get-Location) $preview), [System.Drawing.Imaging.ImageFormat]::Png)
  $bg.Dispose(); $strip.Dispose(); $sprite.Dispose()
  "ok $preview"
}
