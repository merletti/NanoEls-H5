param([string]$dir = "C:/Users/Admin/Documents/Qoder/2026-10-30/dfa27f31/nanoels-h5/screen-it")
Add-Type -AssemblyName System.Drawing
$files = @("ingranaggi_bg.png","filetto_bg.png","tornitura_bg.png","spianatura_bg.png","cono_bg.png","troncatura_bg.png","ellisse_bg.png","asincrono_bg.png","gcode_bg.png","assey_bg.png","joystick_bg.png","xgear_bg.png")
foreach($f in $files){
  $p = Join-Path $dir $f
  if(-not (Test-Path $p)){ Write-Output "$f MISSING"; continue }
  $bmp = [System.Drawing.Bitmap]::FromFile($p)
  $x0=690; $y0=0; $x1=[Math]::Min($bmp.Width-1,799); $y1=[Math]::Min($bmp.Height-1,90)
  $minX=99999; $minY=99999; $maxX=-1; $maxY=-1
  for($y=$y0;$y -le $y1;$y++){
    for($x=$x0;$x -le $x1;$x++){
      $c = $bmp.GetPixel($x,$y)
      $lum = ($c.R*0.299 + $c.G*0.587 + $c.B*0.114)
      if($lum -gt 45){
        if($x -lt $minX){$minX=$x}; if($x -gt $maxX){$maxX=$x}
        if($y -lt $minY){$minY=$y}; if($y -gt $maxY){$maxY=$y}
      }
    }
  }
  Write-Output ("{0,-20} {1}x{2}  bbox=({3},{4})-({5},{6})  w={7} h={8}" -f $f,$bmp.Width,$bmp.Height,$minX,$minY,$maxX,$maxY,($maxX-$minX+1),($maxY-$minY+1))
  $bmp.Dispose()
}
