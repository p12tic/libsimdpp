#!/usr/bin/perl

#   Copyright (C) 2014  Michal Fapso <michal.fapso@gmail.com>
#
# Distributed under the Boost Software License, Version 1.0.
#   (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

use strict;
use Data::Dumper;

my @config = ();

#--------------------------------------------------
# CONFIG
#--------------------------------------------------
sub add_to_config
{
	glob @config;
	my $file = shift;
	my $fun  = shift;
	my $op   = shift;
	my $rx   = shift; $rx ||= '\b'.$fun.'\b';
	my %hash = (
		"file"     => $file,
		"fun"      => $fun,
		"op"       => $op,
		"rx"       => $rx
	);
	push @config, \%hash;
}

add_to_config("i_shift_l.h", "shift_l", "<<", '\bshift_l\b.*\bcount\b');
add_to_config("cmp_eq.h" , "cmp_eq" , "==");
add_to_config("cmp_neq.h", "cmp_neq", "!=");
add_to_config("cmp_ge.h" , "cmp_ge" , ">=");
add_to_config("cmp_gt.h" , "cmp_gt" , ">" );
add_to_config("cmp_le.h" , "cmp_le" , "<=");
add_to_config("cmp_lt.h" , "cmp_lt" , "<" );
add_to_config("f_add.h", "add", "+");
add_to_config("i_add.h", "add", "+");
add_to_config("f_sub.h", "sub", "-");
add_to_config("i_sub.h", "sub", "-");
add_to_config("f_mul.h", "mul"   , "*");
add_to_config("i_mul.h", "mul_lo", "*");
add_to_config("f_div.h", "div", "/");
add_to_config("bit_or.h"     , "bit_or"     , "|" );
add_to_config("bit_and.h"    , "bit_and"    , "&" );
add_to_config("bit_not.h"    , "bit_not"    , "!" );
add_to_config("bit_xor.h"    , "bit_xor"    , "^" );

#print Dumper(@config);

#--------------------------------------------------
# PROCESS FILES
#--------------------------------------------------
foreach my $rec (@config)
{
	#print Dumper($rec);

	my $curly_braces_counter = 0;
	my %types = ();
	mkdir "../simdpp/operator/";
	my $file_out = "../simdpp/operator/".$rec->{file};
	my $file_in  = "../simdpp/core/".$rec->{file};
	open FILE_OUT, ">", $file_out or die "Unable to open the file '$file_out'";
	open FILE_IN , "<", $file_in  or die "Unable to open the file '$file_in'";

	my $header_ifdef = "";

	# Copy the original source file, replacing its function names with operators
	while (<FILE_IN>)
	{
		chomp;
		my $opening_braces = () = $_ =~ /{/gi;
		my $closing_braces = () = $_ =~ /}/gi;

		if ($_ =~ /#(ifndef|define) LIBSIMDPP_SIMDPP_.*_H/) {
			#$_ =~ s/(#(ifndef|define) LIBSIMDPP_SIMDPP_.*)_H/'"$1_OPERATOR_H"'/ee;
			$_ =~ s/_H\b/_OPERATOR_H/;
			($header_ifdef) = $_ =~ /(LIBSIMDPP_SIMDPP_.*)/;
		}

		# Workaround: mul_hi in i_mul.h has to be disabled, because it is not used for an operator
		if ($rec->{file} == "i_mul.h" && $_ =~ /\bmul_hi\b/ && $_ !~ /#include/) {
			$_ =~ s/\bmul_hi\b/mul_hi_DISABLED/;
		}

		if ($_ =~ /\b$rec->{fun}\b/ && $_ !~ /#include/) {
			if ($_ =~ $rec->{rx}) {
				#print "$_\n";
				(my $type) = $_ =~ /((any_){0,1}(float|int|vec)[0-9].*?\b)/;
				#(my @a) = $_ =~ /((any_){0,1}(float|int)[0-9].*?\b)/;
				#my $type = $a[0];
				#print Dumper(@a);
				#print "$type\n";
				$types{$type} = 1;
				$_ =~ s/\b$rec->{fun}\b/operator$rec->{op}/;
			} else {
				$_ =~ s/\b$rec->{fun}\b/$rec->{fun}_DISABLED/; # Disable functions which don't match the specified regex
			}
		}

		#if ($_ =~ )
		print FILE_OUT "$_\n";
	}

	# Add operators with mixed vectors and scalars
	if ($rec->{file} !~ /_shift_/ &&
		$rec->{file} !~ /bit_not/)
	{
		$header_ifdef =~ s/_H\b/_MIX_H/;

		print FILE_OUT "
		#ifndef $header_ifdef
		#define $header_ifdef

		namespace simdpp {
		#ifndef SIMDPP_DOXYGEN
		namespace SIMDPP_ARCH_NAMESPACE {
		#endif
		";
		
		if ($rec->{file} =~ /bit_/) {
			%types = ("any_int64"=>1, "any_int32"=>1, "any_int16"=>1, "any_int8"=>1, "any_float32"=>1, "any_float64"=>1);
		}
		foreach my $any (keys(%types)) {
			my $noany = $any;
			$noany =~ s/^any_//;
			my $scalar = $noany;
			$scalar =~ s/[0-9]*$//;
			my $ret = $rec->{file} =~ /cmp_/ ? "mask_$noany" : $noany;
			#(my $unused, my $scalar) = $type =~ /(any_){0,1}(^[a-z]*)/;
			#print "$any $noany $scalar\n";
		
			print FILE_OUT "
			template<unsigned N, class V>
			$ret<N> operator$rec->{op}(const $scalar& a, const any_$noany<N, V>& b) {
				return ($noany<N>)make_int(a) $rec->{op} b.wrapped();
			}
			template<unsigned N, class V>
			$ret<N> operator$rec->{op}(const any_$noany<N, V>& a, const $scalar& b) {
				return a.wrapped() $rec->{op} ($noany<N>)make_int(b);
			}
		
			";
		}
		
		print FILE_OUT "
		#ifndef SIMDPP_DOXYGEN
		} // namespace SIMDPP_ARCH_NAMESPACE
		#endif
		} // namespace simdpp

		#endif
		";
	}

	close FILE_IN;
	close FILE_OUT;

}

