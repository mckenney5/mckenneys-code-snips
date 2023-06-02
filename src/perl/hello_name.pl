# Perl
# Asks for the users name then says hello
# to run: perl -e perl.pl

use strict; # disables some features (good practice but not needed)
use warnings; # turns on all warnings (good practice but not needed)

sub main{
	# prompt
	print "Enter your name: ";
	
	# get user input
	my $name = <STDIN>;

	# remove the last char (new line)
	chomp $name;

	# say hello
	print "Hello $name!\n";


}
main();

