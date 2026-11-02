param([string]$root = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5")
Add-Type -AssemblyName System.Drawing

$mp = Join-Path $root "mockup-tft"
$ids = Get-Content (Join-Path $mp "card_clean\order.txt")
$h = 358
$groups = @{ "a" = 0..4; "b" = 5..9; "c" = 10..10 }

foreach ($k in @("a","b","c")) {
  $idx = $groups[$k]
  $strip = New-Object System.Drawing.Bitmap(288, ($h * $idx.Count))
  $g = [System.Drawing.Graphics]::FromImage($strip)
  $j = 0
  foreach ($i in $idx) {
    $id = $ids[$i]
    $card = [System.Drawing.Bitmap]::FromFile((Join-Path $root ("screen-it\card_clean_" + $id + ".png")))
    $g.DrawImage($card, 0, ($j * $h))
    $card.Dispose()
    $j++
  }
  $g.Dispose()
  $strip.Save((Join-Path $root ("screen-it\card_strip_" + $k + ".png")), [System.Drawing.Imaging.ImageFormat]::Png)
  "card_strip_$k $($strip.Width)x$($strip.Height) slots $($idx -join ',')"
  $strip.Dispose()
}
