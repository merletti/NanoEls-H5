param([string]$files = "screen-it/*_bg.png")
Add-Type -AssemblyName System.Drawing
$list = Get-ChildItem $files
foreach ($f in $list) {
  $bmp = [System.Drawing.Bitmap]::FromFile($f.FullName)
  $minY = 9999; $maxY = -1; $minX = 9999; $maxX = -1
  for ($y = 60; $y -lt 470; $y++) {
    for ($x = 470; $x -lt 795; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ([math]::Abs($p.R - 0x15) -le 2 -and [math]::Abs($p.G - 0x16) -le 2 -and [math]::Abs($p.B - 0x1A) -le 2) {
        if ($y -lt $minY) { $minY = $y }
        if ($y -gt $maxY) { $maxY = $y }
        if ($x -lt $minX) { $minX = $x }
        if ($x -gt $maxX) { $maxX = $x }
      }
    }
  }
  "{0,-28} card x{1}..{2} y{3}..{4}" -f $f.Name, $minX, $maxX, $minY, $maxY
  $bmp.Dispose()
}
