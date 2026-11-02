param([string]$files = "screen-it/*_bg.png")
Add-Type -AssemblyName System.Drawing
foreach ($f in (Get-ChildItem $files)) {
  $bmp = [System.Drawing.Bitmap]::FromFile($f.FullName)
  $minX = 9999; $maxX = -1; $minY = 9999; $maxY = -1; $c = 0
  for ($y = 358; $y -le 394; $y++) {
    for ($x = 470; $x -lt 800; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ([math]::Max($p.R, [math]::Max($p.G, $p.B)) -gt 70) {
        $c++
        if ($x -lt $minX) { $minX = $x }
        if ($x -gt $maxX) { $maxX = $x }
        if ($y -lt $minY) { $minY = $y }
        if ($y -gt $maxY) { $maxY = $y }
      }
    }
  }
  "{0,-28} ink n={1} x{2}..{3} y{4}..{5}" -f $f.Name, $c, $minX, $maxX, $minY, $maxY
  $bmp.Dispose()
}
