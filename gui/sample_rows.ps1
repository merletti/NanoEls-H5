param()
Add-Type -AssemblyName System.Drawing
function Px($p,$x,$y){
  $b=New-Object System.Drawing.Bitmap((Join-Path (Get-Location) $p))
  $c=$b.GetPixel($x,$y)
  "{0} ({1},{2}) = #{3:X2}{4:X2}{5:X2}" -f $p,$x,$y,$c.R,$c.G,$c.B
  $b.Dispose()
}
"--- page13 COMANDO ---"
foreach($p in @(@(40,100),@(350,100),@(500,100),@(100,210),@(400,210),@(700,210),@(60,92),@(690,30))){ Px "gui/pages/page13.png" $p[0] $p[1] }
"--- page15 WIFI ---"
foreach($p in @(@(100,150),@(100,225),@(100,340),@(100,365),@(640,230),@(640,260),@(640,285))){ Px "gui/pages/page15.png" $p[0] $p[1] }
"--- page16 INFO ---"
foreach($p in @(@(100,120),@(500,120),@(100,245),@(500,245),@(100,370),@(500,370))){ Px "gui/pages/page16.png" $p[0] $p[1] }
"--- page00 MENU chip ---"
foreach($p in @(@(690,25),@(730,40),@(760,40))){ Px "gui/pages/page00.png" $p[0] $p[1] }
