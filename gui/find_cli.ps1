$roots = @("$env:ProgramFiles\Arduino IDE", "$env:LOCALAPPDATA\Programs\Arduino IDE", "$env:USERPROFILE\Desktop", "$env:USERPROFILE\Documents", "$env:LOCALAPPDATA\Arduino15")
foreach ($r in $roots) {
  if (-not (Test-Path $r)) { "MANCA $r"; continue }
  $f = Get-ChildItem -Path $r -Recurse -Filter "arduino-cli*.exe" -ErrorAction SilentlyContinue | Select-Object -First 5 -ExpandProperty FullName
  if ($f) { "TROVATO in $r :"; $f } else { "nessun arduino-cli.exe in $r" }
}
