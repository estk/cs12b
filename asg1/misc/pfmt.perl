#!/usr/bin/perl
# $Id: pfmt.perl,v 1.4 2012-01-05 19:14:21-08 - - $
use strict;
use warnings;

$0 =~ s|^.*/||;
my $exit_status = 0;
END {exit $exit_status}
sub note(@) {print STDERR "@_"};
$SIG{'__WARN__'} = sub {note @_; $exit_status = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

my $linelen = 65;
if (@ARGV and $ARGV[0] =~ m/^-(.+)/) {
   $linelen = $1;
   die "Usage: $0 [-width] [filename...]\n" if $linelen =~ m/\D/;
   shift @ARGV
}

sub print_paragraph (@) {
   my (@words) = @_;
   print "\n";
   my $char_count = 0;
   for my $word (@words) {
      if ($char_count == 0) {
         print $word;
         $char_count = length $word;
      }else {
         $char_count += 1 + length $word;
         if ($char_count > $linelen) {
            print "\n", $word;
            $char_count = length $word;
         }else {
            print " ", $word;
         }
      }
   }
   print "\n" if $char_count > 0;
}

push @ARGV, "-" unless @ARGV;
for my $filename (@ARGV) {
   open my $file, "<$filename" or warn "$0: $filename: $!\n" and next;
   my @output_words;
   for (;;) {
      my $input_line = <$file>;
      last unless defined $input_line;
      my @input_words = split " ", $input_line;
      if (@input_words) {
         push @output_words, @input_words;
      }else {
         print_paragraph @output_words if @output_words;
         @output_words = ();
      }
   }
   print_paragraph @output_words;
   close $file;
}

