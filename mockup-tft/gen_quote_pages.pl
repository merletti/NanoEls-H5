#!/usr/bin/perl
use strict;
use warnings;
use File::Path qw(make_path);

my $src = 'screens.html';
open my $fh, '<', $src or die "screens.html: $!";
my $doc = do { local $/; <$fh> };
close $fh;

my %svg;

$svg{ingranaggi} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <path d="M65 62 L65 104 L185 104 L185 62" fill="none" stroke="#E9E9EE" stroke-width="2.2" stroke-linejoin="round"/>
  <polyline points="65,62 70,56 75,62 80,56 85,62 90,56 95,62 100,56 105,62 110,56 115,62 120,56 125,62 130,56 135,62 140,56 145,62 150,56 155,62 160,56 165,62 170,56 175,62 180,56 185,62" fill="none" stroke="#E9E9EE" stroke-width="1.6" stroke-linejoin="round"/>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="65" y1="104" x2="65" y2="146"/>
    <line x1="185" y1="104" x2="185" y2="146"/>
  </g>
  <line x1="65" y1="140" x2="185" y2="140" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="65,140 72,136.2 72,143.8"/>
    <polygon points="185,140 178,136.2 178,143.8"/>
  </g>
  <rect x="76" y="148" width="98" height="26" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="114" y="165.5" font-family="Arial" font-size="13" font-weight="800" fill="#F2F2F2" text-anchor="middle">200.0</text>
  <text x="141" y="165" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="86" y="26" width="76" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="124" y="41.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P 1.500</text>
  <line x1="124" y1="48" x2="124" y2="55" stroke="#5B616B" stroke-width="1"/>
</svg>
SVG

$svg{filetto} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <path d="M65 64 L65 104 L185 104 L185 64" fill="none" stroke="#E9E9EE" stroke-width="2.2" stroke-linejoin="round"/>
  <polyline points="65,64 69,60.5 73,64 77,60.5 81,64 85,60.5 89,64 93,60.5 97,64 101,60.5 105,64 109,60.5 113,64 117,60.5 121,64 125,60.5 129,64 133,60.5 137,64 141,60.5 145,64 149,60.5 153,64 157,60.5 161,64 165,60.5 169,64 173,60.5 177,64 181,60.5 185,64" fill="none" stroke="#E9E9EE" stroke-width="1.5" stroke-linejoin="round"/>
  <polyline points="65,104 69,107.5 73,104 77,107.5 81,104 85,107.5 89,104 93,107.5 97,104 101,107.5 105,104 109,107.5 113,104 117,107.5 121,104 125,107.5 129,104 133,107.5 137,104 141,107.5 145,104 149,107.5 153,104 157,107.5 161,104 165,107.5 169,104 173,107.5 177,104 181,107.5 185,104" fill="none" stroke="#E9E9EE" stroke-width="1.5" stroke-linejoin="round"/>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="65" y1="108" x2="65" y2="146"/>
    <line x1="185" y1="108" x2="185" y2="146"/>
  </g>
  <line x1="65" y1="140" x2="185" y2="140" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="65,140 72,136.2 72,143.8"/>
    <polygon points="185,140 178,136.2 178,143.8"/>
  </g>
  <rect x="76" y="148" width="98" height="26" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="114" y="165.5" font-family="Arial" font-size="13" font-weight="800" fill="#F2F2F2" text-anchor="middle">120.0</text>
  <text x="141" y="165" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="86" y="26" width="76" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="124" y="41.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P 1.750</text>
  <line x1="124" y1="48" x2="124" y2="56" stroke="#5B616B" stroke-width="1"/>
</svg>
SVG

$svg{tornitura} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <rect x="55" y="62" width="123" height="46" fill="none" stroke="#E9E9EE" stroke-width="2.2"/>
  <polygon points="180,88 200,96 200,110 180,102" fill="#2B2D33" stroke="#9AA0A8" stroke-width="1.2"/>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="55" y1="108" x2="55" y2="146"/>
    <line x1="178" y1="108" x2="178" y2="146"/>
  </g>
  <line x1="55" y1="140" x2="178" y2="140" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="55,140 62,136.2 62,143.8"/>
    <polygon points="178,140 171,136.2 171,143.8"/>
  </g>
  <rect x="70" y="148" width="98" height="26" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="108" y="165.5" font-family="Arial" font-size="13" font-weight="800" fill="#F2F2F2" text-anchor="middle">150.0</text>
  <text x="135" y="165" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="84" y="26" width="76" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="122" y="41.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P 0.200</text>
  <line x1="122" y1="48" x2="122" y2="60" stroke="#5B616B" stroke-width="1"/>
</svg>
SVG

$svg{spianatura} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <circle cx="86" cy="94" r="44" fill="none" stroke="#E9E9EE" stroke-width="2.2"/>
  <g fill="none" stroke="#5B616B" stroke-width="1" stroke-dasharray="3 3">
    <circle cx="86" cy="94" r="32"/>
    <circle cx="86" cy="94" r="20"/>
    <circle cx="86" cy="94" r="8"/>
  </g>
  <polygon points="76,30 96,30 86,46" fill="#9AA0A8"/>
  <line x1="86" y1="94" x2="86" y2="50" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="86,94 82.2,87 89.8,87"/>
    <polygon points="86,50 82.2,57 89.8,57"/>
  </g>
  <rect x="132" y="58" width="78" height="24" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="161" y="74.5" font-family="Arial" font-size="12.5" font-weight="800" fill="#F2F2F2" text-anchor="middle">45.0</text>
  <text x="186" y="74" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="16" y="150" width="76" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="54" y="165.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P 0.150</text>
</svg>
SVG

$svg{troncatura} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <path d="M52 60 L148 60 L148 86 L158 86 L158 60 L170 60 L170 102 L52 102 Z" fill="none" stroke="#E9E9EE" stroke-width="2.2" stroke-linejoin="round"/>
  <rect x="144" y="30" width="18" height="30" fill="#2B2D33" stroke="#9AA0A8" stroke-width="1.2"/>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="158" y1="60" x2="182" y2="60"/>
    <line x1="158" y1="86" x2="182" y2="86"/>
  </g>
  <line x1="172" y1="60" x2="172" y2="86" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="172,60 168.2,67 175.8,67"/>
    <polygon points="172,86 168.2,79 175.8,79"/>
  </g>
  <rect x="184" y="62" width="62" height="24" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="203" y="78.5" font-family="Arial" font-size="12.5" font-weight="800" fill="#F2F2F2" text-anchor="middle">25.0</text>
  <text x="231" y="78" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="30" y="24" width="78" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="69" y="39.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P 0.080</text>
  <line x1="69" y1="46" x2="69" y2="58" stroke="#5B616B" stroke-width="1"/>
</svg>
SVG

$svg{ellisse} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <ellipse cx="122" cy="88" rx="52" ry="26" fill="none" stroke="#E9E9EE" stroke-width="2.2"/>
  <g stroke="#5B616B" stroke-width="1" stroke-dasharray="3 3">
    <line x1="70" y1="88" x2="174" y2="88"/>
    <line x1="122" y1="62" x2="122" y2="114"/>
  </g>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="70" y1="88" x2="70" y2="132"/>
    <line x1="174" y1="88" x2="174" y2="132"/>
  </g>
  <line x1="70" y1="126" x2="174" y2="126" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="70,126 77.8,122.2 77.8,129.8"/>
    <polygon points="174,126 166.2,122.2 166.2,129.8"/>
  </g>
  <rect x="76" y="134" width="94" height="26" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="112" y="151.5" font-family="Arial" font-size="13" font-weight="800" fill="#F2F2F2" text-anchor="middle">80.0</text>
  <text x="139" y="151" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="86" y="26" width="76" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="124" y="41.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P 0.100</text>
</svg>
SVG

$svg{asincrono} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <line x1="52" y1="110" x2="196" y2="110" stroke="#E9E9EE" stroke-width="1.8"/>
  <polygon points="196,110 188,105.8 188,114.2" fill="#E9E9EE"/>
  <circle cx="78" cy="86" r="20" fill="none" stroke="#E9E9EE" stroke-width="2.2"/>
  <path d="M62 72 a20 20 0 0 1 30 -2" fill="none" stroke="#9AA0A8" stroke-width="1.4"/>
  <polygon points="93,71 86,69.5 89,76" fill="#9AA0A8"/>
  <rect x="148" y="96" width="24" height="28" fill="#2B2D33" stroke="#9AA0A8" stroke-width="1.2"/>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="52" y1="110" x2="52" y2="146"/>
    <line x1="196" y1="110" x2="196" y2="146"/>
  </g>
  <line x1="52" y1="140" x2="196" y2="140" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="52,140 59,136.2 59,143.8"/>
    <polygon points="196,140 189,136.2 189,143.8"/>
  </g>
  <rect x="74" y="148" width="98" height="26" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="112" y="165.5" font-family="Arial" font-size="13" font-weight="800" fill="#F2F2F2" text-anchor="middle">200.0</text>
  <text x="139" y="165" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="86" y="26" width="76" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="124" y="41.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P 0.250</text>
</svg>
SVG

$svg{assey} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <line x1="56" y1="132" x2="196" y2="132" stroke="#E9E9EE" stroke-width="1.8"/>
  <polygon points="196,132 188,127.8 188,136.2" fill="#E9E9EE"/>
  <line x1="110" y1="132" x2="110" y2="52" stroke="#E9E9EE" stroke-width="1.8"/>
  <polygon points="110,52 105.8,60 114.2,60" fill="#E9E9EE"/>
  <circle cx="110" cy="132" r="3" fill="#9AA0A8"/>
  <text x="72" y="126" font-family="Arial" font-size="11" font-weight="800" fill="#5B616B">Z</text>
  <text x="120" y="76" font-family="Arial" font-size="11" font-weight="800" fill="#5B616B">Y</text>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="110" y1="52" x2="148" y2="52"/>
    <line x1="110" y1="132" x2="148" y2="132"/>
  </g>
  <line x1="142" y1="52" x2="142" y2="132" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="142,52 138.2,59 145.8,59"/>
    <polygon points="142,132 138.2,125 145.8,125"/>
  </g>
  <rect x="150" y="78" width="78" height="24" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="177" y="94.5" font-family="Arial" font-size="12.5" font-weight="800" fill="#F2F2F2" text-anchor="middle">100.0</text>
  <text x="205" y="94" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="146" y="20" width="90" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="191" y="35.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P Y 0.500</text>
</svg>
SVG

$svg{joystick} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <ellipse cx="126" cy="134" rx="46" ry="12" fill="none" stroke="#9AA0A8" stroke-width="1.4"/>
  <circle cx="126" cy="126" r="18" fill="none" stroke="#5B616B" stroke-width="1" stroke-dasharray="3 3"/>
  <line x1="126" y1="134" x2="126" y2="78" stroke="#E9E9EE" stroke-width="2.4"/>
  <circle cx="126" cy="70" r="10" fill="#2B2D33" stroke="#E9E9EE" stroke-width="2"/>
  <line x1="96" y1="134" x2="58" y2="134" stroke="#9AA0A8" stroke-width="1.4"/>
  <polygon points="58,134 66,129.8 66,138.2" fill="#9AA0A8"/>
  <line x1="156" y1="134" x2="194" y2="134" stroke="#9AA0A8" stroke-width="1.4"/>
  <polygon points="194,134 186,129.8 186,138.2" fill="#9AA0A8"/>
  <text x="48" y="138" font-family="Arial" font-size="12" font-weight="800" fill="#9AA0A8">Z</text>
  <text x="200" y="138" font-family="Arial" font-size="12" font-weight="800" fill="#9AA0A8">X</text>
  <text x="126" y="166" font-family="Arial" font-size="10.5" font-weight="700" fill="#6E7680" text-anchor="middle">zona morta 250</text>
  <text x="126" y="181" font-family="Arial" font-size="10" font-weight="700" fill="#5B616B" text-anchor="middle">1.00 / 8.00 giri/s</text>
</svg>
SVG

$svg{xgear} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <rect x="108" y="56" width="40" height="90" fill="none" stroke="#E9E9EE" stroke-width="2.2"/>
  <polyline points="148,56 153,61 148,66 153,71 148,76 153,81 148,86 153,91 148,96 153,101 148,106 153,111 148,116 153,121 148,126 153,131 148,136 153,141 148,146" fill="none" stroke="#E9E9EE" stroke-width="1.6" stroke-linejoin="round"/>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="148" y1="56" x2="176" y2="56"/>
    <line x1="148" y1="146" x2="176" y2="146"/>
  </g>
  <line x1="170" y1="56" x2="170" y2="146" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="170,56 166.2,63 173.8,63"/>
    <polygon points="170,146 166.2,139 173.8,139"/>
  </g>
  <rect x="178" y="89" width="68" height="24" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="201" y="105.5" font-family="Arial" font-size="12.5" font-weight="800" fill="#F2F2F2" text-anchor="middle">45.0</text>
  <text x="228" y="105" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="24" y="26" width="84" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="66" y="41.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">P X 1.000</text>
</svg>
SVG

$svg{scanalatura} = <<'SVG';
<svg width="252" height="188" viewBox="0 0 252 188" xmlns="http://www.w3.org/2000/svg">
  <path d="M60 64 L118 64 L118 80 L138 80 L138 64 L190 64 L190 104 L60 104 Z" fill="none" stroke="#E9E9EE" stroke-width="2.2" stroke-linejoin="round"/>
  <g stroke="#5B616B" stroke-width="1">
    <line x1="60" y1="104" x2="60" y2="146"/>
    <line x1="190" y1="104" x2="190" y2="146"/>
  </g>
  <line x1="60" y1="140" x2="190" y2="140" stroke="#9AA0A8" stroke-width="1.1"/>
  <g fill="#9AA0A8">
    <polygon points="60,140 67,136.2 67,143.8"/>
    <polygon points="190,140 183,136.2 183,143.8"/>
  </g>
  <rect x="72" y="148" width="98" height="26" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="110" y="165.5" font-family="Arial" font-size="13" font-weight="800" fill="#F2F2F2" text-anchor="middle">200.0</text>
  <text x="137" y="165" font-family="Arial" font-size="9.5" font-weight="700" fill="#9AA0A8">mm</text>
  <rect x="82" y="26" width="84" height="22" rx="4" fill="#101114" stroke="#2E3038" stroke-width="1.2"/>
  <text x="124" y="41.5" font-family="Arial" font-size="11" font-weight="800" fill="#F2F2F2" text-anchor="middle">AV. 0.050</text>
  <line x1="124" y1="48" x2="124" y2="62" stroke="#5B616B" stroke-width="1"/>
</svg>
SVG

my @ids = qw(ingranaggi filetto tornitura spianatura troncatura ellisse asincrono assey joystick xgear scanalatura);

make_path('quote');
for my $id (@ids) {
    die "SVG mancante per $id" unless $svg{$id};
    my $copy = $doc;
    $copy =~ s{<section class="screen" id="$id">}{<section class="screen active" id="$id">};
    $copy =~ s{<section class="screen active" id="home">}{<section class="screen" id="home">};
    $copy =~ s{const id = params\.get\('p'\) \|\| 'home';}{const id = params.get('p') || '$id';};
    $copy =~ s{</head>}{<style>
  .mode-side h3 { margin: 0; }
  .mode-side svg { display: block; margin: 8px 0 0; }
</style>
</head>};
    $copy =~ s{(<section class="screen active" id="$id">)(.*?)(</section>)}{
        my ($a, $body, $c) = ($1, $2, $3);
        $body =~ s{<div class="big-ico">.*?</div>\s*}{}s;
        $body =~ s{<p>.*?</p>\s*}{}s;
        $body =~ s{</h3>}{</h3>\n        $svg{$id}}s;
        $a . $body . $c;
    }se;
    open my $out, '>', "quote/$id.html" or die "quote/$id.html: $!";
    print $out $copy;
    close $out;
    print "scritto quote/$id.html\n";
}
