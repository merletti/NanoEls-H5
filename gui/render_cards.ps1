param([string]$root = (Split-Path $PSScriptRoot -Parent))
Add-Type -AssemblyName System.Drawing

$chrome = "$env:ProgramFiles\Google\Chrome\Application\chrome.exe"
$mp = Join-Path $root "mockup-tft"
$ids = Get-Content (Join-Path $mp "card_clean\order.txt")
$cards = @()

foreach ($id in $ids) {
  $png = Join-Path $env:TEMP ("card_" + $id + ".png")
  $url = "file:///" + ((Join-Path $mp ("card_clean\" + $id + ".html")) -replace '\\','/')
  & $chrome --headless=new --disable-gpu --hide-scrollbars --window-size=800,480 --screenshot=$png $url 2>$null | Out-Null
  if (-not (Test-Path $png)) { throw "render fallito: $id" }

  $bmp = [System.Drawing.Bitmap]::FromFile($png)
  if ($bmp.Width -ne 800 -or $bmp.Height -ne 480) { "ATTENZIONE $id : $($bmp.Width)x$($bmp.Height)" }

  # card bounding box = pixels of the card colour #15161A inside the right column
  $minX = 9999; $maxX = -1; $minY = 9999; $maxY = -1
  for ($y = 60; $y -lt 470; $y++) {
    for ($x = 470; $x -lt 795; $x++) {
      $p = $bmp.GetPixel($x, $y)
      if ([math]::Abs($p.R - 0x15) -le 2 -and [math]::Abs($p.G - 0x16) -le 2 -and [math]::Abs($p.B - 0x1A) -le 2) {
        if ($y -lt $minY) { $minY = $y }; if ($y -gt $maxY) { $maxY = $y }
        if ($x -lt $minX) { $minX = $x }; if ($x -gt $maxX) { $maxX = $x }
      }
    }
  }
  if ($minX -ne 501 -or $minY -ne 75) { "ATTENZIONE $id : card x$minX..$maxX y$minY..$maxY (ritaglio fisso 500,74)" }
  $minX = 500; $minY = 74; $maxX = 787; $maxY = 431

  $card = $bmp.Clone([System.Drawing.Rectangle]::new($minX, $minY, ($maxX - $minX + 1), ($maxY - $minY + 1)), $bmp.PixelFormat)
  $card.Save((Join-Path $root ("screen-it\card_clean_" + $id + ".png")), [System.Drawing.Imaging.ImageFormat]::Png)
  $cards += ,$card
  $bmp.Dispose()
  "$id card $($card.Width)x$($card.Height) a $minX,$minY"
}

$w = $cards[0].Width; $h = $cards[0].Height
$strip = New-Object System.Drawing.Bitmap($w, ($h * $cards.Count))
$g = [System.Drawing.Graphics]::FromImage($strip)
for ($i = 0; $i -lt $cards.Count; $i++) { $g.DrawImage($cards[$i], 0, ($i * $h)) }
$g.Dispose()
$strip.Save((Join-Path $root "screen-it\card_strip.png"), [System.Drawing.Imaging.ImageFormat]::Png)
"strip $($strip.Width)x$($strip.Height)"
$strip.Dispose()
