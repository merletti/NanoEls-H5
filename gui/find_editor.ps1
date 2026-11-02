$roots = @('C:\Program Files','C:\Program Files (x86)','C:\Users\Admin\AppData\Local','C:\Users\Admin\AppData\Roaming','C:\Users\Admin\Desktop','C:\Users\Admin\Downloads','C:\Users\Admin\Documents')
foreach($r in $roots){
  Get-ChildItem $r -Filter '*Nextion*' -Recurse -ErrorAction SilentlyContinue -Depth 3 |
    Select-Object -First 30 FullName, Length
}
Get-ChildItem 'C:\Users\Admin\AppData\Roaming\Microsoft\Windows\Start Menu' -Recurse -Filter '*Nextion*' -ErrorAction SilentlyContinue | Select-Object FullName
