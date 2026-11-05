Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::FromFile("$PSScriptRoot\pages\page21.png")
$pts = @(
  @{n='bg-footer'; x=400; y=465},
  @{n='bg-left-giri'; x=180; y=340},
  @{n='bg-mid-pastata'; x=420; y=340},
  @{n='mode-field'; x=550; y=25},
  @{n='passo-field'; x=100; y=90},
  @{n='axisX-card'; x=100; y=200},
  @{n='stato-card'; x=650; y=330},
  @{n='stato-bigbox'; x=650; y=370},
  @{n='senso-field'; x=530; y=90},
  @{n='top-blue-line'; x=550; y=13}
)
foreach ($p in $pts) {
  $c = $img.GetPixel($p.x, $p.y)
  $hex = '#{0:X2}{1:X2}{2:X2}' -f $c.R, $c.G, $c.B
  $rgb565 = (($c.R -shr 3) -shl 11) -bor (($c.G -shr 2) -shl 5) -bor ($c.B -shr 3)
  Write-Output ("{0,-16} ({1,3},{2,3}) {3}  rgb565={4}" -f $p.n, $p.x, $p.y, $hex, $rgb565)
}
$img.Dispose()
