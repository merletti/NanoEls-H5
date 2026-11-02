Add-Type -AssemblyName System.Drawing
$src = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5\screen-it\sprite_values.png"
$out = "C:\Users\Admin\Documents\Qoder\2026-10-30\dfa27f31\nanoels-h5\screen-it\sprite_values2.png"
$bmp = New-Object System.Drawing.Bitmap $src
$fg = [System.Drawing.Color]::FromArgb(255,242,242,242)
$bg = [System.Drawing.Color]::FromArgb(255,16,17,20)
$font = New-Object System.Drawing.Font("Arial Black",20,[System.Drawing.FontStyle]::Bold,[System.Drawing.GraphicsUnit]::Pixel)
$cell = New-Object System.Drawing.Bitmap 16,26
$g = [System.Drawing.Graphics]::FromImage($cell)
$g.TextRenderingHint=[System.Drawing.Text.TextRenderingHint]::AntiAlias
for($ascii=91; $ascii -le 126; $ascii++){
  $code = $ascii-32
  $cx = ($code % 50)*16; $cy = [math]::Floor($code/50)*26
  # clear cell
  for($y=0;$y -lt 26;$y++){ for($x=0;$x -lt 16;$x++){ $bmp.SetPixel($cx+$x,$cy+$y,$bg) } }
  $ch = [string][char]$ascii
  $g.Clear([System.Drawing.Color]::Black)
  $g.DrawString($ch,$font,[System.Drawing.Brushes]::White,0,-1)
  # threshold -> write into cell; compress horizontally if ink exceeds 16
  $minx=99;$maxx=-1
  for($y=0;$y -lt 26;$y++){ for($x=0;$x -lt 16;$x++){ $c=$cell.GetPixel($x,$y); if((($c.R+$c.G+$c.B)/3) -gt 128){ if($x -lt $minx){$minx=$x}; if($x -gt $maxx){$maxx=$x} } } }
  for($y=0;$y -lt 26;$y++){
    for($x=0;$x -lt 16;$x++){
      $sx=$x
      if($maxx -ge 16 -and $maxx -gt $minx){ $sx=[int][math]::Round($minx + ($x-$minx)*($maxx-$minx)/15.0) }
      if($sx -gt 15){$sx=15}
      $c=$cell.GetPixel($sx,$y)
      if((($c.R+$c.G+$c.B)/3) -gt 128){ $bmp.SetPixel($cx+$x,$cy+$y,$fg) }
    }
  }
}
$g.Dispose();$cell.Dispose();$font.Dispose()
$bmp.Save($out,[System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"OK $out"
