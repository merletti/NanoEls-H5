param([string]$src,[int]$px,[int]$py)
Add-Type -AssemblyName System.Drawing
$b=[System.Drawing.Bitmap]::FromFile((Resolve-Path $src).Path)
"size $($b.Width)x$($b.Height)"
$c1=$b.GetPixel($px,$py)
"({0},{1}) = #{2:X2}{3:X2}{4:X2}" -f $px,$py,$c1.R,$c1.G,$c1.B
$c2=$b.GetPixel(($px+2),$py)
"({0},{1}) = #{2:X2}{3:X2}{4:X2}" -f ($px+2),$py,$c2.R,$c2.G,$c2.B
$c3=$b.GetPixel(($px+8),$py)
"({0},{1}) = #{2:X2}{3:X2}{4:X2}" -f ($px+8),$py,$c3.R,$c3.G,$c3.B
$b.Dispose()
