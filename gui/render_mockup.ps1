param([string]$html = "mockup-tft\lavorazione.html", [string]$png = "mockup-tft\lavorazione.png")
$root = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5"
$chrome = "C:\Program Files\Google\Chrome\Application\chrome.exe"
$url = "file:///" + ((Join-Path $root $html) -replace '\\','/')
$out = Join-Path $root $png
& $chrome --headless=new --disable-gpu --hide-scrollbars --window-size=800,480 --screenshot=$out $url 2>$null | Out-Null
if (-not (Test-Path $out)) { throw "render fallito: $html" }
Add-Type -AssemblyName System.Drawing
$bmp = [System.Drawing.Bitmap]::FromFile($out)
"$png $($bmp.Width)x$($bmp.Height)"
$bmp.Dispose()
