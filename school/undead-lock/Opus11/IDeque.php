<?php
/**
 * @copyright Copyright (c) 2005 by Bruno R. Preiss, P.Eng.
 *
 * @author $Author: brpreiss $
 * @version $Id: IDeque.php,v 1.6 2005/11/27 23:32:31 brpreiss Exp $
 * @package Opus11
 */

/**
 */
require_once 'IContainer.php';
require_once 'IQueue.php';

//{
/**
 * Interface implemented by all deques.
 *
 * @package Opus11
 */
interface IDeque
    extends IContainer, IQueue
{
    /**
     * Enqueues the given object at the head of this deque.
     *
     * @param object IObject $obj The object to enqueue.
     */
    public function enqueueHead(IObject $obj);
    /**
     * Enqueues the given object at the tail of this deque.
     *
     * @param object IObject $obj The object to enqueue.
     */
    public function enqueueTail(IObject $obj);
    /**
     * Dequeues and returns the object at the head of this deque.
     *
     * @return object IObject The object at the head of this deque.
     */
    public function dequeueHead();
    /**
     * Dequeues and returns the object at the tail of this deque.
     *
     * @return object IObject The object at the tail of this deque.
     */
    public function dequeueTail();
    /**
     * Tail getter.
     *
     * @return object IObject The object at the tail of this deque.
     */
    public function getTail();
}
//}>a
?>
