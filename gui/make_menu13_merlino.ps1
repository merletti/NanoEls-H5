Add-Type -AssemblyName System.Drawing
$srcPath = Join-Path (Get-Location) '../mockup-tft/home13.png'
$outPath = Join-Path (Get-Location) '../screen-it/menu13_merlino.png'
$src = [System.Drawing.Image]::FromFile($srcPath)
$bmp = New-Object System.Drawing.Bitmap 800,480
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
$g.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::AntiAliasGridFit
$g.DrawImage($src, 0, 0, 800, 480)
$f = New-Object System.Drawing.Font 'Segoe UI', 10.5, ([System.Drawing.FontStyle]::Bold)
$br = New-Object System.Drawing.SolidBrush ([System.Drawing.Color]::FromArgb(154, 160, 168))
$sf = New-Object System.Drawing.StringFormat
$sf.Alignment = [System.Drawing.StringAlignment]::Near
$g.DrawString('MERLINO', $f, $br, (New-Object System.Drawing.RectangleF 240, 37, 160, 16), $sf)
$bmp.Save($outPath, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose(); $src.Dispose()
