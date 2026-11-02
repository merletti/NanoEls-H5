param([string]$src, [string]$dst)
$fs = [System.IO.File]::Open($src, [System.IO.FileMode]::Open, [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite)
$out = [System.IO.File]::Create($dst)
$fs.CopyTo($out)
$out.Close(); $fs.Close()
"ok $dst"
