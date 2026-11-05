$roots = @($env:ProgramFiles,"${env:ProgramFiles(x86)}",$env:LOCALAPPDATA,$env:APPDATA,"$env:USERPROFILE\Desktop","$env:USERPROFILE\Downloads","$env:USERPROFILE\Documents")
foreach($r in $roots){
  Get-ChildItem $r -Filter '*Nextion*' -Recurse -ErrorAction SilentlyContinue -Depth 3 |
    Select-Object -First 30 FullName, Length
}
Get-ChildItem "$env:APPDATA\Microsoft\Windows\Start Menu" -Recurse -Filter '*Nextion*' -ErrorAction SilentlyContinue | Select-Object FullName
