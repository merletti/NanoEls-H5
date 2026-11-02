#!/usr/bin/perl
# Converts the NanoEls H5 rear-label PDF (800x500, Figma export, all text as paths)
# into a standalone SVG.
use strict;
use warnings;
use Compress::Zlib;

my ($pdf, $out) = @ARGV;
die "usage: pdf2svg.pl <in.pdf> <out.svg>\n" unless $pdf && $out;

open my $fh, '<:raw', $pdf or die "open $pdf: $!";
local $/;
my $data = <$fh>;
close $fh;

# page content is object 172 in this PDF
my ($obj) = $data =~ /172\s+0\s+obj\s*<<(.*?)>>\s*stream\r?\n(.*?)\r?\nendstream/s
  or die "object 172 not found\n";
my $content = Compress::Zlib::uncompress($2);
die "inflate failed\n" unless defined $content;

my @blocks = split /^Q\s*$/m, $content;
my @out;

push @out, '<svg xmlns="http://www.w3.org/2000/svg" width="800" height="500" viewBox="0 0 800 500">';
push @out, '<g transform="translate(0,500) scale(1,-1)">';

for my $b (@blocks) {
  next unless $b =~ /^\s*q\b/m;
  next if $b =~ /\bBT\b/;                 # text duplicate; glyphs are already paths

  my $g = '';
  if ($b =~ /([0-9.\-]+) ([0-9.\-]+) ([0-9.\-]+) ([0-9.\-]+) ([0-9.\-]+) ([0-9.\-]+) cm/) {
    my @m = map { $_ + 0 } ($1, $2, $3, $4, $5, $6);
    if ($m[0] != 1 || $m[1] != 0 || $m[2] != 0 || $m[3] != 1 || $m[4] != 0 || $m[5] != 0) {
      $g = sprintf('<g transform="matrix(%.6f,%.6f,%.6f,%.6f,%.6f,%.6f)">', @m);
    }
  }

  my ($r, $gr, $bl) = (1, 1, 1);
  if ($b =~ /([0-9.]+) ([0-9.]+) ([0-9.]+) scn/) {
    ($r, $gr, $bl) = ($1 + 0, $2 + 0, $3 + 0);
  }

  # drop the "q / cm / scn" header, keep only the path body
  my $body = $b;
  $body =~ s/^.*?\bscn\b\s*//s;
  $body =~ s/^.*?\bcm\b\s*//s if $body =~ /^\s*1\.000000/;

  my @tok = ($body =~ /([0-9.\-]+|[mlch])/g);
  my $d = '';
  my @nums;
  for my $t (@tok) {
    if ($t =~ /^[0-9.\-]+$/) { push @nums, $t; next; }
    if ($t eq 'm' && @nums >= 2) { $d .= sprintf('M%s %s', splice(@nums,0,2)); }
    elsif ($t eq 'l' && @nums >= 2) { $d .= sprintf('L%s %s', splice(@nums,0,2)); }
    elsif ($t eq 'c' && @nums >= 6) { $d .= sprintf('C%s %s %s %s %s %s', splice(@nums,0,6)); }
    elsif ($t eq 'h') { $d .= 'Z'; }
    else { @nums = (); }
  }
  next unless length $d;

  my $fill = sprintf('rgb(%d,%d,%d)', int($r * 255 + 0.5), int($gr * 255 + 0.5), int($bl * 255 + 0.5));
  push @out, $g;
  push @out, qq{<path d="$d" fill="$fill"/>};
  push @out, '</g>' if length $g;
}

push @out, '</g>';
push @out, '</svg>';

open my $oh, '>:raw', $out or die "write $out: $!";
print $oh join("\n", @out), "\n";
close $oh;
print "OK $out\n";
