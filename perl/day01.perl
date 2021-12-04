#!/usr/bin/env perl
use strict;
use warnings;
require "./utils.perl";

my @ex01_example = (199, 200, 208, 210, 200, 207, 240, 269, 260, 263);
my @ex01_input = &readtable("../input/01");

sub ex01_work {
  my ($xs, $n) = @_;
  my $total = 0;
  for (my $i = $n; $i <=$#$xs; $i++) {
    if ($$xs[$i - $n][0] < $$xs[$i][0]) {
      $total++;
    }
  }
  $total
}

sub ex01 {
  my $xs = \@ex01_input;

  my @ex01_result = (&ex01_work($xs,1), &ex01_work($xs, 3));
  print "Day 01: @ex01_result\n";
}

&ex01();
1;


