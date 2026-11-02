#!/usr/bin/perl
use strict; use warnings;
# Genera gli script evento delle pagine servizio. Formato Nextion:
# printh 68 <page> <code> 5A FF FF FF
# page = id della pagina in esadecimale a due cifre.
my $dir = "gui/ev";
sub zone {
  my ($x1, $y1, $x2, $y2, $page, $code) = @_;
  return sprintf("if(tch0>=%d&&tch0<=%d&&tch1>=%d&&tch1<=%d)\n{\nprinth 68 %02X %02X 5A FF FF FF\n}\n",
    $x1, $x2, $y1, $y2, $page, $code);
}
sub post { my ($page) = @_; return sprintf("printh 68 %02X 10 5A FF FF FF\n", $page); }
sub writefile { my ($name, $body) = @_; open(my $o, '>', "$dir/$name") or die "$dir/$name: $!"; print $o $body; close $o; print "ok $name\n"; }

# ---------- MENU (page 0) ----------
my $menu = '';
$menu .= zone(684, 10, 790, 62, 0x00, 0x70);   # pill ELS ON/OFF
my @cardx = (12, 168, 324, 480, 636);
my @cardy = (64, 172, 280);
my $code = 0x71;
my @rowcount = (5, 5, 3);
for my $r (0 .. 2) {
  for my $c (0 .. $rowcount[$r] - 1) {
    my $x = $cardx[$c];
    my $y = $cardy[$r];
    $menu .= zone($x, $y, $x + 147, $y + 99, 0x00, $code);
    $code++;
  }
}
# servizi: COMANDO, G-CODE, SETUP, WIFI, INFO
my @srvx = (12, 168, 325, 482, 639);
for my $i (0 .. 4) {
  $menu .= zone($srvx[$i], 388, $srvx[$i] + 148, 441, 0x00, 0x80 + $i);
}
writefile("0_touch.txt", $menu);
writefile("0_post.txt", post(0x00));

# ---------- pill MENU comune alle sottopagine ----------
my $pill = zone(684, 6, 788, 64, 0, 0x31);

# ---------- CONO (page 5): 5 misure editabili ----------
my $cone = '';
my @conv = (83, 141, 199, 257, 315);   # top of each value row
for my $i (0 .. 4) {
  my $y = $conv[$i];
  $cone .= zone(235, $y, 389, $y + 44, 0x05, 0x40 + $i);
}
$cone .= zone(12, 374, 328, 432, 0x05, 0x30);   # ATTIVA MODALITA'
$cone .= zone(338, 374, 488, 432, 0x05, 0x31);  # ANNULLA
for my $i (0 .. 4) {
  my $y = $conv[$i];
  $cone .= zone(389, $y, 433, $y + 44, 0x05, 0x20 + $i * 2);      # -
  $cone .= zone(434, $y, 484, $y + 44, 0x05, 0x20 + $i * 2 + 1);  # +
}
writefile("5_touch.txt", $cone);
writefile("5_post.txt", post(0x05));

# ---------- COMANDO (page 13) ----------
my $com = '';
$com .= zone(684, 6, 788, 64, 0x0D, 0x31);      # MENU
$com .= zone(13, 72, 105, 128, 0x0D, 0x70);     # STATO -> ON/OFF
$com .= zone(335, 72, 465, 128, 0x0D, 0x72);    # PRINCIPI
$com .= zone(477, 72, 643, 128, 0x0D, 0x73);    # PASSO
$com .= zone(654, 72, 788, 128, 0x0D, 0x74);    # MISURA
$com .= zone(24, 183, 78, 241, 0x0D, 0x75);     # badge X
$com .= zone(286, 183, 340, 241, 0x0D, 0x76);   # badge Y
$com .= zone(549, 183, 603, 241, 0x0D, 0x77);   # badge Z
# jog: X+ X- Y+ Y- Z- Z+
my @jogx = (12, 146, 279, 401, 535, 668);
for my $i (0 .. 5) {
  $com .= zone($jogx[$i], 294, $jogx[$i] + 119, 358, 0x0D, 0x60 + $i);
}
$com .= zone(12, 360, 104, 430, 0x0D, 0x78);    # STOP
my @digx = (109, 164, 219, 274, 329, 384, 439, 494, 549, 604);
for my $i (0 .. 9) {
  $com .= zone($digx[$i], 360, $digx[$i] + 54, 430, 0x0D, 0x79 + $i);
}
$com .= zone(662, 360, 727, 430, 0x0D, 0x83);   # CANC
$com .= zone(729, 360, 790, 430, 0x0D, 0x84);   # OK
writefile("13_touch.txt", $com);
writefile("13_post.txt", post(0x0D));
# Rilascio: qualunque dito alzato ferma tutti i jog.
writefile("13_release.txt", "printh 68 0D 6F 5A FF FF FF\n");

# ---------- SETUP (page 14) ----------
my $set = '';
$set .= zone(684, 6, 788, 64, 0x0E, 0x31);     # MENU
my @scx = (9, 275, 541);
my @scy = (73, 247);
my $scode = 0xA0;
for my $y (@scy) {
  for my $x (@scx) {
    $set .= zone($x, $y, $x + 252, $y + 160, 0x0E, $scode);
    $scode++;
  }
}
writefile("14_touch.txt", $set);
writefile("14_post.txt", post(0x0E));

# ---------- WIFI (page 15) ----------
my $wifi = '';
$wifi .= zone(684, 6, 788, 64, 0x0F, 0x31);      # MENU
$wifi .= zone(26, 126, 478, 176, 0x0F, 0xA0);     # NOME RETE
$wifi .= zone(26, 204, 478, 254, 0x0F, 0xA1);     # PASSWORD
$wifi .= zone(22, 260, 248, 318, 0x0F, 0xB0);     # CONNETTI
$wifi .= zone(252, 260, 478, 318, 0x0F, 0xB1);    # DIMENTICA
writefile("15_touch.txt", $wifi);
writefile("15_post.txt", post(0x0F));

# ---------- INFO (page 16) ----------
writefile("16_touch.txt", zone(684, 6, 788, 64, 0x10, 0x31));
writefile("16_post.txt", post(0x10));

# ---------- PANNELLO IMPOSTAZIONI (page 19) ----------
my $pan = '';
$pan .= zone(714, 8, 790, 46, 0x13, 0xD2);        # X chiudi
for my $i (0 .. 6) {
  my $y = 68 + $i * 46;
  $pan .= zone(12, $y, 628, $y + 42, 0x13, 0xA0 + $i);      # riga
  $pan .= zone(636, $y + 4, 680, $y + 38, 0x13, 0xB0 + $i);  # -
  $pan .= zone(692, $y + 4, 736, $y + 38, 0x13, 0xC0 + $i);  # +
}
$pan .= zone(24, 402, 146, 446, 0x13, 0xD0);      # PREC
$pan .= zone(654, 402, 778, 446, 0x13, 0xD1);     # SUCC
writefile("19_touch.txt", $pan);
writefile("19_post.txt", post(0x13));

# ---------- TASTIERA TESTUALE (page 20) ----------
my $kb = '';
my @rowy = (120, 172, 224, 276);
my @kbcount = (10, 10, 9, 10);
my @rowbase = (0x70, 0x80, 0x90, 0xA0);
for my $r (0 .. 3) {
  my $count = $kbcount[$r];
  my $total = $count * 74 + ($count - 1) * 4;
  my $x0 = int((800 - $total) / 2);
  for my $i (0 .. $count - 1) {
    my $x = $x0 + $i * 78;
    $kb .= zone($x, $rowy[$r], $x + 74, $rowy[$r] + 46, 0x14, $rowbase[$r] + $i);
  }
}
$kb .= zone(12, 338, 152, 388, 0x14, 0xB0);       # MAIUSC
$kb .= zone(158, 338, 438, 388, 0x14, 0xB1);      # SPAZIO
$kb .= zone(444, 338, 584, 388, 0x14, 0xB2);      # CANC
$kb .= zone(590, 338, 690, 388, 0x14, 0xB3);      # ANN.
$kb .= zone(696, 338, 788, 388, 0x14, 0xB4);      # OK
writefile("20_touch.txt", $kb);
writefile("20_post.txt", post(0x14));

# ---------- LAVORAZIONE (pagina 21) ----------
my $work = '';
$work .= zone(684, 10, 788, 54, 0x15, 0x31);      # MENU
$work .= zone(12, 74, 160, 126, 0x15, 0x8B);      # PASSO
$work .= zone(168, 74, 316, 126, 0x15, 0x8C);     # PRINCIPI
$work .= zone(324, 74, 472, 126, 0x15, 0x8D);     # PASSATE
$work .= zone(552, 356, 776, 390, 0x15, 0x70);    # AVVIA / STOP
$work .= zone(24, 268, 82, 296, 0x15, 0x75);      # ZERO X
$work .= zone(87, 268, 169, 296, 0x15, 0x85);     # MAX QUI X
$work .= zone(174, 268, 256, 296, 0x15, 0x86);    # MIN QUI X
$work .= zone(284, 268, 342, 296, 0x15, 0x76);    # ZERO Y
$work .= zone(347, 268, 429, 296, 0x15, 0x87);    # MAX QUI Y
$work .= zone(434, 268, 516, 296, 0x15, 0x88);    # MIN QUI Y
$work .= zone(544, 268, 602, 296, 0x15, 0x77);    # ZERO Z
$work .= zone(607, 268, 689, 296, 0x15, 0x89);    # MAX QUI Z
$work .= zone(694, 268, 776, 296, 0x15, 0x8A);    # MIN QUI Z
$work .= zone(12, 404, 200, 444, 0x15, 0x65);     # jog Z-
$work .= zone(208, 404, 396, 444, 0x15, 0x64);    # jog Z+
$work .= zone(404, 404, 592, 444, 0x15, 0x60);    # jog X+
$work .= zone(600, 404, 788, 444, 0x15, 0x61);    # jog X-
writefile("21_touch.txt", $work);
writefile("21_post.txt", post(0x15));
writefile("21_release.txt", "printh 68 15 6F 5A FF FF FF\n");

# ---------- SCANALATURA: riduzione sinistra + finecorsa Z (pagina 17) ----------
my $scan = zone(255, 132, 387, 180, 0x11, 0x41)   # RIDUZIONE SINISTRA
         . zone(181, 293, 284, 339, 0x11, 0x44)   # FINECORSA Z MAX
         . zone(285, 293, 387, 339, 0x11, 0x45);  # FINECORSA Z MIN
open(my $in, '<', "$dir/17_touch.txt") or die "17_touch: $!";
local $/; my $body = <$in>; close $in;
# elimina i blocchi gia' presenti prima di reinserirli (0x31 resta: e' ANNULLA)
$body =~ s/if\([^)]*\)\s*\{\s*printh 68 11 4[145] 5A FF FF FF\s*\}\s*\n?//g;
writefile("17_touch.txt", $scan . $body);

# ---------- G-CODE (page 9): elenco, ESEGUI, ELIMINA, RICARICA ----------
my $gc = '';
$gc .= zone(684, 6, 788, 64, 0x09, 0x31);        # MENU
my @rowtop = (106, 180, 254, 326);
for my $i (0 .. 3) {
  $gc .= zone(26, $rowtop[$i], 474, $rowtop[$i] + 64, 0x09, 0xA0 + $i);
}
$gc .= zone(513, 223, 775, 278, 0x09, 0xB0);      # ESEGUI
$gc .= zone(513, 288, 775, 343, 0x09, 0xB1);      # ELIMINA
$gc .= zone(513, 352, 775, 401, 0x09, 0xB2);      # RICARICA
writefile("9_touch.txt", $gc);
