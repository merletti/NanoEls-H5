#!/usr/bin/perl
use strict; use warnings;
# Genera le zone "tocco sul valore" (68 PP 4i, i = indice campo in TFT_PAGES)
# da anteporre agli eventi Touch Press. clearLeft/y presi da TFT_PAGES del firmware.
my %pages = (
  1  => [[0,259,92],[1,263,158],[2,244,224],[3,263,290]],
  2  => [[0,259,92],[1,263,158],[2,263,224],[3,244,290]],
  3  => [[0,259,92],[1,263,158],[2,243,224],[3,244,290]],
  4  => [[0,259,92],[1,263,158],[2,257,224],[3,259,290]],
  5  => [[0,256,92],[1,243,158],[2,244,224],[3,259,290]],
  6  => [[0,259,92],[1,263,158],[2,243,224],[3,259,290]],
  7  => [[0,259,92],[1,263,158],[2,243,224],[3,259,290]],
  8  => [[0,259,92],[1,263,158],[2,263,224],[3,244,290]],
  10 => [[0,259,92],[1,263,158],[2,263,224],[3,244,290]],
  11 => [[0,263,92],[1,263,158],[2,263,224]],
  12 => [[0,259,92],[1,263,158],[2,259,224],[3,263,290]],
  # SCANALATURA: i campi 1 e 4 sono TK_NONE, restano gli indici 0, 2, 3
  17 => [[0,271,86],[2,267,194],[3,271,248]],
);
for my $idx (sort { $a <=> $b } keys %pages) {
  my $old = "prev_val/${idx}_touch.txt";
  open(my $in, '<', $old) or die "no $old: $!";
  local $/; my $body = <$in>; close $in;
  my $pp = sprintf("%02X", $idx);
  my $out = '';
  for my $f (@{$pages{$idx}}) {
    my ($i, $cl, $y) = @$f;
    my ($x1, $x2) = ($cl - 12, 387);
    my ($y1, $y2) = ($y - 9, $y + 37);
    my $code = sprintf("%02X", 0x40 + $i);
    $out .= "if(tch0>=$x1&&tch0<=$x2&&tch1>=$y1&&tch1<=$y2)\n{\nprinth 68 $pp $code 5A FF FF FF\n}\n";
  }
  open(my $o, '>', "${idx}_touch.txt") or die $!;
  print $o $out . $body;
  close $o;
  print "ok $idx\n";
}
