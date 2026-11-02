param([string]$src,[int]$x,[int]$y,[int]$w,[int]$h,[int]$s=4,[string]$out="gui/zoom.png")
Add-Type -AssemblyName System.Drawing
$b=[System.Drawing.Bitmap]::FromFile((Resolve-Path $src).Path)
$dst=New-Object System.Drawing.Bitmap ($w*$s),($h*$s)
$g=[System.Drawing.Graphics]::FromImage($dst)
$g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g.PixelOffsetMode=[System.Drawing.Drawing2D.PixelOffsetMode]::Half
$g.DrawImage($b,(New-Object System.Drawing.Rectangle 0,0,($w*$s),($h*$s)),(New-Object System.Drawing.Rectangle $x,$y,$w,$h),[System.Drawing.GraphicsUnit]::Pixel)
$dst.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose();$dst.Dispose();$b.Dispose()
"saved $out"
