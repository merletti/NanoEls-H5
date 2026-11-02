#!/usr/bin/perl
# Builds a print-ready A4 sheet with two copies of the NanoEls H5 rear label
# at the original 19% size (53.62 x 33.51 mm), with crop marks and a 50 mm ruler.
use strict;
use warnings;

my ($svg_file, $outdir) = @ARGV;
die "usage: build_label_sheet.pl <label.svg> <outdir>\n" unless $svg_file && $outdir;

open my $sf, '<:raw', $svg_file or die "open $svg_file: $!";
local $/;
my $svg = <$sf>;
close $sf;

mkdir $outdir unless -d $outdir;

$svg =~ s/<\?xml[^>]*>\s*//;
$svg =~ s/<svg\b/<svg class="art"/;

my $unit = <<'UNIT';
<div class="unit" style="left:@LEFT@mm">
  <div class="label">@SVG@</div>
  <span class="mh tl"></span><span class="mv tl"></span>
  <span class="mh tr"></span><span class="mv tr"></span>
  <span class="mh bl"></span><span class="mv bl"></span>
  <span class="mh br"></span><span class="mv br"></span>
</div>
UNIT

my $u1 = $unit; $u1 =~ s/\@LEFT\@/20/;   $u1 =~ s/\@SVG\@/$svg/;
my $u2 = $unit; $u2 =~ s/\@LEFT\@/120/;  $u2 =~ s/\@SVG\@/$svg/;

my $html = <<"HTML";
<!doctype html>
<html lang="it">
<head>
<meta charset="utf-8">
<title>Targhetta posteriore NanoEls H5</title>
<style>
  \@page { size: A4; margin: 0; }
  * { box-sizing: border-box; }
  html, body { margin: 0; padding: 0; background: #fff; color: #111;
               font-family: "Segoe UI", Arial, sans-serif; }
  .sheet { position: relative; width: 210mm; height: 296.5mm; overflow: hidden; }
  .title { position: absolute; left: 20mm; top: 15mm; font-size: 5mm; font-weight: 600; }
  .sub   { position: absolute; left: 20mm; top: 22mm; font-size: 2.7mm; color: #555; }
  .unit  { position: absolute; top: 35mm; width: 53.62mm; height: 33.51mm; }
  .label { position: absolute; inset: 0; background: #000; }
  .label .art { display: block; width: 100%; height: 100%; }
  .mh { position: absolute; width: 3mm; height: 0.2mm; background: #000; }
  .mv { position: absolute; width: 0.2mm; height: 3mm; background: #000; }
  .mh.tl { left: -5mm; top: -2mm; }  .mv.tl { left: -2mm; top: -5mm; }
  .mh.tr { right: -5mm; top: -2mm; } .mv.tr { right: -2mm; top: -5mm; }
  .mh.bl { left: -5mm; bottom: -2mm; } .mv.bl { left: -2mm; bottom: -5mm; }
  .mh.br { right: -5mm; bottom: -2mm; } .mv.br { right: -2mm; bottom: -5mm; }
  .note { position: absolute; left: 20mm; top: 82mm; width: 165mm;
          font-size: 2.7mm; line-height: 1.55; color: #333; }
  .note b { color: #111; }
  .ruler { position: absolute; left: 20mm; top: 100mm; }
</style>
</head>
<body>
<div class="sheet">
  <div class="title">Targhetta posteriore NanoEls H5</div>
  <div class="sub">53,6 &times; 33,5 mm &middot; due copie identiche &middot; stampa al 100%</div>

  $u1
  $u2

  <div class="note">
    <b>Stampa:</b> foglio A4, scala 100% (&ldquo;Actual size&rdquo;, senza &ldquo;Adatta alla pagina&rdquo;).<br>
    <b>Uso:</b> ritagliare lungo i segni agli angoli e incollare sul retro del case con nastro biadesivo.<br>
    <b>Controllo scala:</b> il righello qui sotto deve misurare esattamente 50&nbsp;mm.
  </div>

  <svg class="ruler" width="50mm" height="7mm" viewBox="0 0 50 7">
    <g stroke="#000" fill="none">
      <line x1="0" y1="5.5" x2="50" y2="5.5" stroke-width="0.25"/>
      <line x1="0"  y1="5.5" x2="0"  y2="2.6" stroke-width="0.25"/>
      <line x1="10" y1="5.5" x2="10" y2="3.5" stroke-width="0.25"/>
      <line x1="20" y1="5.5" x2="20" y2="2.6" stroke-width="0.25"/>
      <line x1="30" y1="5.5" x2="30" y2="3.5" stroke-width="0.25"/>
      <line x1="40" y1="5.5" x2="40" y2="2.6" stroke-width="0.25"/>
      <line x1="50" y1="5.5" x2="50" y2="2.6" stroke-width="0.25"/>
    </g>
    <g fill="#000" font-family="Arial, sans-serif" font-size="2.1" text-anchor="middle">
      <text x="0"  y="1.3">0</text>
      <text x="20" y="1.3">20</text>
      <text x="40" y="1.3">40</text>
      <text x="50" y="1.3" text-anchor="end">50 mm</text>
    </g>
  </svg>
</div>
</body>
</html>
HTML

sub write_file {
  my ($path, $data) = @_;
  open my $oh, '>:raw', $path or die "write $path: $!";
  print $oh $data;
  close $oh;
  print "OK $path\n";
}

write_file("$outdir/targhetta_h5_A4.html", $html);

my $single = <<"SINGLE";
<!doctype html>
<html lang="it"><head><meta charset="utf-8"><title>Targhetta NanoEls H5</title>
<style>
  \@page { size: 53.62mm 33.51mm; margin: 0; }
  html, body { margin: 0; padding: 0; background: #000; }
  svg { display: block; width: 53.62mm; height: 33.51mm; }
</style></head><body>
$svg
</body></html>
SINGLE
write_file("$outdir/targhetta_h5.html", $single);

my $preview = <<"PREVIEW";
<!doctype html>
<html lang="it"><head><meta charset="utf-8"><title>Anteprima targhetta NanoEls H5</title>
<style>
  html, body { margin: 0; padding: 0; background: #000; }
  svg { display: block; width: 1600px; height: 1000px; }
</style></head><body>
$svg
</body></html>
PREVIEW
write_file("$outdir/preview_label.html", $preview);
