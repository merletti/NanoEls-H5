use strict; use warnings;
for my $path (glob("gui/ev/[0-9]*_touch.txt")) {
    open my $fh, '<', $path or die $!;
    my @lines = <$fh>; close $fh;
    my @out;
    for my $l (@lines) {
        chomp $l;
        $l =~ s/\r$//;
        next if $l =~ /^\s*$/;
        $l =~ s/touch_x/tch0/g;
        $l =~ s/touch_y/tch1/g;
        if ($l =~ /^if\(([^)]+)\)\{(printh [^}]+)\}$/) {
            push @out, "if($1)\n{\n$2\n}\n";
        } else {
            push @out, "$l\n";
        }
    }
    open my $wh, '>', $path or die $!; print $wh @out; close $wh;
    printf "%s: %d righe\n", $path, scalar(@out);
}
