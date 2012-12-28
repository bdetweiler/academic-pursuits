<?php
/**
 * @copyright Copyright (c) 2005 by Bruno R. Preiss, P.Eng.
 *
 * @author $Author: brpreiss $
 * @version $Id: DigraphAsMatrix.php,v 1.2 2005/12/09 01:11:11 brpreiss Exp $
 * @package Opus11
 */

/**
 */
require_once 'GraphAsMatrix.php';
require_once 'IDigraph.php';
require_once 'AbstractDigraph.php';
require_once 'Exceptions.php';

/**
 * Iterator that enumerates the edges of a DigraphAsMatrix.
 *
 * @package Opus11
 */
class DigraphAsMatrix_EdgeIterator
    extends AbstractIterator
{
    /**
     * @var object DigraphAsMatrix The graph.
     */
    protected $graph = NULL;
    /**
     * @var integer The current row.
     */
    protected $v = 0;
    /**
     * @var integer The current column.
     */
    protected $w = 0;

    /**
     * Constructs a DigraphAsMatrix_EdgeIterator for the given graph.
     *
     * @param object DigraphAsMatrix $graph The graph.
     */
    public function __construct(DigraphAsMatrix $graph)
    {
        parent::__construct();
        $this->graph = $graph;
        $matrix = $this->graph->getMatrix();
        for ($this->v = 0;
            $this->v < $this->graph->getNumberOfVertices(); ++$this->v)
        {
            for ($this->w = 0;
                $this->w < $this->graph->getNumberOfVertices(); ++$this->w)
            {
                if ($matrix[array($this->v,$this->w)] !== NULL)
                    break 2;
            }
        }
    }

    /**
     * Destructor.
     */
    public function __destruct()
    {
        $this->graph = NULL;
        parent::__destruct();
    }

    /**
     * Valid predicate.
     *
     * @return boolean True if the current position of this iterator is valid.
     */
    public function valid()
    {
        return $this->v < $this->graph->getNumberOfVertices() &&
            $this->w < $this->graph->getNumberOfVertices();
    }

    /**
     * Key getter.
     *
     * @return integer The key for the current position of this iterator.
     */
    public function key()
    {
        return $this->v * $this->graph->getNumberOfVertices() + $this->w;
    }

    /**
     * Current getter.
     *
     * @return mixed The value for the current postion of this iterator.
     */
    public function current()
    {
        $matrix = $this->graph->getMatrix();
        return $matrix[array($this->v, $this->w)];
    }

    /**
     * Advances this iterator to the next position.
     */
    public function next()
    {
        $matrix = $this->graph->getMatrix();
        for (++$this->w;
            $this->w < $this->graph->getNumberOfVertices(); ++$this->w)
        {
            if ($matrix[array($this->v,$this->w)] !== NULL)
                return;
        }
        for (++$this->v;
            $this->v < $this->graph->getNumberOfVertices(); ++$this->v)
        {
            for ($this->w = 0;
                $this->w < $this->graph->getNumberOfVertices(); ++$this->w)
            {
                if ($matrix[array($this->v,$this->w)] !== NULL)
                    return;
            }
        }
    }

    /**
     * Rewinds this iterator to the first position.
     */
    public function rewind()
    {
        $matrix = $this->graph->getMatrix();
        for ($this->v = 0;
            $this->v < $this->graph->getNumberOfVertices(); ++$this->v)
        {
            for ($this->w = 0;
                $this->w < $this->graph->getNumberOfVertices(); ++$this->w)
            {
                if ($matrix[array($this->v,$this->w)] !== NULL)
                    break 2;
            }
        }
    }
}

/**
 * Aggregate that represents the edges of a DigraphAsMatrix.
 *
 * @package Opus11
 */
class DigraphAsMatrix_EdgeAggregate
    implements IteratorAggregate
{
    /**
     * @var object DigraphAsMatrix The graph.
     */
    protected $graph = NULL;

    /**
     * Constructs a DigraphAsMatrix_EdgeAggregate for the given graph.
     *
     * @param object DigraphAsMatrix $graph The graph.
     */
    public function __construct(DigraphAsMatrix $graph)
    {
        $this->graph = $graph;
    }

    /**
     * Destructor.
     */
    public function __destruct()
    {
        $this->graph = NULL;
    }

    /**
     * Returns an iterator the enumerates the edges of the graph.
     *
     * @return object Iterator An iterator.
     */
    public function getIterator()
    {
        return new DigraphAsMatrix_EdgeIterator($this->graph);
    }
}

//{
/**
 * A directed graph implemented using an adjacency matrix.
 *
 * @package Opus11
 */
class DigraphAsMatrix
    extends GraphAsMatrix
    implements IDigraph
{
//}@head

//{
//!    // ...
//!}
//}@tail

//{
    /**
     * Constructs a DigraphAsMatrix with the specified size.
     *
     * @param size The maximum number of vertices.
     */
    public function __construct($size = 0)
    {
        parent::__construct($size);
    }
//}>a

    /**
     * Destructor.
     */
    public function __destruct()
    {
        parent::__destruct();
    }

    /**
     * Inserts the given edge into this graph.
     *
     * @param object Edge $edge The edge to insert.
     */
    public function insertEdge(Edge $edge)
    {
        $v = $edge->getV0()->getNumber();
        $w = $edge->getV1()->getNumber();

        if($this->matrix[array($v,$w)] !== NULL)
            throw new ArgumentError();
        if($v == $w)
            throw new ArgumentError();

        $this->matrix[array($v,$w)] = $edge;
        ++$this->numberOfEdges;
    }

    /**
     * Removes the given edge into this graph.
     * Added by Brian Detweiler
     *
     * @param int $from The edge emanates from this node
     * @param int $from The edge goes to this node
     */
    public function removeEdge($from, $to)
    {
        if($this->matrix[array($from, $to)] == NULL)
            throw new ArgumentError();
        if($from == $to)
            throw new ArgumentError();

        $this->matrix[array($from, $to)] = NULL;
        --$this->numberOfEdges;
    }

    /**
     * Returns the edges in this graph.
     *
     * @return object IteratorAggregate
     * The edges in this graph.
     */
    public function getEdges()
    {
        return new DigraphAsMatrix_EdgeAggregate($this);
    }

    /**
     * Returns the weight of the edge connecting $v1 and $v2
     * Added by Brian Detweiler
     *
     * @return int The weight
     * The weight of the edge connecting $v1 and $v2
     */
    public function getEdgeWeight($v1, $v2)
    {
        $rval = null;

        $matrix = parent::getMatrix();

        // Go to column $v and run down it
        if($matrix[array($v1, $v2)])
            $rval = $matrix[array($v1, $v2)]->getWeight();

        return $rval;
    }

    /**
     * Returns the In Degree for a vertex in this graph.
     * Added by Brian Detweiler
     *
     * @return int
     * The number of edges entering this vertex
     */
    public function getInDegree($v)
    {
        $inDegree = 0;
        $matrix = parent::getMatrix();
        // Go to column $v and run down it
        for($i = 0; $i < parent::getNumberOfVertices(); ++$i)
            if($matrix[array($i, $v)])
                ++$inDegree;

        return $inDegree;
    }

    /**
     * Check if $v1 connects to $v2
     * Added by Brian Detweiler
     *
     * @return boolean True if $v1 connects to $v2
     */
    public function connectsTo($v1, $v2)
    {
        $rval = false;

        $matrix = parent::getMatrix();
        if($matrix[array($v1, $v2)])
            $rval = true;

        return $rval;
    }


    /**
     * Gets the largest weight of all incoming edges
     * Added by Brian Detweiler
     *
     * @return int 
     */
    public function getMaxWeightIn($v)
    {
        $rval = 0;

        $matrix = parent::getMatrix();
        for($i = 0; $i < parent::getNumberOfVertices(); ++$i)
            if($matrix[array($i, $v)] && 
               $matrix[array($i, $v)]->getWeight() > $rval)
                $rval = $matrix[array($i, $v)]->getWeight();

        return $rval;
    }

    /**
     * Returns the Out Degree for a vertex in this graph.
     * Added by Brian Detweiler
     *
     * @return int
     * The number of edges leaving this vertex
     */
    public function getOutDegree($v)
    {
        $outDegree = 0;
        $matrix = parent::getMatrix();
        // Go to column $v and run down it

        for($i = 0; $i < parent::getNumberOfVertices(); ++$i)
            if($matrix[array($v, $i)])
                ++$outDegree;

        return $outDegree;
    }

    /**
     * Main program.
     *
     * @param array $args Command-line arguments.
     * @return integer Zero on success; non-zero on failure.
     */
    public static function main($args)
    {
        printf("DigraphAsMatrix main program.\n");
        $status = 0;
        $g = new DigraphAsMatrix(4);
        AbstractDigraph::test($g);
        $g->purge();
        AbstractDigraph::testWeighted($g);
        $g->purge();
        return $status;
    }
}

if (realpath($argv[0]) == realpath(__FILE__))
{
    exit(DigraphAsMatrix::main(array_slice($argv, 1)));
}
?>
