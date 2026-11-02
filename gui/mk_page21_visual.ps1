param([string]$out)
$bg = [Convert]::ToBase64String([IO.File]::ReadAllBytes('screen-it/lavorazione_tft_bg.png'))
$mk = [Convert]::ToBase64String([IO.File]::ReadAllBytes('mockup-tft/lavorazione_tft.png'))
$html = @"
<div style="font-family:Segoe UI,Arial,sans-serif;background:#0c0d10;color:#e8eaee;padding:18px;border-radius:12px">
  <div style="font-size:19px;font-weight:600;margin-bottom:4px">Pagina 21 — LAVORAZIONE</div>
  <div style="font-size:13px;color:#9aa3ad;margin-bottom:16px">Nextion 800×480 · sfondo = picture 47 · nessun componente: i valori li scrive il firmware via seriale</div>

  <div style="font-size:13px;color:#c8ced6;margin:0 0 6px 2px">1 · La pagina come sta nel TFT (solo sfondo)</div>
  <img src="data:image/png;base64,$bg" width="800" height="480" style="display:block;border:1px solid #2a2f38;border-radius:6px">

  <div style="font-size:13px;color:#c8ced6;margin:22px 0 6px 2px">2 · Con i valori vivi che il firmware disegna sopra (prova grafica, valori di esempio)</div>
  <img src="data:image/png;base64,$mk" width="800" height="480" style="display:block;border:1px solid #2a2f38;border-radius:6px">
</div>
"@
[IO.File]::WriteAllText($out, $html, (New-Object System.Text.UTF8Encoding($false)))
"ok $out"
