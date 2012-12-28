<?php
/**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: AbstractGrammar.php,v 1.0 bdetweiler Exp $
 * @package necktie
 */

/**
 */
require_once 'IGrammar.php';
require_once 'Opus11/SetAsArray.php';
require_once 'Opus11/DenseMatrix.php';

//{
/**
 * Abstract base class from which all tree classes are derived.
 *
 * @package Opus11
 */
abstract class AbstractGrammar
    implements IGrammar
{

    /**
     * The Grammar, laid out as a DenseMatrix
     */
    protected $grammar = null;

    /**
     * The set of terminals, laid out as a SetAsArray
     */
    protected $terminals = null;

    /**
     * The set of nonTerminals, laid out as a SetAsArray
     */
    protected $nonTerminals = null;

    /**
     * The set of nonTerminals, laid out as a SetAsArray
     */
    protected $nullables = null;

//}@head

//{
//!    // ...
//!}
//}@tail

    /**
     * Constructor.
     *
     * Takes a grammar in this format:
     *
     * nonterminal          -> othernonterminal TERMINAL
     * nonterminal          -> <epsilon>
     * othernonterminal     -> 'literal'
     * 
     * eg:
     * ________________________________
     * program              -> function    program             
     * program              -> <epsilon>                  
     * ________________________________
     *
     *
     * Rules: - MUST be in Backus-Nauer Format
     *        - nonterminals are lowercase
     *        - terminals are all caps
     *        - epsilons are <epsilon>
     *        - use the -> operator to assign a list of terminals and nonterminals to a nonterminal
     *        - literals are singal-quoted
     *        - each rule is separated with a new line character '\n'
     */
    public function __construct($grammar = null)
    { 
        $this->nonTerminals = array();
        $this->terminals = array();
        $this->nullables = array();

        if($grammar != null)
        {
            $this->setGrammar($grammar);
        }

        // Get the set of nonTerminals (everything on the lefthand side)
        for($i = 0; $i < count($this->grammar); ++$i)
            if(!in_array($this->grammar[$i][0], $this->nonTerminals))
                array_push($this->nonTerminals, $this->grammar[$i][0]);

        // Get the set of terminals (everything on the rhs that isn't on the lhs)
        for($i = 0; $i < count($this->grammar); ++$i)
            for($j = 1; $j < count($this->grammar[$i]); ++$j)
                if(!in_array($this->grammar[$i][$j], $this->nonTerminals) && 
                   !in_array($this->grammar[$i][$j], $this->terminals)    &&
                   $this->grammar[$i][$j] != "<epsilon>")
                    array_push($this->terminals, $this->grammar[$i][$j]);

        
        // Knuth's algorithm for finding nullables
        $oldSize = 0;
        do
        {
            $oldSize = count($this->nullables);
            for($p = 0; $p < count($this->grammar); ++$p)
            {
                $allNull = false;
                for($t = 1; $t < count($this->grammar[$p]); ++$t)
                {
                    if($this->grammar[$p][$t] == '<epsilon>' &&
                       !in_array($this->grammar[$p][$t], $this->nullables))
                    {
                        $allNull = true;
                    }
                }

                if($allNull)
                {

                    if(in_array($this->grammar[$p][0], $this->nonTerminals) && 
                       !in_array($this->grammar[$p][0], $this->nullables))
                    {
                        array_push($this->nullables, $this->grammar[$p][0]);
                    }
                }
            }
        } while(count($this->nullables) > $oldSize);
    } 

    // TODO: This is not working
    public function reachable($start)
    {
        $reachable = array();
        array_push($reachable, $start);
        $oldSize = 0;
        do
        {
            $oldSize = count($reachable);
            // Iterate over all the "reachables" we compiled
            foreach($reachable as $node)
            {
                for($i = 0; $i < count($this->grammar); ++$i)
                {
                    // Iterate over each production rule matching the current node
                    if($node == $this->grammar[$i][0])
                    {
                        // If the first element is a terminal, add it to the list and continue
                            // Iterate over each element of this production rule
                            for($j = 1; $j < count($this->grammar[$i]); ++$j)
                            {
                                // If it's not already in the "reachable" set
                                if(!in_array($this->grammar[$i][$j], $reachable))
                                {
                                    // Found a terminal
                                    if(in_array($this->grammar[$i][$j], $this->terminals))
                                    {
                                            if($reachable[$k] == $this->grammar[$i][0])
                                                $reachable[$k] = $this->grammar[$i][$j];
                                        // array_push($reachable, $this->grammar[$i][$j]);
                                        break;
                                    }
                                    // We know it's a nonTerminal. If it's not nullable, push it and break.
                                    else if(!in_array($this->grammar[$i][$j], $this->nullables))
                                    {
                                        array_push($reachable, $this->grammar[$i][$j]);
                                        break;
                                    }
                        /*
                                    // If this non-terminal and it's not-nullable, follow it
                                    if(in_array($this->grammar[$i][$j], $this->nonTerminals) 
                                       && !in_array($this->grammar[$i][$j], $this->nullables))
                                    {
                                        array_push($reachable, $this->grammar[$i][$j]);
                                    }
                                    else if(in_array($this->grammar[$i][$j], $this->terminals))
                                    {
                                        array_push($reachable, $this->grammar[$i][$j]);
                                    }
                                    break;
                                }
                    */
                            }
                        }
                    }
                }
            }
        } while(count($reachable) > $oldSize);

        return $reachable;
    }

    /**
     * Destructor.
     */
    public function __destruct()
    { 
        $this->grammar = null;
    }

    /**
     * To String.
     * Defines how a Grammar will be printed
     */
    public function __tostring()
    { 

        // Get lengths of strings
        $maxNonTerminalLen = 0;
        $nonTerminalLenArr = array();
        for($i = 0; $i < count($this->grammar); ++$i)
        {
            if(strlen($this->grammar[$i][0]) > $maxNonTerminalLen)
                $maxNonTerminalLen = strlen($this->grammar[$i][0]);
            $nonTerminalLenArr[$i] = strlen($this->grammar[$i][0]);
        }

        for($i = 0; $i < count($this->grammar); ++$i)
        {
            for($j = 0; $j < count($this->grammar[$i]); ++$j)
            {

                if($j == 1)
                {
                    for($k = strlen($this->grammar[$i][0]); $k < $maxNonTerminalLen; ++$k)
                        print(" ");

                    print("-> ");
                }

                print($this->grammar[$i][$j]);
                print(" ");
            }
            printf("\n");
        }
    }
//{


    /**
     * Takes a grammar in this format:
     *
     * nonterminal          -> othernonterminal TERMINAL
     * nonterminal          -> <epsilon>
     * othernonterminal     -> 'literal'
     * 
     * eg:
     * ________________________________
     * program              -> function    program             
     * program              -> <epsilon>                  
     * ________________________________
     *
     *
     * Rules: - MUST be in Backus-Nauer Format
     *        - nonterminals are lowercase
     *        - terminals are all caps
     *        - epsilons are <epsilon>
     *        - use the -> operator to assign a list of terminals and nonterminals to a nonterminal
     *        - literals are singal-quoted
     *        - each rule is separated with a new line character '\n'
     *
     * @param string $grammar The CORRECTLY FORMATTED grammar to parse
     * @return none
     */
    public function setGrammar($grammar)
    {
        $grammarMatrix = array(array());

        $breakLines = explode("\n", $grammar);

        $count1 = 0;

        for($i = 0; $i < count($breakLines); ++$i)
        {
            $breakSpaces = explode(" ", trim($breakLines[$i]));

            if(trim($breakSpaces[0]))
            {
                $grammarMatrix[$count1][0] = $breakSpaces[0];

                $count2 = 1;
                for($j = 1; $j < count($breakSpaces); ++$j)
                {
                    if(trim($breakSpaces[$j]) && trim($breakSpaces[$j]) != "->")
                    {
                        $grammarMatrix[$count1][$count2] = $breakSpaces[$j];
                        ++$count2;
                    }
                }

                ++$count1;
            } 
        }
     
        $this->grammar = $grammarMatrix;
    } 

    /**
     * Gets the start symbol of the grammar
     *
     * @param string $nonTerminal The non terminal for which to find the first set
     * @return object SetAsArray $firstSet The set of items in the first set of $nonTerminal
     */
    public function startSymbol()
    {
        return $this->grammar[0][0];
    }

    public function isTerminal($symbol)
    {
        return(in_array($symbol, $this->terminals));
    }


    public function isIdentifier($symbol)
    {
        $rval = true;

        if(in_array($symbol, $this->terminals))
            $rval = false;

        if(in_array($symbol, $this->nonTerminals))
            $rval = false;
        
        $tmp = str_split($symbol);
        if(is_numeric($tmp[0]))
            $rval = false;

        return $rval;
    }

    public function isInteger($symbol)
    {
        $rval = false;

        if(is_numeric($symbol))
            $rval = true;

        return $rval;
    }

    public function isString($symbol)
    {
        $rval = false;

        $tmp = str_split($symbol);
        if($tmp[0] == '"' &&
           $tmp[count($tmp) - 1] == '"') 
            $rval = true;

        return $rval;
    }

    public function isNonTerminal($symbol)
    {
        return(in_array($this->nonTerminals, $symbol));
    }

    /**
     * Gets the first set of the $nonTerminal
     *
     * @param string $nonTerminal The non terminal for which to find the first set
     * @return object SetAsArray $firstSet The set of items in the first set of $nonTerminal
     */
    public function first($nonTerminal)
    {

    }

    /**
     * Gets the follow set of the $nonTerminal
     *
     * @param string $nonTerminal The non terminal for which to find the follow set
     * @return object SetAsArray $followSet The set of items in the follow set of $nonTerminal
     */
    public function follow($nonTerminal)
    {

    }

    /**
     * Gets the select set of the $nonTerminal
     *
     * @param int $rule The rule number to look up
     * @return object SetAsArray $followSet The set of items in the select set of $rule
     */
    public function select($rule)
    {
        
    }

    /**
     * Gets the lookAhead rule of the $nonTerminal for 
     *
     * @param string $nonTerminal The non terminal for which to find the select set rule number
     * @param string $terminal The terminal for which to find the select set rule number
     * @return object SetAsArray $followSet The set of items in the select set of $rule
     */
    public function lookAhead($nonTerminal, $terminal)
    {
        
    }


    /**
     * Main program.
     *
     * @param array $args Command-line arguments.
     * @return integer Zero on success; non-zero on failure.
     */
    public static function main($args)
    {
        printf("AbstractGrammar main program.\n");
        $status = 0;
        return $status;
    }
}

if (realpath($argv[0]) == realpath(__FILE__))
{
    exit(AbstractGrammar::main(array_slice($argv, 1)));
}
?>
