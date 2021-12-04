#!/usr/bin/env perl
use strict;
use warnings;
use 5.010;
no warnings 'experimental';
require "./utils.perl";

my @ex02_input = &readtable("../input/02");

sub ex02a_work {
  my ($xs) = @_;
  my $depth = 0;
  my $hor = 0;

  foreach(@$xs) {
    my ($dir, $x) = @$_;
    given($dir) {
      when ($_ eq "forward") {
        $hor += $x;
      }
      when ($_ eq "up") {
        $depth -= $x;
      }
      when ($_ eq "down") {
        $depth += $x;
      }
    }
  }
  $depth * $hor
}

sub ex02b_work {
  my ($xs) = @_;
  my $depth = 0;
  my $hor = 0;
  my $aim = 0;

  foreach(@$xs) {
    my ($dir, $x) = @$_;
    given($dir) {
      when ($_ eq "forward") {
        $depth += $x * $aim;
        $hor += $x;
      }
      when ($_ eq "up") {
        $aim -= $x;
      }
      when ($_ eq "down") {
        $aim += $x;
      }
    }
  }
  $depth * $hor
}

sub ex02 {
  my ($xs) = \@ex02_input;
  my @ex02_result = (&ex02a_work($xs), &ex02b_work($xs));
  print "Day 02: @ex02_result\n";
}

ex02();
1;

