#!/usr/bin/perl
# Builds the clean card pages: the quote drawings without the sample values,
# with the chip and the dimension box enlarged so the firmware sprite text
# (16x26 glyphs) fits inside them.
use strict;
use warnings;
use File::Path qw(make_path);

my @ids = qw(ingranaggi filetto tornitura spianatura troncatura ellisse
             asincrono assey joystick xgear scanalatura);

# page => [ chip old, chip new, box old, box new ] (empty when the page has none)
my %rects = (
  ingranaggi  => ['x="86" y="26" width="76" height="22"',  'x="48" y="24" width="152" height="28"',
                  'x="76" y="148" width="98" height="26"', 'x="76" y="146" width="100" height="30"'],
  filetto     => ['x="86" y="26" width="76" height="22"',  'x="48" y="24" width="152" height="28"',
                  'x="76" y="148" width="98" height="26"', 'x="76" y="146" width="100" height="30"'],
  tornitura   => ['x="84" y="26" width="76" height="22"',  'x="46" y="24" width="152" height="28"',
                  'x="70" y="148" width="98" height="26"', 'x="70" y="146" width="100" height="30"'],
  spianatura  => ['x="16" y="150" width="76" height="22"', 'x="16" y="148" width="152" height="28"',
                  'x="132" y="58" width="78" height="24"', 'x="132" y="56" width="100" height="30"'],
  troncatura  => ['x="30" y="24" width="78" height="22"',  'x="20" y="22" width="152" height="28"',
                  'x="184" y="62" width="62" height="24"', 'x="146" y="108" width="100" height="30"'],
  ellisse     => ['x="86" y="26" width="76" height="22"',  'x="48" y="24" width="152" height="28"',
                  'x="76" y="134" width="94" height="26"', 'x="76" y="132" width="100" height="30"'],
  asincrono   => ['x="86" y="26" width="76" height="22"',  'x="48" y="24" width="152" height="28"',
                  'x="74" y="148" width="98" height="26"', 'x="74" y="146" width="100" height="30"'],
  assey       => ['x="146" y="20" width="90" height="22"', 'x="100" y="18" width="152" height="28"',
                  'x="150" y="78" width="78" height="24"', 'x="150" y="76" width="100" height="30"'],
  joystick    => [],
  xgear       => ['x="24" y="26" width="84" height="22"',  'x="24" y="24" width="152" height="28"',
                  'x="178" y="89" width="68" height="24"', 'x="140" y="150" width="100" height="30"'],
  scanalatura => ['x="82" y="26" width="84" height="22"',  'x="48" y="24" width="152" height="28"',
                  'x="72" y="148" width="98" height="26"', 'x="72" y="146" width="100" height="30"'],
);

make_path('card_clean');
open(my $man, '>', 'card_clean/order.txt') or die $!;
for my $id (@ids) {
    open(my $fh, '<', "quote/$id.html") or die "quote/$id.html: $!";
    my $html = do { local $/; <$fh> };
    close $fh;

    my $r = $rects{$id};
    for (my $i = 0; $i < @$r; $i += 2) {
        my $n = ($html =~ s/\Q$r->[$i]\E/$r->[$i + 1]/g);
        die "$id: rect non trovato: $r->[$i]\n" unless $n == 1;
    }

    # Values are drawn by the firmware; keep only the axis letters of ASSE Y.
    $html =~ s{<text\b[^>]*>(?!Z<|Y<)[^<]*</text>\s*}{}g;

    open(my $out, '>', "card_clean/$id.html") or die $!;
    print $out $html;
    close $out;
    print $man "$id\n";
}
close $man;
print "ok\n";
