param([int]$procId=0,[int]$ms=9000)
$p = Get-Process -Id $procId
$start = $p.TotalProcessorTime.TotalMilliseconds
$n = [int]($ms/300)
for($i=0;$i -lt $n;$i++){
  Start-Sleep -Milliseconds 300
  $p.Refresh()
  "{0,5:N0} ms  cpu={1,8:N0} ms" -f (($i+1)*300), $p.TotalProcessorTime.TotalMilliseconds
}
