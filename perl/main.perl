#!/usr/bin/env perl
use strict;
use warnings;

sub readtable {
  my ($file) = @_;
  my @result;
  open (my $csv, '<', $file) || die "can't open $file";
  foreach (<$csv>) {
     chomp;
     my @fields = split(/\,/);
     push @result, $fields[0];
  }
  return @result
}

my @ex01_example = (199, 200, 208, 210, 200, 207, 240, 269, 260, 263);
my @ex01_input = &readtable("../input/01");

sub ex01_work {
  my ($xs, $n) = @_;
  my $total = 0;
  for (my $i = $n; $i <=$#$xs; $i++) {
    if ($$xs[$i - $n] < $$xs[$i]) {
      $total++;
    }
  }
  $total
}

sub ex01 {
  my ($xs) = @_;

  (&ex01_work($xs,1), &ex01_work($xs, 3))
}

my @ex01_result = &ex01(\@ex01_input);
print "Day 01: @ex01_result\n";
