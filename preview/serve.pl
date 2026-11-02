use strict;
use warnings;
use HTTP::Daemon;
use HTTP::Response;

my $port = $ARGV[0] || 8765;
my $daemon = HTTP::Daemon->new(LocalAddr => '127.0.0.1', LocalPort => $port, ReuseAddr => 1)
  or die "Impossibile aprire la porta $port: $!";
print "http://127.0.0.1:$port/\n";
$| = 1;

while (my $client = $daemon->accept) {
  while (my $request = $client->get_request) {
    my $path = $request->uri->path;
    $path = '/webui-preview.html' if $path eq '/' || $path eq '/index.html';
    (my $file = $path) =~ s{^/}{};
    if (-f $file) {
      my $body = do {
        local $/;
        open my $fh, '<', $file or die "Apertura $file fallita: $!";
        <$fh>;
      };
      my $response = HTTP::Response->new(200);
      $response->header('Content-Type' => 'text/html; charset=utf-8');
      $response->header('Cache-Control' => 'no-store');
      $response->content($body);
      $client->send_response($response);
    } else {
      my $response = HTTP::Response->new(404);
      $response->content('File non trovato');
      $client->send_response($response);
    }
  }
  $client->close;
  undef $client;
}
