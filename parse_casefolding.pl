#!/usr/bin/env perl

# This file parses the Unicode CaseFolding rules as defined in
# http://unicode.org/Public/UNIDATA/CaseFolding.txt
# and outputs the src/utf_data.h header file.
# It should not be needed to build the software, but can be used to
# regenerate src/utf_data.h or change it's format.

use warnings;
use strict;
use List::MoreUtils;

open my $cf, "<", "res/CaseFolding.txt"
  or die "Could not open CaseFolding-Rules File. At res/CaseFolding.txt\n",
         "Check if it exists or download it from:\n",
         "http://unicode.org/Public/UNIDATA/CaseFolding.txt\n";

open my $src, ">", "src/utf_data.h"
  or die "Could not create source file src/utf_data.h\n";

# Structure ((code, (mappings)))
my @folds = ();

make_head();
while(<$cf>) {
  chomp;
  next if /^#/ or /^$/;
  if(my ($code, $mappings) = /^([0-9A-F]+);\s[CFST];((?:\s[0-9A-F]+)+)/i) {
    push @folds, [(hex $code, [map(hex, split(' ', $mappings))])];
  }
}
set_codes();
set_mappings();
make_foot();

sub make_head {
  print $src "#ifndef UTF_DATA_H\n";
  print $src "#define UTF_DATA_H\n";
  print $src "#include \"utf8.h\"\n";
  print $src "#include <stdlib.h>\n\n";
  print $src "#define map(...) ";
  print $src "(codepoint[]) {__VA_ARGS__, CODEPOINT_SENTINEL}\n\n";
}

sub make_foot {
  print $src "#endif\n";
}

sub set_codes {
  print $src "static codepoint codes[] = {";
  my $it = List::MoreUtils::natatime(8, @folds);
  local $" = ", ";
  while(my @mappings = $it->()) {
    my @codes = map {${$_}[0]} @mappings;
    print $src "\n\t@codes,";
  }
  print $src "\n\tCODEPOINT_SENTINEL";
  print $src "};\n\n";
}

sub set_mappings {
  printf $src "static codepoint* mappings[%d] = {\n", @folds;
  local $" = ", ";
  for my $i (0 .. $#folds) {
    print $src "\tmap(@{@{$folds[$i]}[1]}),\n";
  }
  print $src "};\n";
}
