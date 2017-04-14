#!/usr/bin/perl -w
# x.pl
#

# output methods
#-----------------------------------------------------------

## expression output
#print grep { !/^(tcp|udp)/ } `netstat -an 2>&1`;

## piped output
#print `netstat -an 2>&1 |grep -v tcp|grep -v udp`;

#-----------------------------------------------------------
# file handle output

open STATUS, "ls 2>&1 |"
	or die "can't fork: $!";

while (<STATUS>) {
	##one way
	#chop #and split(/[ ]+/);
	next if $_ =~ /(cgi)/;
	#print "$_\n";
	print `uudecode $_`;

	##another way
	#($perm,$ftype,$own, $grp, $size, $mth, $day, $time, $file)=split(/[ ]+/);
	#print "<A HREF=\"./$file\">$_</A>\n"; 
}
close STATUS or die "bad netstat: $! $?";

