use strict; use warnings;
binmode STDOUT;

my $in  = 'C:/Users/Admin/Documents/Qoder/2026-10-30/dfa27f31/nanoels-h5/screen-it/h5_it.HMI';
my $out = 'C:/Users/Admin/Documents/Qoder/2026-10-30/dfa27f31/nanoels-h5/screen-it/h5_it_patched.HMI';

open my $fh, '<:raw', $in or die "open: $!";
local $/; my $d = <$fh>; close $fh;

my @err;

sub put {
    my ($off, $old, $new) = @_;
    my $cur = substr($d, $off, length($old));
    if ($cur ne $old) {
        push @err, sprintf("MISMATCH @%d expected [%s] found [%s]", $off, $old, $cur);
        return;
    }
    if (length($old) != length($new)) {
        push @err, sprintf("LEN @%d old=%d new=%d", $off, length($old), length($new));
        return;
    }
    substr($d, $off, length($new)) = $new;
}

# 1) pill MENU sulle 12 pagine modalita': page 2 -> page 0
for my $o (7342532, 7343822, 7399806, 7401096, 7402386, 7403676,
           7539842, 7541133, 7542424, 7596639, 7597930, 7599221) {
    put($o, 'page 2', 'page 0');
}

# 2) card del menu: m0..m13
my @old = ('page 3','page 4','page 5','page 6','page 7','page 8','page 9',
           'page 10','page 11','page 12','page 13','page 14','page 0','page 11');
my @new = ('page 1','page 2','page 3','page 4','page 5','page 6','page 7',
           'page 8 ','page 9 ','page 10','page 11','page 12','page 0','page 9 ');

my @blocks = (
    [7428133,7428642,7429151,7429660,7430169,7430678,7431187,7431696,7432206,7432716,7433227,7433738,7434249,7434759],
    [7756107,7756616,7757125,7757634,7758143,7758652,7759161,7759670,7760180,7760690,7761201,7761712,7762223,7762733],
    [9839090,9839599,9840108,9840617,9841126,9841635,9842144,9842653,9843163,9843673,9844184,9844695,9845206,9845716],
);

for my $b (@blocks) {
    for my $i (0..13) {
        put($b->[$i], $old[$i], $new[$i]);
    }
}

if (@err) { print "ERRORI:\n", join("\n", @err), "\n"; exit 2; }

open my $o, '>:raw', $out or die "write: $!";
print $o $d; close $o;
print "OK scritto $out (", length($d), " byte)\n";
