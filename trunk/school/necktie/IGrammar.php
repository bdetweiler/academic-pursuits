<?php
/**
 * @copyright Copyright (c) 2009 by Brian Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: IGrammar.php,v 1.0 bdetweiler Exp $
 * @package Opus11
 */

/**
 */
require_once 'Opus11/SetAsArray.php';

//{
/**
 * Interface implemented by all Grammars.
 *
 * @package necktie
 */
interface IGrammar
{
    /**
     * Returns the set of items appearing directly after $non_terminal
     *
     * @param string $nonTerminal The non-terminal to look up
     * @return firstSet SetAsArray The first set for this $non_terminal.
     */
    public function first($nonTerminal);

    /**
     * Returns the set of items appearing in the follow of $non_terminal
     *
     * @param string $nonTerminal The non-terminal to look up
     * @return followSet SetAsArray The first set for this $non_terminal.
     */
    public function follow($nonTerminal);

    /**
     * Gets the select set of the $nonTerminal
     *
     * @param int $rule The rule number to look up
     * @return object SetAsArray $followSet The set of items in the select set of $rule
     */
    public function select($rule);

    /**
     * Returns the set of items appearing in the lookahead of $non_terminal
     *
     * @param string $nonTerminal The non-terminal to look up
     * @param string $terminal The terminal to look up
     * @return lookAhead SetAsArray The first set for this $non_terminal.
     */
    public function lookAhead($nonTerminal, $terminal);
}

?>
