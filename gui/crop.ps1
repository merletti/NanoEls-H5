param([string]$src,[string]$out,[int]$xx,[int]$yy,[int]$ww,[int]$hh,[int]$zoom=3)
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile($src)
$rect = New-Object System.Drawing.Rectangle($xx,$yy,$ww,$hh)
$crop = $bmp.Clone($rect, $bmp.PixelFormat)
$bw = $ww * $zoom
$bh = $hh * $zoom
$big = New-Object System.Drawing.Bitmap($bw, $bh)
$g = [System.Drawing.Graphics]::FromImage($big)
$g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
$g.DrawImage($crop, 0, 0, $bw, $bh)
$g.Dispose()
$big.Save($out, [System.Drawing.Imaging.ImageFormat]::Png)
$big.Dispose(); $crop.Dispose(); $bmp.Dispose()
"ok $out"
