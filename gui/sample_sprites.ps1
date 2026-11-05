Add-Type -AssemblyName System.Drawing
$files = @(
  "$PSScriptRoot\..\screen-it\sprite_values.png",
  "$PSScriptRoot\..\screen-it\sprite_values2.png",
  "$PSScriptRoot\..\screen-it\sprite_values_card.png"
)
foreach ($f in $files) {
  if (!(Test-Path $f)) { Write-Output "MISSING $f"; continue }
  $img = [System.Drawing.Bitmap]::FromFile($f)
  $c = $img.GetPixel(0,0)
  $c2 = $img.GetPixel(3,3)
  $hex = '#{0:X2}{1:X2}{2:X2}' -f $c.R,$c.G,$c.B
  $hex2 = '#{0:X2}{1:X2}{2:X2}' -f $c2.R,$c2.G,$c2.B
  Write-Output ("{0} {1}x{2} px(0,0)={3} px(3,3)={4}" -f [System.IO.Path]::GetFileName($f), $img.Width, $img.Height, $hex, $hex2)
  $img.Dispose()
}
