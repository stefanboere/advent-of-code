use strict;
use warnings;

sub readtable {
  my ($file) = @_;
  my @result;
  open (my $csv, '<', $file) || die "can't open $file";
  foreach (<$csv>) {
     chomp;
     my @fields = split(/\s/);
     push @result, \@fields;
  }
  return @result
}

1;
