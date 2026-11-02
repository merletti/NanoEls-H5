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
$base = "C:/Users/Admin/Documents/Qoder/2026-10-30/dfa27f31/nanoels-h5/screen-it/"
Sample ($base + "ingranaggi_bg.png") @(@(400,300),@(300,100),@(640,300),@(700,310),@(50,460))
Sample ($base + "scanalatura_bg.png") @(@(400,300),@(250,310),@(400,460),@(400,320))
Sample ($base + "menu_bg.png") @(@(400,60),@(700,30),@(750,37),@(300,200))
