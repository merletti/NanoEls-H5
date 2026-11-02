param([string]$src = "screen-it/sprite_values2.png", [string]$out = "screen-it/sprite_values_card.png")
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile((Join-Path (Get-Location) $src))
$dst = New-Object System.Drawing.Bitmap -ArgumentList $bmp.Width, $bmp.Height
$bg = [System.Drawing.Color]::FromArgb(255, 0x10, 0x11, 0x14)
$card = [System.Drawing.Color]::FromArgb(255, 0x15, 0x16, 0x1A)
$changed = 0
for ($y = 0; $y -lt $bmp.Height; $y++) {
  for ($x = 0; $x -lt $bmp.Width; $x++) {
    $c = $bmp.GetPixel($x, $y)
    if ($c.R -eq $bg.R -and $c.G -eq $bg.G -and $c.B -eq $bg.B) {
      $dst.SetPixel($x, $y, $card); $changed++
    } else {
      $dst.SetPixel($x, $y, $c)
    }
  }
}
$bmp.Dispose()
$dst.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$dst.Dispose()
"ok $out ($changed px rimappati)"
