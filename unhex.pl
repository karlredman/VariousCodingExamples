#!/usr/bin/perl -w

use strict

open FD, "dumpfile";

while ($line = <FD>)
{
	chomp $line;

	@thing = split ' ', $line;
}
close FD;

for $ch (@thing)
{
	printf("%c", hex($ch));
}
