#!/usr/bin/perl
# $Id: pxref.perl,v 1.1 2012-01-19 18:49:53-08 - - $
use strict;
use warnings;

$0 =~ s|^.*/||;
my $exit_status = 0;
END {exit $exit_status}
sub note(@) {print STDERR "@_"};
$SIG{'__WARN__'} = sub {note @_; $exit_status = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

my $sep = ":" x 32;
push @ARGV, "-" unless @ARGV;

for my $filename (@ARGV) {
   my %xref;
   open my $file, "<$filename" or warn "$0: $filename: $!\n" and next;
   while (defined (my $line = <$file>)) {
      push @{$xref{$1}}, $. while $line =~ s|^.*?(\w+([-'.:/]\w+)*)||;
   }
   close $file;
   print "$sep\n$filename\n$sep\n";
   printf "%s [%d] %s\n", $_, @{$xref{$_}} + 0, join " ", @{$xref{$_}}
          for sort keys %xref;
}

