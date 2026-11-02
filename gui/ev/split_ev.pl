use strict; use warnings;
my $dir = "gui/ev";
for my $path (glob("$dir/*_touch.txt")) {
    open my $fh, '<', $path or die $!;
    my @lines = <$fh>; close $fh;
    my @out;
    for my $l (@lines) {
        chomp $l;
        next if $l =~ /^\s*$/;
        if ($l =~ /^if\(touch_y>=(\d+)&&touch_y<=(\d+)\)\{if\(touch_x>=(\d+)&&touch_x<=(\d+)\)\{(printh [^}]*)\}else\{if\(touch_x>=(\d+)&&touch_x<=(\d+)\)\{(printh [^}]*)\}\}\}$/) {
            my ($y1,$y2,$x1,$x2,$p1,$x3,$x4,$p2) = ($1,$2,$3,$4,$5,$6,$7,$8);
            push @out, "if(touch_y>=$y1&&touch_y<=$y2&&touch_x>=$x1&&touch_x<=$x2){$p1}
if(touch_y>=$y1&&touch_y<=$y2&&touch_x>=$x3&&touch_x<=$x4){$p2}
";
        } elsif ($l =~ /^if\(touch_x>=(\d+)&&touch_x<=(\d+)&&touch_y>=(\d+)&&touch_y<=(\d+)\)\{if\(touch_x<=(\d+)\)\{(printh [^}]*)\}else\{(printh [^}]*)\}\}$/) {
            my ($x1,$x2,$y1,$y2,$m,$p1,$p2) = ($1,$2,$3,$4,$5,$6,$7);
            push @out, "if(touch_x>=$x1&&touch_x<=$x2&&touch_y>=$y1&&touch_y<=$y2&&touch_x<=$m){$p1}
if(touch_x>=$x1&&touch_x<=$x2&&touch_y>=$y1&&touch_y<=$y2&&touch_x>$m){$p2}
";
        } else {
            push @out, "$l
";
        }
    }
    open my $wh, '>', $path or die $!; print $wh @out; close $wh;
    my $max = 0;
    for (@out) { chomp; $max = length($_) if length($_) > $max; }
    printf "%s: %d righe, max %d caratteri\n", $path, scalar(@out), $max;
}
