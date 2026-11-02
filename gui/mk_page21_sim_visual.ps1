param([string]$out)
$img = [Convert]::ToBase64String([IO.File]::ReadAllBytes('gui/sim_page21_canvas.png'))
$html = @"
<div style="font-family:Segoe UI,Arial,sans-serif;background:#0c0d10;color:#e8eaee;padding:18px;border-radius:12px">
  <div style="font-size:19px;font-weight:600;margin-bottom:4px">Pagina 21 — LAVORAZIONE (simulatore Nextion)</div>
  <div style="font-size:13px;color:#9aa3ad;margin-bottom:12px">Cattura reale del simulatore dopo <code style="color:#e8eaee">page 21</code> · i riquadri restano vuoti perché a disegnarli è il firmware via seriale</div>
  <img src="data:image/png;base64,$img" width="800" height="480" style="display:block;border:1px solid #2a2f38;border-radius:6px">
</div>
"@
[IO.File]::WriteAllText($out, $html, (New-Object System.Text.UTF8Encoding($false)))
"ok $out"
