param([string]$file, [string]$hex)
Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap((Join-Path (Get-Location) $file))
$w = $bmp.Width; $h = $bmp.Height
$target = [int]$hex
$seen = New-Object 'bool[]' ($w * $h)
$boxes = @()
for($y = 0; $y -lt $h; $y++){
  for($x = 0; $x -lt $w; $x++){
    $i = $y * $w + $x
    if($seen[$i]){ continue }
    if($bmp.GetPixel($x,$y).ToArgb() -ne [System.Drawing.Color]::FromArgb(255, (($target -shr 16) -band 255), (($target -shr 8) -band 255), ($target -band 255)).ToArgb()){
      $seen[$i] = $true; continue
    }
    $stack = New-Object System.Collections.Stack
    $stack.Push(@($x,$y))
    $seen[$i] = $true
    $minx=$x; $maxx=$x; $miny=$y; $maxy=$y; $count=0
    while($stack.Count -gt 0){
      $p = $stack.Pop(); $px=$p[0]; $py=$p[1]; $count++
      if($px -lt $minx){$minx=$px}; if($px -gt $maxx){$maxx=$px}
      if($py -lt $miny){$miny=$py}; if($py -gt $maxy){$maxy=$py}
      foreach($d in @(@(1,0),@(-1,0),@(0,1),@(0,-1))){
        $nx=$px+$d[0]; $ny=$py+$d[1]
        if($nx -lt 0 -or $ny -lt 0 -or $nx -ge $w -or $ny -ge $h){ continue }
        $ni = $ny * $w + $nx
        if($seen[$ni]){ continue }
        $c = $bmp.GetPixel($nx,$ny)
        if($c.ToArgb() -ne [System.Drawing.Color]::FromArgb(255, (($target -shr 16) -band 255), (($target -shr 8) -band 255), ($target -band 255)).ToArgb()){ $seen[$ni]=$true; continue }
        $seen[$ni] = $true
        $stack.Push(@($nx,$ny))
      }
    }
    if($count -ge 60){ $boxes += [pscustomobject]@{x=$minx; y=$miny; w=($maxx-$minx+1); h=($maxy-$miny+1); n=$count} }
  }
}
$bmp.Dispose()
$boxes | Sort-Object -Property y,x | ForEach-Object { "x={0} y={1} w={2} h={3} n={4}" -f $_.x,$_.y,$_.w,$_.h,$_.n }
