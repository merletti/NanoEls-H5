param([string]$root = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5")
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile((Join-Path $root "screen-it\card_clean_ingranaggi.png"))
$pts = @(
  @{n="card angolo";  x=8;   y=8},
  @{n="chip interno"; x=150; y=98},
  @{n="box dim";      x=160; y=215},
  @{n="box ridotto";  x=150; y=330},
  @{n="riga stato";   x=100; y=278}
)
foreach ($p in $pts) {
  $c = $bmp.GetPixel($p.x, $p.y)
  "{0}: #{1:X2}{2:X2}{3:X2}" -f $p.n, $c.R, $c.G, $c.B
}
$bmp.Dispose()
