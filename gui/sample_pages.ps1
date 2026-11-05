Add-Type -AssemblyName System.Drawing
$base = "$PSScriptRoot\"
$files = @("sim_wifi_open.png","sim_comando_open.png","sim_setup_open.png","sim_scanalatura_open.png","sim_info_open.png","sim_gcode2_open.png")
$points = @{
  "sim_wifi_open.png" = @(@(300,150),@(300,230),@(200,290),@(360,290),@(300,350),@(600,300),@(300,120));
  "sim_comando_open.png" = @(@(60,300),@(300,300),@(60,395),@(300,395),@(60,100),@(200,100),@(700,100),@(60,220));
  "sim_setup_open.png" = @(@(100,150),@(400,150),@(700,150),@(100,300));
  "sim_scanalatura_open.png" = @(@(300,110),@(300,320),@(250,300),@(340,300),@(430,110),@(700,300));
  "sim_info_open.png" = @(@(200,120),@(600,120),@(200,400));
  "sim_gcode2_open.png" = @(@(200,130),@(200,200),@(200,330),@(600,240),@(600,300),@(600,360),@(200,90));
}
foreach ($f in $files) {
  $bmp = [System.Drawing.Bitmap]::FromFile($base + $f)
  foreach ($p in $points[$f]) {
    $c = $bmp.GetPixel($p[0], $p[1])
    $r = [int]($c.R -shr 3); $g = [int]($c.G -shr 2); $b = [int]($c.B -shr 3)
    $v = ($r -shl 11) -bor ($g -shl 5) -bor $b
    Write-Output ("{0} ({1},{2}) = #{3:X2}{4:X2}{5:X2} -> {6}" -f $f, $p[0], $p[1], $c.R, $c.G, $c.B, $v)
  }
  $bmp.Dispose()
}
