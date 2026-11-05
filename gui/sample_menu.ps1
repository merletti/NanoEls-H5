Add-Type -AssemblyName System.Drawing
$base = "$PSScriptRoot\..\"
$bmp = [System.Drawing.Bitmap]::FromFile($base + "screen-it/menu_bg.png")
foreach ($p in @(@(120,90),@(20,80),@(120,400),@(300,400),@(400,300),@(600,50),@(400,460))) {
  $c = $bmp.GetPixel($p[0], $p[1])
  $r = [int]($c.R -shr 3); $g = [int]($c.G -shr 2); $b = [int]($c.B -shr 3)
  $v = ($r -shl 11) -bor ($g -shl 5) -bor $b
  Write-Output ("({0},{1}) = #{2:X2}{3:X2}{4:X2} -> {5}" -f $p[0], $p[1], $c.R, $c.G, $c.B, $v)
}
$bmp.Dispose()
