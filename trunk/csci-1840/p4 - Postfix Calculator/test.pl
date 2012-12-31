#!/usr/bin/perl

# the first argument to this script will be used as 
# the postfix calculator program 

$calc = $ARGV[0];

sub func 
{
    $input = $_[0];
    $ans = $_[1];
    $cmd = "printf \" " . $input . "\" | ./" . $calc;
    $tmp = `$cmd`;
    print $cmd , "\n", $tmp, " -->answer should be ", $ans,  "\n\n";
}

func( "2 3 + 5 *", 25 );
func( "2 3 + 5 * 4 /", 6.25 );
func( "2 3 ^ 5 / 7 -", -5.4 );
func( "2 3 5 7 ^ / -", 1.999962 );
func( "2 0 /", "ERROR" );
func( "2 3 5 * +", 17 );
func( "12 158 16 / -", 2.125 );
func( "2 3 + 5 -", 0 );
