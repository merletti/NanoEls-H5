param([string]$out="gui/contact_sheet.png",[int]$cols=4,[int]$tw=400,[int]$th=240,[int]$pad=10,[int]$lab=22,[int]$count=22)
Add-Type -AssemblyName System.Drawing
$rows=[Math]::Ceiling($count/$cols)
$W=$cols*($tw+$pad)+$pad
$H=$rows*($th+$lab+$pad)+$pad
$sheet=New-Object System.Drawing.Bitmap($W,$H)
$g=[System.Drawing.Graphics]::FromImage($sheet)
$g.Clear([System.Drawing.Color]::FromArgb(12,13,16))
$g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
$font=New-Object System.Drawing.Font("Consolas",11)
$brush=[System.Drawing.Brushes]::WhiteSmoke
$names=@("MENU","INGRANAGGI","FILETTATURA","TORNITURA","SPIANATURA","CONO","TRONCATURA","ELLISSE","ASINCRONO","GCODE","ASSE Y","JOYSTICK","X-INGRANAGGI","COMANDO","SETUP","WIFI","INFO","SCANALATURA","TASTIERO","PANNELLI","TASTIERA","LAVORAZIONE")
for($i=0;$i -lt $count;$i++){
  $r=[Math]::Floor($i/$cols); $c=$i % $cols
  $x=$pad+$c*($tw+$pad); $y=$pad+$r*($th+$lab+$pad)
  $f=("gui/pages/page{0:00}.png" -f $i)
  if(Test-Path $f){
    $img=[System.Drawing.Image]::FromFile((Resolve-Path $f))
    $g.DrawImage($img,$x,$y,$tw,$th)
    $img.Dispose()
  }
  $g.DrawString(("{0:00}  {1}" -f $i,$names[$i]),$font,$brush,$x,$y+$th+2)
}
$g.Dispose()
$sheet.Save((Join-Path (Get-Location) $out),[System.Drawing.Imaging.ImageFormat]::Png)
$sheet.Dispose()
"ok $out $W x $H"
