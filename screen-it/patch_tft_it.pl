#!/usr/bin/perl
# Genera una versione italiana di h5.tft cambiando solo i campi testo
# della pagina modalita' (maxl=100 nel progetto h5.HMI) e il watermark.
use strict; use warnings;
no warnings 'portable';

my $SRC = shift // "h5.tft";
my $OUT = shift // "h5_it_test.tft";

open(my $fh, "<:raw", $SRC) or die "src: $!";
local $/; my $buf = <$fh>; close $fh;
my $size = length($buf);

my $BLOCK_START = 0x0c17b0;      # inizio del gruppo pulsanti modalita'
my $BLOCK_END   = 0x0c1d00;
my $MAXL        = 100;          # da h5.HMI: txt_maxl dei pulsanti modalita'

# vecchio -> nuovo (nessun accento: font bitmap mono50/60/72)
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

# --- trova l'offset di ogni etichetta dentro il blocco dati globale ---
sub find_label {
  my ($label) = @_;
  my $pos = $BLOCK_START - 1;
  while (($pos = index($buf, $label, $pos + 1)) != -1) {
    last if $pos > $BLOCK_END;
    my $before_ok = $pos == $BLOCK_START || substr($buf, $pos - 1, 1) eq "\x00";
    next unless $before_ok;
    my $tail = substr($buf, $pos + length($label), $MAXL - length($label));
    next unless $tail eq "\x00" x length($tail);   # spazio libero sufficiente
    return $pos;
  }
  die "etichetta non trovata o campo troppo stretto: $label\n";
}

my %plan;
for my $m (@MAP) {
  my ($old, $new) = @$m;
  die "testo troppo lungo: $new\n" if length($new) >= $MAXL;
  my $off = find_label($old);
  $plan{$off} = [ $old, $new ];
}

# watermark (t3): marcatore visibile che il nuovo tft e' caricato
my $wm_off = index($buf, "NanoEls TFT20260511");
die "watermark non trovato\n" if $wm_off < 0;
my $wm_new = "NanoEls IT 20261028";
my $wm_tail = substr($buf, $wm_off + 19, $MAXL - 19);
die "watermark senza spazio libero\n" unless $wm_tail eq "\x00" x length($wm_tail);
$plan{$wm_off} = [ "NanoEls TFT20260511", $wm_new ];

# --- applica le modifiche ---
my @changed_ranges;
for my $off (sort { $a <=> $b } keys %plan) {
  my ($old, $new) = @{ $plan{$off} };
  die "offset inatteso a 0x$off\n" unless substr($buf, $off, length($old)) eq $old;
  substr($buf, $off, $MAXL) = $new . ("\x00" x ($MAXL - length($new)));
  push @changed_ranges, [ $off, $off + $MAXL - 1 ];
  printf "0x%06x  %-19s -> %s\n", $off, $old, $new;
}

# --- ricalcola il CRC finale (variante word-based, header 0x15-0x16 = 03 00) ---
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
      $reg = ($reg << 1) & 0x1_ffff_ffff;
      $reg += 1 if $word >= (1 << 31);
      $word = ($word << 1) & 0xffffffff;
      $reg ^= $poly if $reg >= (1 << 32);
    }
  }
  return $reg & 0xffffffff;
}

my $body = substr($buf, 0, $size - 4);
my $crc = crc32_word($body);
$crc ^= ord(substr($buf, 0x03, 1)) ^ ord(substr($buf, 0x2e, 1)) ^ ord(substr($buf, 0x3c, 1));
substr($buf, $size - 4, 4) = pack("V", $crc);

open(my $out, ">:raw", $OUT) or die "out: $!";
print $out $buf; close $out;

# --- verifica: dimensione, CRC, byte cambiati solo nei campi previsti ---
open(my $chk, "<:raw", $OUT) or die; local $/; my $v = <$chk>; close $chk;
die "dimensione cambiata\n" unless length($v) == $size;
my $stored = unpack("V", substr($v, $size - 4, 4));
my $recalc = crc32_word(substr($v, 0, $size - 4))
           ^ ord(substr($v, 0x03, 1)) ^ ord(substr($v, 0x2e, 1)) ^ ord(substr($v, 0x3c, 1));
die sprintf("CRC errato: 0x%08x vs 0x%08x\n", $stored, $recalc) unless $stored == $recalc;

open(my $orig, "<:raw", $SRC) or die; local $/; my $o = <$orig>; close $orig;
my $outside = 0;
for (my $i = 0; $i < $size - 4; $i++) {
  next if substr($o, $i, 1) eq substr($v, $i, 1);
  my $inside = 0;
  for my $r (@changed_ranges) { $inside = 1 if $i >= $r->[0] && $i <= $r->[1]; }
  $outside++ unless $inside;
}
printf "OK: %d byte -> %s, CRC 0x%08x, modifiche fuori campo: %d\n",
  $size, $OUT, $stored, $outside;
die "modifiche inattese fuori dai campi testo\n" if $outside;
