Add-Type -AssemblyName System.Drawing
function Sample($file, $points) {
  $bmp = [System.Drawing.Bitmap]::FromFile($file)
  foreach ($p in $points) {
    $c = $bmp.GetPixel($p[0], $p[1])
    $r = [int]($c.R -shr 3); $g = [int]($c.G -shr 2); $b = [int]($c.B -shr 3)
    $v = ($r -shl 11) -bor ($g -shl 5) -bor $b
    Write-Output ("{0} ({1},{2}) = #{3:X2}{4:X2}{5:X2} -> {6}" -f (Split-Path $file -Leaf), $p[0], $p[1], $c.R, $c.G, $c.B, $v)
  }
  $bmp.Dispose()
}
$base = "C:/Users/Admin/Documents/Qoder/2026-10-30/dfa27f31/nanoels-h5/gui/"
Sample ($base + "sim_gcode2_open.png") @(@(600,250),@(600,300),@(600,355),@(100,230),@(100,290),@(100,350))
Sample ($base + "sim_setup_open.png") @(@(200,200),@(400,300),@(150,190))
Sample ($base + "sim_wifi_open.png") @(@(60,280),@(300,280),@(60,240),@(700,260))
Sample ($base + "sim_comando_open.png") @(@(30,400),@(130,400),@(700,400),@(60,370))
