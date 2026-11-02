use strict; use warnings;
my $f = shift or die "uso: jpgscan.pl file.HMI\n";
open(my $fh, '<:raw', $f) or die $!;
local $/; my $d = <$fh>; close $fh;
my @pics;
my $pos = 0;
while (1) {
  my $i = index($d, "\xFF\xD8\xFF", $pos);
  last if $i < 0;
  # find SOF marker within next 4KB
  my $j = $i + 2; my $end = $i + 4096;
  my ($w, $h, $m);
  while ($j < $end && $j + 9 < length($d)) {
    last unless substr($d, $j, 1) eq "\xFF";
    my $mk = ord(substr($d, $j+1, 1));
    if ($mk == 0xC0 || $mk == 0xC1 || $mk == 0xC2) {
      $h = unpack('n', substr($d, $j+5, 2));
      $w = unpack('n', substr($d, $j+7, 2));
      $m = sprintf('SOF%d', $mk - 0xC0);
      last;
    }
    last if $mk == 0xD9;
    my $len = unpack('n', substr($d, $j+2, 2));
    last if $len < 2;
    $j += 2 + $len;
  }
  push @pics, [$i, $w, $h, $m];
  $pos = $i + 3;
}
my $n = 0;
for my $p (@pics) {
  printf "%2d  off %8d  %sx%s %s\n", $n++, $p->[0], (defined $p->[1]?$p->[1]:'?'), (defined $p->[2]?$p->[2]:'?'), (defined $p->[3]?$p->[3]:'');
}
print "totale JPEG: $n\n";
