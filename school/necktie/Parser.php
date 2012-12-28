<?php
/**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: Parser.php, Exp $
 * @package Necktie
 */

//{
/**
 * Take an array from the Scanner and puts it into a parse tree
 *
 * @package Necktie
 */

// require_once 'ParseTree.php';
require_once 'AbstractGrammar.php';
require_once 'IGrammar.php';
require_once 'NECTJGrammar.php';
require_once 'Scanner.php';

class Parser
{

    private $NECTJGrammar  = null;

    /**
     * Constructs a Parser
     *
     */
    public function __construct()
    {
        $this->NECTJGrammar  = new NECTJGrammar();
    }

    /**
     * Destructor.
     */
    public function __destruct()
    {
        $this->NECTJGrammar  = null;
    }

    /**
     * Takes a scanned file in array form and returns a perse tree of it.
     *
     * @param string $filename
     *
     * @return ParseTree $parsed_file
     */
    public function parse($program = null)
    {
        $stack = array();

        // Push start symbol
        array_push($stack, $this->NECTJGrammar->startSymbol());

        // while stack not empty
        while(count($stack))
        {
            $symbol = array_pop($stack);
            if($this->NECTJGrammar->isTerminal($symbol))
            {
                // Match
                array_shift($program);
            }
            else if($symbol == '<epsilon>')
            {
                ;;;
            }
            else if(count($program))
            {

                if($this->NECTJGrammar->isIdentifier($program[0]))
                {
                    $program[0] = "IDENTIFIER";
                }
                else if($this->NECTJGrammar->isInteger($program[0]))
                {
                    $program[0] = "INTEGER";
                }
                else if($this->NECTJGrammar->isString($program[0]))
                { 
                    $program[0] = "STRING";
                }
                $rule = $this->NECTJGrammar->getRule($symbol, $program[0]);

                if(!is_array($rule))
                    die("INVALID SYNTAX. Actually, it probably is valid. My grammar is broke. :-(\n");
                array_shift($rule);

                while(count($rule))
                    array_push($stack, array_pop($rule));
            }
        }
    }

    /**
     * Main program.
     *
     * @param array $args Command-line arguments.
     * @return integer Zero on success; non-zero on failure.
     */
    public static function main($filename)
    {
        $scanner = new Scanner();
        $parser = new Parser();

        $parser->parse($scanner->scan($filename));

        printf("Parser main program.\n");

        $status = 0;
        return $status;
    }
}

if(realpath($argv[0]) == realpath(__FILE__))
{
    exit(Parser::main($argv[1]));
}
?>
