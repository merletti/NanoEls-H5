Add-Type -AssemblyName System.Drawing
foreach ($n in @('page13','page14','page15','page18','page19')) {
  $p = 'C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5\gui\pages\' + $n + '.png'
  if (!(Test-Path $p)) { Write-Output "$n missing"; continue }
  $i = [System.Drawing.Bitmap]::FromFile($p)
  $c = $i.GetPixel(400,465)
  $d = $i.GetPixel(400,300)
  Write-Output ("{0} footer=#{1:X2}{2:X2}{3:X2} body=#{4:X2}{5:X2}{6:X2}" -f $n,$c.R,$c.G,$c.B,$d.R,$d.G,$d.B)
  $i.Dispose()
}
