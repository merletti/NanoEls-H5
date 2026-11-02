param([switch]$Kill)
$procs = Get-Process 'Nextion Editor' -ErrorAction SilentlyContinue
foreach ($p in $procs) {
  if ($Kill) { $p.Kill() } else { $p.CloseMainWindow() | Out-Null }
}
Start-Sleep -Seconds 2
$still = Get-Process 'Nextion Editor' -ErrorAction SilentlyContinue
if ($still) { "ANCORA APERTO: " + (($still | ForEach-Object { $_.Id }) -join ',') } else { "chiuso" }
