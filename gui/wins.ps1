Get-Process | Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object Id,ProcessName,MainWindowTitle | Format-Table -AutoSize | Out-String -Width 200
