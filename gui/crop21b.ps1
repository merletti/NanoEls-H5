Add-Type -AssemblyName System.Drawing
$src = [System.Drawing.Bitmap]::FromFile('C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5\gui\pages\page21.png')
$rect = New-Object System.Drawing.Rectangle -ArgumentList 0, 120, 270, 200
$crop = $src.Clone($rect, $src.PixelFormat)
$big = New-Object System.Drawing.Bitmap 810, 600
$g = [System.Drawing.Graphics]::FromImage($big)
$g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g.DrawImage($crop, 0, 0, 810, 600)
$big.Save('C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5\gui\_crop21_xcard.png', [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $big.Dispose(); $crop.Dispose(); $src.Dispose()
