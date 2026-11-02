Add-Type -AssemblyName System.Drawing
$names=@(
 @('page01','INGRANAGGI (pic 48)'),
 @('page02','FILETTATURA (pic 49)'),
 @('page03','TORNITURA (pic 50)'),
 @('page04','SPIANATURA (pic 51)'),
 @('page06','TRONCATURA (pic 52)'),
 @('page07','ELLISSE (pic 53)'),
 @('page08','ASINCRONO (pic 54)'),
 @('page10','ASSE Y (pic 55)'),
 @('page11','JOYSTICK (pic 56)'),
 @('page12','X-INGRANAGGI (pic 57)'),
 @('page17','SCANALATURA (pic 58)'),
 @('page05','CONO (pic 41, invariata)'),
 @('page09','GCODE (pic 13, invariata)')
)
$cw=400; $ch=240; $lbl=20; $cols=3; $rows=[math]::Ceiling($names.Count/$cols)
$sheet=New-Object System.Drawing.Bitmap(($cw*$cols), (($ch+$lbl)*$rows))
$g=[System.Drawing.Graphics]::FromImage($sheet)
$g.Clear([System.Drawing.Color]::FromArgb(30,30,30))
$g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
$font=New-Object System.Drawing.Font('Segoe UI',11,[System.Drawing.FontStyle]::Bold)
$brush=[System.Drawing.Brushes]::White
for($i=0;$i -lt $names.Count;$i++){
  $col=$i % $cols; $row=[math]::Floor($i / $cols)
  $x=$col*$cw; $y=$row*($ch+$lbl)
  $img=[System.Drawing.Image]::FromFile((Join-Path (Get-Location) ("gui/pages/"+$names[$i][0]+".png")))
  $dst=New-Object System.Drawing.Rectangle -ArgumentList $x,($y+$lbl),$cw,$ch
  $g.DrawImage($img, $dst)
  $g.DrawString($names[$i][1], $font, $brush, [single]($x+6), [single]($y+2))
  $img.Dispose()
}
$sheet.Save((Join-Path (Get-Location) 'gui/_sheet_cards.png'),[System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $sheet.Dispose()
'sheet ok'
