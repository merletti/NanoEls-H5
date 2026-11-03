#!/usr/bin/perl
# Renders the 11 work pages with the sample values hidden. The numbers are
# painted by the firmware, so the background must not carry them; the "mm"
# units stay in place because a hidden copy of the value keeps the layout.
use strict;
use warnings;
use File::Path qw(make_path);
use Cwd qw(getcwd);

my @ids = qw(ingranaggi filetto tornitura spianatura troncatura ellisse
             asincrono assey joystick xgear scanalatura);

my $hidden = 0;
sub valbox_clean {
    my ($c) = @_;
    my $unit = '';
    $unit = $1 if $c =~ m{(\s*<small>.*?</small>)\s*\z}s;
    $c =~ s{\s*<small>.*?</small>\s*\z}{}s;
    $hidden++;
    return '<div class="valbox"><span><span class="ghost">' . $c . '</span>'
         . $unit . '</span></div>';
}

my $src = 'screens.html';
open my $fh, '<', $src or die "screens.html: $!";
my $doc = do { local $/; <$fh> };
close $fh;

$doc =~ s{<div class="valbox"><span>(.*?)</span></div>}{valbox_clean($1)}ge;
die "nessun valbox trovato\n" unless $hidden > 20;

$doc =~ s{</head>}{<style>
  .ghost { visibility: hidden; }
</style>
</head>};

make_path('clean');
open(my $out, '>', 'clean/screens_clean.html') or die $!;
print $out $doc;
close $out;

my $chrome = 'C:\Program Files\Google\Chrome\Application\chrome.exe';
my $here = getcwd;
$here =~ s{^/([a-z])/}{uc($1) . ':/'}ie;
for my $id (@ids) {
    my $png = "$here/clean/${id}.png";
    my $url = "file:///$here/clean/screens_clean.html?p=$id";
    unlink $png;
    system($chrome, '--headless=new', '--disable-gpu', '--hide-scrollbars',
           '--window-size=800,480', "--screenshot=$png", $url);
    die "render fallito: $id\n" unless -s $png;
    print "clean/$id.png\n";
}
print "valori nascosti: $hidden\n";
