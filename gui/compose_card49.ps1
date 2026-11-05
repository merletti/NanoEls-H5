$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$base = Join-Path (Split-Path $PSScriptRoot -Parent) 'screen-it'
$imp  = Join-Path $base 'import_card49'
$bak  = Join-Path $base 'backup-20261102\bg_before_card49'
New-Item -ItemType Directory -Force -Path $imp,$bak | Out-Null
$map = @(
  @{bg='ingranaggi_bg.png'; card='card_clean_ingranaggi.png'; out='01_ingranaggi_bg.png'},
  @{bg='filetto_bg.png';    card='card_clean_filetto.png';    out='02_filetto_bg.png'},
  @{bg='tornitura_bg.png';  card='card_clean_tornitura.png';  out='03_tornitura_bg.png'},
  @{bg='spianatura_bg.png'; card='card_clean_spianatura.png'; out='04_spianatura_bg.png'},
  @{bg='troncatura_bg.png'; card='card_clean_troncatura.png'; out='05_troncatura_bg.png'},
  @{bg='ellisse_bg.png';    card='card_clean_ellisse.png';    out='06_ellisse_bg.png'},
  @{bg='asincrono_bg.png';  card='card_clean_asincrono.png';  out='07_asincrono_bg.png'},
  @{bg='assey_bg.png';      card='card_clean_assey.png';      out='08_assey_bg.png'},
  @{bg='joystick_bg.png';   card='card_clean_joystick.png';   out='09_joystick_bg.png'},
  @{bg='xgear_bg.png';      card='card_clean_xgear.png';      out='10_xgear_bg.png'},
  @{bg='scanalatura_bg.png';card='card_clean_scanalatura.png';out='11_scanalatura_bg.png'}
)
foreach($m in $map){
  $bgp = Join-Path $base $m.bg
  if(-not (Test-Path $bgp)){ throw "manca $bgp" }
  $cardp = Join-Path $base $m.card
  if(-not (Test-Path $cardp)){ throw "manca $cardp" }
  Copy-Item $bgp (Join-Path $bak $m.bg) -Force
  $bg = [System.Drawing.Image]::FromFile($bgp)
  $card = [System.Drawing.Image]::FromFile($cardp)
  $bmp = New-Object System.Drawing.Bitmap($bg.Width, $bg.Height)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.DrawImage($bg, 0, 0)
  $g.DrawImage($card, 500, 74, 288, 358)
  $g.Dispose()
  $bmp.Save((Join-Path $imp $m.out), [System.Drawing.Imaging.ImageFormat]::Png)
  $bmp.Dispose(); $card.Dispose(); $bg.Dispose()
  Write-Host ("{0} + {1} -> {2}" -f $m.bg, $m.card, $m.out)
}
Write-Host "import: $imp"
