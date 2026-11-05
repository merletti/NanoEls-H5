$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$jpg  = Join-Path $PSScriptRoot 'contact_sheet.jpg'
$out  = Join-Path $PSScriptRoot 'pagine-tft-verifica-01.html'
$b64  = [Convert]::ToBase64String([IO.File]::ReadAllBytes($jpg))
$html = @"
<style>
#pagine-tft-verifica{font-family:var(--font-sans);color:var(--seed-fg);font-size:13px;line-height:1.5;max-width:1650px;margin:0 auto;padding:4px 0}
#pagine-tft-verifica .pt-head{font-size:16px;font-weight:500;letter-spacing:-.01em}
#pagine-tft-verifica .pt-sub{color:var(--seed-muted);font-size:12px;margin:2px 0 12px}
#pagine-tft-verifica .pt-frame{border:1px solid var(--border-standard);border-radius:10px;overflow:hidden;background:var(--inset-bg)}
#pagine-tft-verifica .pt-frame img{display:block;width:100%;height:auto}
#pagine-tft-verifica .pt-notes{display:grid;grid-template-columns:repeat(auto-fit,minmax(280px,1fr));gap:12px 20px;margin-top:14px}
#pagine-tft-verifica .pt-note{border-top:1px solid var(--border-subtle);padding-top:8px}
#pagine-tft-verifica .pt-lbl{font-size:12px;color:var(--seed-muted);margin-bottom:3px}
#pagine-tft-verifica .pt-txt{font-size:13px}
#pagine-tft-verifica .pt-txt b{font-weight:500}
#pagine-tft-verifica .pt-foot{margin-top:14px;font-size:12px;color:var(--seed-muted)}
#pagine-tft-verifica code{font-family:var(--font-code);font-size:12px;background:var(--fill-2);border-radius:4px;padding:0 4px}
</style>
<div id="pagine-tft-verifica">
  <div class="pt-head">Verifica di tutte le pagine del TFT &mdash; 22 schermate</div>
  <div class="pt-sub">Catture reali dal simulatore Nextion (800&times;480), dopo la riparazione dei clic sintetici. Ordine: 0 MENU &rarr; 21 LAVORAZIONE.</div>
  <div class="pt-frame"><img alt="Foglio di contatto con le 22 pagine del TFT" src="data:image/jpeg;base64,$b64"></div>
  <div class="pt-notes">
    <div class="pt-note"><div class="pt-lbl">Esito generale</div><div class="pt-txt"><b>22/22 pagine si aprono</b> e disegnano il contenuto previsto. Nessuna schermata bianca o corrotta.</div></div>
    <div class="pt-note"><div class="pt-lbl">Modalit&agrave; 1&ndash;12</div><div class="pt-txt">Campi e bordo cambio pagina corretti. La card a destra mostra ancora l'icona v48: normale, la card quotata v49 viene dipinta dal firmware sopra il fondo (<code>xpic 500,74,288,358</code>).</div></div>
    <div class="pt-note"><div class="pt-lbl">COMANDO 13 &middot; SETUP 14 &middot; WIFI 15</div><div class="pt-txt">Jog e tastierino presenti; SETUP con le 6 voci; WIFI con SSID, IP e i due pulsanti.</div></div>
    <div class="pt-note"><div class="pt-lbl">INFO 16</div><div class="pt-txt">Da controllare solo a runtime: &ldquo;H3V2&rdquo;, 192.168.1.50 e 02:14:37 sono valori di esempio nell'HMI, sovrascritti dal firmware con H5V46 e IP reale.</div></div>
    <div class="pt-note"><div class="pt-lbl">SCANALATURA 17 &middot; TASTIERO 18</div><div class="pt-txt">Campi, direzione AVANTI, FINE CORSA 206.00; tastierino con display, OK/ANNULLA e cancellazione.</div></div>
    <div class="pt-note"><div class="pt-lbl">PANNELLI 19 &middot; TASTIERA 20</div><div class="pt-txt"><b>Nere per progetto.</b> Le dipinge il firmware (<code>TFT_PANEL_PAGE 19</code>, <code>TFT_KEYBOARD_PAGE 20</code>): senza firmware, nel simulatore restano vuote.</div></div>
    <div class="pt-note"><div class="pt-lbl">LAVORAZIONE 21</div><div class="pt-txt"><b>Corretta.</b> PASSATE, ASSE X/Y/Z, SENSO SX con passata a 1.500, pulsanti Z&minus;/Z+/X&minus;/X+. &Egrave; la pagina aperta da AVVIA.</div></div>
    <div class="pt-note"><div class="pt-lbl">Limite della verifica</div><div class="pt-txt">Il simulatore non esegue il firmware: card quotate, PANNELLI, TASTIERA e valori live di INFO vanno confermati a banco con il controller acceso.</div></div>
  </div>
  <div class="pt-foot">Fonti: gui/pages/page00.png &hellip; page21.png, composti in gui/contact_sheet.png.</div>
</div>
"@
[IO.File]::WriteAllText($out, $html, (New-Object Text.UTF8Encoding($false)))
Write-Host "scritto $out ($((Get-Item $out).Length) byte)"
