param([string]$text = "1.500", [string]$out = "gui/keypad_preview.png")
Add-Type -AssemblyName System.Drawing
$bgPath = (Resolve-Path "screen-it/tastiera_bg.png").Path
$spPath = (Resolve-Path "screen-it/sprite_keypad.png").Path
$bg = [System.Drawing.Bitmap]::FromFile($bgPath)
$sp = [System.Drawing.Bitmap]::FromFile($spPath)
$g = [System.Drawing.Graphics]::FromImage($bg)
$black = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::Black)
$g.FillRectangle($black, 13, 79, 773, 102)
$gw = 32; $gh = 52; $cols = 50; $right = 768; $y = 104
$n = $text.Length
$left = $right - $n * $gw
for($i = 0; $i -lt $n; $i++){
  $code = [int][char]$text[$i] - 32
  if($code -lt 0 -or $code -gt 58){ continue }
  $sx = ($code % $cols) * $gw
  $sy = [math]::Floor($code / $cols) * $gh
  $dst = New-Object System.Drawing.Rectangle (($left + $i * $gw), $y, $gw, $gh)
  $src = New-Object System.Drawing.Rectangle ($sx, $sy, $gw, $gh)
  $g.DrawImage($sp, $dst, $src, [System.Drawing.GraphicsUnit]::Pixel)
}
$bg.Save((Join-Path (Get-Location) $out), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bg.Dispose(); $sp.Dispose()
"left=$left glyphs=$n"
