#!/usr/bin/php
<?php
require_once 'Parser.php';
if(realpath($argv[0]) == realpath(__FILE__))
{
    exit(Parser::main($argv[1]));
}
?>
