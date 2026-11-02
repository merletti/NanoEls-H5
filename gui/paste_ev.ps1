param([string]$file)
Add-Type -AssemblyName System.Windows.Forms
$txt = [System.IO.File]::ReadAllText($file).TrimEnd()
Set-Clipboard -Value $txt
Start-Sleep -Milliseconds 300
[System.Windows.Forms.SendKeys]::SendWait('^a')
Start-Sleep -Milliseconds 200
[System.Windows.Forms.SendKeys]::SendWait('^v')
Start-Sleep -Milliseconds 800
"pasted $file ($($txt.Length) chars)"
