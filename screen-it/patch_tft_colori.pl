#!/usr/bin/perl
# Variante italiana + colori per asse (X rosso, Y verde, Z blu).
# - etichette modalita' in italiano (campi txt maxl=100)
# - watermark "NanoEls IT 20261028"
# - pco dei 9 campi numerici DRO (3 per asse) colorato per asse
use strict; use warnings;
no warnings 'portable';

my $SRC = shift // "C:/Users/Admin/Desktop/h5/screen/h5.tft";
my $OUT = shift // "C:/Users/Admin/Documents/Qoder/2026-10-28/9b591104/screen-it/h5_it_colori.tft";

open(my $fh, "<:raw", $SRC) or die "src: $!";
local $/; my $buf = <$fh>; close $fh;
my $size = length($buf);

my $BLOCK_START = 0x0c17b0;
my $BLOCK_END   = 0x0c1d00;
my $MAXL        = 100;

my @MAP = (
  [ "GEAR",    "INGR."      ],
  [ "TURN",    "TORN."      ],
  [ "FACE",    "SPIAN."     ],
  [ "CONE",    "CONO"        ],
  [ "CUT",     "TRONC."     ],
  [ "THREAD",  "FILET."     ],
  [ "ELLIPSE", "ELLISSE"     ],
  [ "GCODE",   "G-CODE"      ],
  [ "ASYNC",   "ASINC."     ],
  [ "Y",       "ASSE Y"      ],
  [ "XGEAR",   "X-ING"      ],
  [ "JOY",     "JOY"        ],
  [ "SLOT",    "SCAN."      ],
);

sub find_label {
  my ($label) = @_;
  my $pos = $BLOCK_START - 1;
  while (($pos = index($buf, $label, $pos + 1)) != -1) {
    last if $pos > $BLOCK_END;
    next unless $pos == $BLOCK_START || substr($buf, $pos - 1, 1) eq "\x00";
    my $tail = substr($buf, $pos + length($label), $MAXL - length($label));
    next unless $tail eq "\x00" x length($tail);
    return $pos;
  }
  die "etichetta non trovata o campo troppo stretto: $label\n";
}

my %plan;
for my $m (@MAP) {
  my ($old, $new) = @$m;
  die "testo troppo lungo: $new\n" if length($new) >= $MAXL;
  $plan{ find_label($old) } = [ $old, $new ];
}

my $wm_off = index($buf, "NanoEls TFT20260511");
die "watermark non trovato\n" if $wm_off < 0;
my $wm_new = "NanoEls IT 20261028";
my $wm_tail = substr($buf, $wm_off + 19, $MAXL - 19);
die "watermark senza spazio libero\n" unless $wm_tail eq "\x00" x length($wm_tail);
$plan{$wm_off} = [ "NanoEls TFT20260511", $wm_new ];

my @changed_ranges;
for my $off (sort { $a <=> $b } keys %plan) {
  my ($old, $new) = @{ $plan{$off} };
  die "offset inatteso a 0x$off\n" unless substr($buf, $off, length($old)) eq $old;
  substr($buf, $off, $MAXL) = $new . ("\x00" x ($MAXL - length($new)));
  push @changed_ranges, [ $off, $off + $MAXL - 1 ];
  printf "txt 0x%06x  %-19s -> %s\n", $off, $old, $new;
}

# --- colori per asse: pco dei campi numerici DRO ---
# record Number: +0x28 x,y,w,h | +0x3E bco | +0x40 pco | +0x48 txt_rel
my %AXIS = (
  X => { color => 0xF800, recs => [ 0xC03BC, 0xC0410, 0xC0464 ], coords => [ 49, 120, 221 ] },
  Y => { color => 0x07E0, recs => [ 0xC050C, 0xC0560, 0xC05B4 ], coords => [ 316, 315, 315 ] },
  Z => { color => 0x04FF, recs => [ 0xC065C, 0xC06B0, 0xC0704 ], coords => [ 580, 580, 580 ] },
);
for my $ax (sort keys %AXIS) {
  my $a = $AXIS{$ax};
  for my $p (@{ $a->{recs} }) {
    (my $ptr) = unpack("V", substr($buf, $p, 4));
    die sprintf("record 0x%06x non valido\n", $p) unless ($ptr & 0xFFFF0000) == 0x37010000;
    die sprintf("record 0x%06x: attesa riempimento FF\n", $p)
      unless substr($buf, $p + 4, 24) eq "\xff" x 24;
    my ($x, $y, $w, $h) = unpack("v4", substr($buf, $p + 0x28, 8));
    my $rel = unpack("V", substr($buf, $p + 0x48, 4));
    my $txt = substr($buf, 0xC0000 + $rel + 0x2C, 8); $txt =~ s/\x00.*//s;
    my ($bco, $pco) = unpack("v2", substr($buf, $p + 0x3E, 4));
    die sprintf("record 0x%06x: bco/pco inattesi (%04x/%04x)\n", $p, $bco, $pco)
      unless $bco == 0x0000 && $pco == 0xFFFF;
    die sprintf("record 0x%06x: testo '%s' non numerico\n", $p, $txt)
      unless $txt =~ /^[0-9]+$/;
    substr($buf, $p + 0x40, 2) = pack("v", $a->{color});
    push @changed_ranges, [ $p + 0x40, $p + 0x41 ];
    printf "pco 0x%06x  asse %s @(%d,%d %dx%d) -> %04X\n", $p + 0x40, $ax, $x, $y, $w, $h, $a->{color};
  }
}

sub crc32_word {
  my ($data) = @_;
  my @w = unpack("V*", $data);
  push @w, 0 if length($data) % 4;
  my $poly = 0x4c11db7 | (1 << 32);
  my $reg = 0; my $first = 1;
  push @w, 0;
  for my $word (@w) {
    $word ^= 0xffffffff if $first;
    $first = 0;
    for (1 .. 32) {
      $reg = ($reg << 1) & 0x1ffffffff;
      $reg += 1 if $word >= (1 << 31);
      $word = ($word << 1) & 0xffffffff;
      $reg ^= $poly if $reg >= (1 << 32);
    }
  }
  return $reg & 0xffffffff;
}

my $crc = crc32_word(substr($buf, 0, $size - 4));
$crc ^= ord(substr($buf, 0x03, 1)) ^ ord(substr($buf, 0x2e, 1)) ^ ord(substr($buf, 0x3c, 1));
substr($buf, $size - 4, 4) = pack("V", $crc);

open(my $out, ">:raw", $OUT) or die "out: $!";
print $out $buf; close $out;

# --- verifica ---
open(my $chk, "<:raw", $OUT) or die; local $/; my $v = <$chk>; close $chk;
die "dimensione cambiata\n" unless length($v) == $size;
my $stored = unpack("V", substr($v, $size - 4, 4));
my $recalc = crc32_word(substr($v, 0, $size - 4))
           ^ ord(substr($v, 0x03, 1)) ^ ord(substr($v, 0x2e, 1)) ^ ord(substr($v, 0x3c, 1));
die sprintf("CRC errato: 0x%08x vs 0x%08x\n", $stored, $recalc) unless $stored == $recalc;

open(my $orig, "<:raw", $SRC) or die; local $/; my $o = <$orig>; close $orig;
my ($outside, $changed) = (0, 0);
for (my $i = 0; $i < $size - 4; $i++) {
  next if substr($o, $i, 1) eq substr($v, $i, 1);
  $changed++;
  my $inside = 0;
  for my $r (@changed_ranges) { $inside = 1 if $i >= $r->[0] && $i <= $r->[1]; }
  $outside++ unless $inside;
}
printf "OK: %d byte / %s, CRC 0x%08x, modifiche fuori campo: %d\n",
  $size, $OUT, $stored, $outside;
die "modifiche inattese fuori dai campi previsti\n" if $outside;
