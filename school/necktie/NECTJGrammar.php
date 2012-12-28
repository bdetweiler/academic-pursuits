<?php
/**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: NECTJGrammar.php, Exp $
 * @package Necktie
 */

//{
/**
 * Holds the definitions for the NECTJ grammar
 *
 * @package Necktie
 */

require_once 'IGrammar.php';
require_once 'AbstractGrammar.php';

class NECTJGrammar
    extends AbstractGrammar
    implements IGrammar
{

    /*                              The actual BNF grammar for NECTJ
     * XXX: I'm not positive on this, as it caused me quite a bit of headache, but I think
     *      I finally got in in LL(1) form. Or so says this site:
     *                                                              http://tr.im/finalNECTJ
     *      I also removed this rule: statement -> id = '(' params ')' because it didn't make sense.
     *      You could have this: x = (v, w, y, z) in the grammar, and that doesn't make sense to me 
     *      (Unless we're allowing sets or arrays, but I don't wanna do that. :-)
     */
    const GRAMMAR = "program               -> function    program\n
                     program               -> <epsilon>\n
                     function              -> FUNC IDENTIFIER  (  params  )  slist   ENDFUNC\n
                     params                -> IDENTIFIER  moreidentifiers\n
                     slist                 -> labeledstatement  ;    morelabeledstatements\n
                     labeledstatement      -> IDENTIFIER   fid\n
                     fid                   -> : statement\n
                     fid                   -> = expression\n
                     moreidentifiers       -> ,    IDENTIFIER  moreidentifiers\n
                     moreidentifiers       -> <epsilon>\n
                     statement             -> IDENTIFIER   =    expression\n
                     statement             -> READ     (    IDENTIFIER   )\n
                     statement             -> WRITE    (    idorstring   )\n
                     statement             -> IF   (    test     )    TO  IDENTIFIER\n
                     idorstring            -> IDENTIFIER\n
                     idorstring            -> STRING\n
                     test                  -> EQ  test2\n
                     test                  -> NE  test2\n
                     test                  -> TRUE\n
                     test                  -> LT  test2\n
                     test                  -> LE  test2\n
                     test                  -> GT  test2\n
                     test                  -> GE  test2\n
                     test2                 -> (    IDENTIFIER   ,    IDENTIFIER   )\n
                     expression            -> term fterm\n
                     fterm                 -> + expression\n
                     fterm                 -> - expression\n
                     fterm                 -> <epsilon>\n
                     term                  -> factor ffactor\n
                     ffactor               -> * term\n
                     ffactor               -> / term\n
                     ffactor               -> <epsilon>
                     factor                -> (    expression   )\n
                     factor                -> IDENTIFIER\n
                     factor                -> INTEGER\n
                     morelabeledstatements -> labeledstatement  ;    morelabeledstatements\n
                     morelabeledstatements -> <epsilon>";


    private $parseTable = null;


    /**
     * The First Sets, laid out as an array of SetAsArray's
     */
    private $firstSets = null;

    /**
     * The Follow Sets, laid out as an array of SetAsArray's
     */
    private $followSets = null;

    /**
     * The Select Sets, laid out as an array of SetAsArray's
     */
    private $selectSets = null;

    /**
     * The LookAhead Table, laid out as a DenseMatrix
     */
    private $lookAheadTable = null;

    /**
     * Constructs a NECTJGrammar
     */
    public function __construct()
    { 
        parent::__construct(self::GRAMMAR); 

        /* XXX: I realize this should be generated. But I'm running late, 
         *      so I'm just doing it by hand, since it's already been worked out.
         */
        $this->parseTable = array('program'                 => array('FUNC'         => 0,
                                                                     '<EOF>'        => 1),
                                  'function'                => array('FUNC'         => 2),
                                  'params'                  => array('IDENTIFIER'   => 3),
                                  'slist'                   => array('IDENTIFIER'   => 4),
                                  'labeledstatement'        => array('IDENTIFIER'   => 5),
                                  'fid'                     => array(':'            => 6,
                                                                     '='            => 7),
                                  'moreidentifiers'         => array(','            => 8,
                                                                     ')'            => 9),
                                  'statement'               => array('IDENTIFIER'   => 10,
                                                                     'READ'         => 11,
                                                                     'WRITE'        => 12,
                                                                     'IF'           => 13),
                                  'idorstring'              => array('IDENTIFIER'   => 14,
                                                                     'STRING'       => 15),
                                  'test'                    => array('EQ'           => 16,
                                                                     'NE'           => 17,
                                                                     'TRUE'         => 18,
                                                                     'LT'           => 19,
                                                                     'LE'           => 20,
                                                                     'GT'           => 21,
                                                                     'GE'           => 22),
                                  'test2'                   => array('('            => 23),
                                  'expression'              => array('INTEGER'      => 24,
                                                                     'IDENTIFIER'   => 24,
                                                                     '('            => 24),
                                  'fterm'                   => array('+'            => 25,
                                                                     '-'            => 26,
                                                                     ';'            => 27,
                                                                     ')'            => 27),
                                  'term'                    => array('INTEGER'      => 28,
                                                                     'IDENTIFIER'   => 28,
                                                                     '('            => 28),
                                  'ffactor'                 => array('*'            => 29,
                                                                     '/'            => 30,
                                                                     ';'            => 31,
                                                                     ')'            => 31,
                                                                     '+'            => 31,
                                                                     '-'            => 31),
                                  'factor'                  => array('('            => 32,
                                                                     'IDENTIFIER'   => 33,
                                                                     'INTEGER'      => 34),
                                  'morelabeledstatements'   => array('IDENTIFIER'   => 35,
                                                                     'ENDFUNC'      => 36));
    }

    
    /**
     * Destructs the NECTJGrammar
     *
     */
    public function __destruct()
    { 
        parent::__destruct(); 
        $this->parseTable = null;
    }
        

    /**
     * Returns a textual representation of the grammar
     *
     * @return string A string.
     */
    public function __toString()
    { 
        parent::__tostring(); 
        return "";
    }

    public function getRule($nonTerminal, $lookahead)
    {
        return($this->grammar[$this->parseTable[$nonTerminal][$lookahead]]);
    }

    /**
     * Returns the first set given a non-terminal
     *
     * XXX: This is not the best way to do this. This is hard coded.
     *
     */
    public function first($nonTerminal)
    {
        $rval = array();
        // Not implemented
        return $rval;
    }


    /**
     * Returns the follow set given a non-terminal
     *
     * XXX: This is not the best way to do this. This is hard coded.
     *
     */
    public function follow($nonTerminal)
    {
        $rval = array();

        // Not implemented
        return $rval;
    }
    public function endable($nonTerminal)
    {
        $rval = false;

        if($nonTerminal == "program" ||
           $nonTerminal == "function")
            $rval = true;

        return $rval;
    }


    public function select($rule)
    {
        $rval = array();

        // Not implemented
        return $rval;
    }

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
        $NECTJGrammar = new NECTJGrammar();

        printf("NECTJGrammar main program.\n");
        //echo "print out grammar: \n";
        //echo $NECTJGrammar;

        //print_r($NECTJGrammar->firstSets);
        $status = 0;
        return $status;
    }
}

if(realpath($argv[0]) == realpath(__FILE__))
{
    exit(NECTJGrammar::main(array_slice($argv, 1)));
}
?>
