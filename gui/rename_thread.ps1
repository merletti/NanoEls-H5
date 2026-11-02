Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Drawing.Drawing2D

$fmt = [System.Drawing.StringFormat]::GenericTypographic

function DrawSpaced($g, $text, $font, $brush, [double]$x, [double]$y, [double]$spacing) {
  foreach ($ch in $text.ToCharArray()) {
    if ($ch -eq ' ') { $x += $font.Size * 0.278 + $spacing; continue }
    $s = [string]$ch
    $g.DrawString($s, $font, $brush, [float]$x, [float]$y, $fmt)
    $m = $g.MeasureString($s, $font, 1000, $fmt)
    $x += $m.Width + $spacing
  }
}

function TextWidth($g, $text, $font, [double]$spacing) {
  $w = 0.0
  foreach ($ch in $text.ToCharArray()) {
    if ($ch -eq ' ') { $w += $font.Size * 0.278 + $spacing; continue }
    $w += $g.MeasureString([string]$ch, $font, 1000, $fmt).Width + $spacing
  }
  return $w - $spacing
}

function NewCtx($path, $format) {
  $src = [System.Drawing.Image]::FromFile((Resolve-Path $path))
  $bmp = New-Object System.Drawing.Bitmap $src.Width, $src.Height, $format
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
  $g.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::AntiAliasGridFit
  $g.DrawImage($src, 0, 0, $src.Width, $src.Height)
  $src.Dispose()
  return @($bmp, $g)
}

$root = (Get-Location).Path
$filetto = '../screen-it/filetto_bg.png'
$menu = '../screen-it/menu13_merlino.png'
$filettoPre = '../screen-it/filetto_bg_preFILETTATURA.png'
$menuPre = '../screen-it/menu13_merlino_preFILETTATURA.png'
if (-not (Test-Path $filettoPre)) { Copy-Item $filetto $filettoPre -Force }
if (-not (Test-Path $menuPre)) { Copy-Item $menu $menuPre -Force }
$filettoSrc = $filettoPre
$menuSrc = $menuPre

# ---------- FILETTO page ----------
$r = NewCtx $filettoSrc ([System.Drawing.Imaging.PixelFormat]::Format24bppRgb)
$bmp = $r[0]; $g = $r[1]
$bgPage = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(10, 10, 12))
$bgCard = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(21, 22, 26))
$bgChip = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(28, 29, 34))
$bgStrip = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(16, 17, 20))
$ink = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(242, 242, 242))
$inkChip = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(154, 160, 168))
$inkStrip = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(168, 173, 180))

# big title
$g.FillRectangle($bgPage, 8, 10, 300, 38)
$fTitle = New-Object System.Drawing.Font 'Arial', 26, ([System.Drawing.FontStyle]::Bold), ([System.Drawing.GraphicsUnit]::Pixel)
DrawSpaced $g 'FILETTATURA' $fTitle $ink 12 18 0.8

# header chip
$g.FillRectangle($bgChip, 620, 33, 72, 24)
$fChip = New-Object System.Drawing.Font 'Arial', 9, ([System.Drawing.FontStyle]::Bold), ([System.Drawing.GraphicsUnit]::Pixel)
$wChip = TextWidth $g 'FILETTATURA' $fChip 0.3
DrawSpaced $g 'FILETTATURA' $fChip $inkChip (652 - $wChip / 2) 35 0.3

# side card title
$g.FillRectangle($bgCard, 505, 197, 270, 27)
$fSide = New-Object System.Drawing.Font 'Arial', 21, ([System.Drawing.FontStyle]::Bold), ([System.Drawing.GraphicsUnit]::Pixel)
$wSide = TextWidth $g 'FILETTATURA' $fSide 0.7
DrawSpaced $g 'FILETTATURA' $fSide $ink (643.5 - $wSide / 2) 198 0.7

# strip
$g.FillRectangle($bgStrip, 10, 458, 330, 20)
$fStrip = New-Object System.Drawing.Font 'Arial', 12, ([System.Drawing.FontStyle]::Regular), ([System.Drawing.GraphicsUnit]::Pixel)
DrawSpaced $g ("FILETTATURA " + [char]0x00B7 + " F2 " + [char]0x00B7 + " passo 1.750 mm") $fStrip $inkStrip 13 460 0

$bmp.Save((Join-Path $root '../screen-it/filetto_bg.png'), [System.Drawing.Imaging.ImageFormat]::Png)
"filetto chip width=$([math]::Round($wChip,1)) side width=$([math]::Round($wSide,1))"
$g.Dispose(); $bmp.Dispose()

# ---------- MENU card ----------
$r2 = NewCtx $menuSrc ([System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
$bmp2 = $r2[0]; $g2 = $r2[1]
$bgCard2 = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(21, 22, 26))
$ink2 = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(242, 242, 242))
$fMenu = New-Object System.Drawing.Font 'Arial', 14, ([System.Drawing.FontStyle]::Bold), ([System.Drawing.GraphicsUnit]::Pixel)
$g2.FillRectangle($bgCard2, 176, 108, 136, 22)
DrawSpaced $g2 'FILETTATURA' $fMenu $ink2 181 110 0.3
$bmp2.Save((Join-Path $root '../screen-it/menu13_merlino.png'), [System.Drawing.Imaging.ImageFormat]::Png)
$g2.Dispose(); $bmp2.Dispose()
'ok'
