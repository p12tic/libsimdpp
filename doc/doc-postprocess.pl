package main;

# Copyright (c) 2009  Openismus GmbH  <http://www.openismus.com/>
#
# This file is part of mm-common.
#
# mm-common is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 2 of the License,
# or (at your option) any later version.
#
# mm-common is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with mm-common.  If not, see <http://www.gnu.org/licenses/>.

use strict;
use warnings;
use bytes;
use File::Glob qw(:glob);
use File::Spec;
use Getopt::Long qw(:config no_getopt_compat no_ignore_case require_order bundling);

sub path_basename ($)
{
  my ($path) = @_;
  my $basename = File::Spec->splitpath($path);

  return $basename;
}

sub exit_help ()
{
  my $script_name = path_basename($0) || 'doc-postprocess.pl';

  print <<"EOF";
Usage: perl $script_name [OPTION]... [PATTERN]...

Post-process the Doxygen-generated HTML files matching PATTERN.

Options:
  -?, --help                        display this help and exit
EOF
  exit;
}

sub error (@)
{
  my $script_name = path_basename($0);
  $script_name =~ s/\.[^.]*$//s if (defined $script_name);

  print STDERR ($script_name || 'doc-postprocess', ': ', @_, "\n");
  exit 1;
}

GetOptions('help|?' => \&exit_help)
  or exit 2;

foreach my $filename (map(bsd_glob($_, GLOB_NOSORT), @ARGV))
{
  my @buf;
  my $file;

  open($file, '<', $filename) and (@buf = <$file>) and close($file)
    or error('Failed to read ', path_basename($filename), ': ', $!);

  foreach (@buf)
  {
    if (/<a class="el"/)
    {
      # return value
      s/ &amp;&nbsp; */&amp;&#160;/;
      s/ \*&nbsp; */*&#160;/;

      # parameters
      s/ &amp;/&amp;/g;
      s/&amp;\b/&amp; /g;
      s/ \*/*/g;
      s/\*\b/* /g;

      # templates
      s/\btemplate&lt;/template &lt;/;
    }
    elsif (/<td class="md(?:name)?"/)
    {
      # left parenthesis
      s/\(&nbsp; */(/;

      # return value
      s/ &amp; /&amp; /g;
      s/ \* /* /g;

      # parameters
      s/ &amp;&nbsp; */&amp;&#160;/g;
      s/ \*&nbsp; */*&#160;/g;

      # templates
      s/\btemplate&lt;/template &lt;/;
    }
    else
    {
      # template decls
      s/^(<h\d>|)template&lt;/$1template &lt;/;
    }

    s/&copy;/&#169;/g;
    s/&mdash;/&#8212;/g;
    s/&ndash;/&#8211;/g;
    s/ *&nbsp; */&#160;/g;
    s/(?<=\S)\s{2,}/ /g;
  }

  # write the whole buffer back
  open($file, '>', $filename) and print $file (@buf) and close($file)
    or error('Failed to write ', path_basename($filename), ': ', $!);
}

exit;
