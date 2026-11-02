param([string]$src)
Add-Type -AssemblyName System.Drawing
$b = [System.Drawing.Bitmap]::FromFile($src)
$pts = @(@(0,0),@(20,10),@(1,30),@(400,5),@(18,20))
foreach ($p in $pts) {
  $c = $b.GetPixel($p[0], $p[1])
  "{0},{1} A={2} R={3} G={4} B={5}" -f $p[0], $p[1], $c.A, $c.R, $c.G, $c.B
}
$b.Dispose()
