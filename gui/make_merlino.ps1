Add-Type -AssemblyName System.Drawing
$src = [System.Drawing.Image]::FromFile((Join-Path (Get-Location) '../screen-it/page0_bg7.png'))
$bmp = New-Object System.Drawing.Bitmap 800,480
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
$g.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::AntiAliasGridFit
$g.DrawImage($src, 0, 0, 800, 480)
$f = New-Object System.Drawing.Font 'Consolas', 20, ([System.Drawing.FontStyle]::Bold)
$br = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(201, 212, 224))
$sf = New-Object System.Drawing.StringFormat
$sf.Alignment = [System.Drawing.StringAlignment]::Far
$g.DrawString('Merlino', $f, $br, (New-Object System.Drawing.RectangleF 596, 364, 194, 34), $sf)
$bmp.Save((Join-Path (Get-Location) '../screen-it/page0_merlino.png'), [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose(); $src.Dispose()
Get-Item '../screen-it/page0_merlino.png' | Select-Object Length
