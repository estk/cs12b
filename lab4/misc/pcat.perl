#!/usr/bin/perl
# $Id: pcat.perl,v 1.3 2012-01-31 18:12:24-08 - - $
use strict;
use warnings;
use Getopt::Std;

$0 =~ s|^.*/||;
my $exit_status = 0;
END {exit $exit_status}
sub note(@) {print STDERR "@_"};
$SIG{'__WARN__'} = sub {note @_; $exit_status = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

my %opts;
getopts "mns", \%opts;
my $colons = ":" x 64;
my $s_count = 0;

for my $filename (@ARGV ? @ARGV : '-') {
   open my $file, "<$filename" or warn "$0: $filename: $!\n" and next;
   print "\n$colons\n$filename\n$colons\n\n" if $opts{'m'};
   while (defined (my $line = <$file>)) {
      next if $opts{'s'}
           and ($s_count = $line =~ m/^\n$/ ? $s_count + 1 : 0) >= 2;
      printf "%6d  ", $. if $opts{'n'};
      print $line;
   }
   close $file;
}

