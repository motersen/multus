#!/usr/bin/env perl

use strict;
use warnings;

use File::Find;

my $src_dir = 'src/';
my $obj_dir = 'obj/';
my $bin_dir = 'bin/';
my $rules_file = 'makerules.mk';
my $src_ext = 'c';
my $header_ext = 'h';
my $obj_ext = 'o';
my $header_format = qr/\w+\.$header_ext/;
my $bin = "${bin_dir}multus";

my $targets = scan_sources();
make_rules($targets, $rules_file);

sub scan_sources {
  my %targets;
  find(sub {
      if(is_source($_)) {
        $targets{$File::Find::name} = list_deps($File::Find::name);
      }
    }, $src_dir);
  return \%targets;
}

sub is_source {
  (shift) =~ /\w+\.$src_ext$/;
}

sub list_deps {
  my @all_deps;
  file_deps($_, \@all_deps);
  return \@all_deps;
}

sub file_deps {
  my ($file, $deps_ref) = @_;
  open my $dep, "<", $file or warn "File could not be opened:$file\n";
  no warnings "closed";
  while(<$dep>) {
    if(/^\#include\h+['"]($header_format)['"]/ and not grep(/^$src_dir$1$/, @$deps_ref)) {
      push @$deps_ref, $src_dir.$1;
      file_deps($1, $deps_ref);
    }
  }
  close $dep;
}

sub make_rules {
  my ($targets, $filename) = @_;
  my @objects = map {
    src2obj($_);
  } (keys %$targets);
  open my $file, ">", $filename or die "Error opening Rules-File: $!";
  make_bin($file, \@objects);
  while(my ($key, $val) = each %$targets) {
    make_obj($file, $key, $val);
  }
  make_dirs($file);
  make_clean($file);
  make_new($file);
  close $file;
}

sub make_bin {
  my ($file, $deps) = @_;
  print $file "$bin: @$deps | $bin_dir\n";
  print $file "\t".'$(CC) $(CFLAGS)'." -o $bin @$deps ".'$(LIBS)'."\n\n";
}

sub make_obj {
  my ($file, $src, $deps) = @_;
  my $obj = src2obj($src);
  print $file "$obj: $src @$deps | $obj_dir\n";
  print $file "\t".'$(CC) $(CFLAGS) $(INCLUDE)'." -c -o $obj $src\n\n";
  return $obj;
}

sub make_dirs {
  my $file = shift;
  for my $dir ($bin_dir, $obj_dir) {
    print $file "$dir:\n",
                "\tmkdir -p $dir\n\n";
  }
}

sub make_clean {
  my $file = shift;
  print $file "clean:\n";
  print $file "\trm -rf $rules_file $obj_dir $bin_dir\n\n";
}

sub make_new {
  my $file = shift;
  print $file "new: clean $bin\n\n";
}

sub src2obj {
  (shift) =~ s/$src_dir(\w+\.)$src_ext/$obj_dir$1$obj_ext/r;
}
