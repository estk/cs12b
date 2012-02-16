#!/usr/bin/perl
# $Id: cooksortdb.perl,v 1.2 2012-02-07 15:47:22-08 - - $
#
# Cook the database order so that linear insertion produces a
# balanced tree.  Balancing a BST is not included in this course.
#

use strict;
use warnings;
system "cid $0";

$0 =~ s|^(.*/)?([^/]+)/*$|$2|;
my $EXITCODE = 0;
END {exit $? || $EXITCODE}
sub note(@) {print STDERR "$0: @_"}
$SIG{'__WARN__'} = sub {note @_; $EXITCODE = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

sub cooksort ($$$$);
sub cooksort ($$$$) {
   my ($outfile, $lo, $hi, $arrayref) = @_;
   return unless $lo <= $hi;
   my $mid = int (($lo + $hi) / 2);
   print $outfile $arrayref->[$mid];
   cooksort $outfile, $lo, $mid - 1, $arrayref;
   cooksort $outfile, $mid + 1, $hi, $arrayref;
}

sub openfile ($) {
   my ($filespec) = @_;
   open my $file, $filespec or do {warn "$filespec: $!"; return undef};
   print "$0: open $filespec: OK\n";
   return $file;
}

for my $infilename (<*.db.sorted>) {
   system "cid $infilename";
   my $outfilename = $infilename;
   $outfilename =~ s/\.sorted$//;
   system "cid + $infilename";
   my $infile = openfile "<$infilename";
   my $outfile = openfile ">$outfilename";

   if ($infile && $outfile) {
      my @airports;
      while (defined (my $line = <$infile>)) {
         if ($line =~ m/^\s*(#|$)/) {print $outfile $line}
                               else {push @airports, $line}
      }
      @airports = sort @airports;
      cooksort $outfile, 0, $#airports, \@airports;
   }

   close $infile if $infile;
   close $outfile if $outfile;
}
