<?php
/**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: Simulation.php, Exp $
 * @package undead-lock
 */

//{
/**
 * @package undead-lock
 */

class Process
{
    private $procId         = "";
    private $procNumber     = 0;
    private $instructions   = null;
    private $state          = "";
    private $runTime        = 0;
    private $terminatedTime = 0;

    const REQUEST           = 1;
    const RELEASE           = 2;
    const COMPUTE           = 3;

    // In the data, the INSTRUCTION is the first part of the pair
    const INSTRUCTION       = 0;

    // In the data, the ARGUMENT is the second part of the pair
    // Either a resource to allocate/deallocate or a number of clock cycles to compute for
    const ARGUMENT          = 1;

    /**
     * Constructs a Process
     *
     */
    public function __construct($procId, $instructions)
    {
        $this->instructions = array();

        if(!is_array($instructions))
            $instructions = explode(" ", trim($instructions));
       
        while(count($instructions))
            if($instructions[0])
                array_push($this->instructions, array_shift($instructions));
            else
                array_shift($instructions);


        $this->procId = trim($procId);
        $this->procNumber = (substr($procId, 1, strlen($procId)) - 1);
        $this->setCreated();
    }

    /**
     * A default method for printing a process
     *
     */
    public function __tostring()
    {
        print("___________ $this->procId ___________\n");
        print("Process Number:    $this->procNumber\n");
        print("State:             $this->state\n");
        print("RunTime:           $this->runTime\n");
        print("Instructions:      \n");
        print_r($this->instructions);

        if($this->instructions[self::INSTRUCTION] == self::COMPUTE)
            print("Compute Time Left: " . $this->instructions[self::ARGUMENT] . "\n");

        return "";
    }

    /**
     * Destructs the Process
     *
     */
    public function __destruct()
    {
        $this->procId       = "";
        $this->procNumber   = 0;
        $this->state        = "";
        $this->runTime      = 0;
        $this->instructions = null;
    }

    /**
     * Sets the time the process terminated
     *
     */
    public function setTerminatedTime($time)
    {
        $this->terminatedTime = $time;
    }
    /**
     * Returns the time at which the process terminated
     *
     */
    public function getTerminatedTime()
    {
        return($this->terminatedTime);
    }
    /**
     * Returns the actual Process number (0 indexed)
     *
     */
    public function getProcNumber()
    {
        return($this->procNumber);
    }

    /**
     * Returns the actual Process number (0 indexed)
     *
     */
    public function getProcId()
    {
        return($this->procId);
    }

    /**
     * 
     *
     */
    public function incrementRunTime()
    {
        ++$this->runTime; 
    }

    /**
     * 
     *
     */
    public function getRunTime()
    {
        return $this->runTime; 
    }

    /**
     * Returns true if there are more instructions
     *
     */
    public function instructionsEmpty()
    {
        $rval = true;

        if(count($this->instructions))
            $rval = false;
        
        return $rval;
    }

    /**
     * Returns the next instruction if there are any
     *
     */
    public function getInstruction()
    {
        if($this->instructionsEmpty())
            exit("There are no instructions left.");

        return(array_slice($this->instructions, 0, 2));
    }

    /**
     * Advances the instruction set to the next instructions
     *
     */
    public function advanceInstructions()
    {
        if($this->instructionsEmpty())
            exit("There are no instructions left.");

        array_shift($this->instructions);
        array_shift($this->instructions);
        
        if($this->instructionsEmpty())
            $this->setTerminated();
    }

    /**
     * Set the process to the WAITING state
     *
     */
    public function setCreated()
    {
        $this->setState("CREATED");
    }

    /**
     * Set the process to the WAITING state
     *
     */
    public function setWaiting()
    {
        $this->setState("WAITING");
    }

    /**
     * Set the process to the RUNNING state
     *
     */
    public function setRunning()
    {
        $this->setState("RUNNING");
    }

    /**
     * Set the process to the BLOCKED state
     *
     */
    public function setBlocked()
    {
        $this->setState("BLOCKED");
    }

    /**
     * Set the process to the TERMINATED state
     *
     */
    public function setTerminated()
    {
        $this->setState("TERMINATED");
    }

    /**
     * Set the process to a specified state
     *
     */
    public function setState($state)
    {
        $this->state = trim($state);
    }

    /**
     * Get the process' current state
     *
     */
    public function getState()
    {
        return($this->state);
    }


    /**
     * Gets the time left to compute
     *
     */
    public function getComputeTime()
    {
        $rval = 0;

        if($this->instructions[self::INSTRUCTION] == self::COMPUTE)
            $rval = $this->instructions[self::ARGUMENT];
    
        return($rval);
    }

    /**
     * Compute one clock cycle of the process.
     *
     */
    public function compute()
    {
        if($this->getComputeTime() > 0)
            --$this->instructions[self::ARGUMENT];
        else
            exit("No time left to compute!\n");
    }

    /**
     * A main function for testing and running directly
     *
     */
    public static function main()
    {

        // Compute 3, 
        // allocate resource 3, 
        // compute 5, 
        // release resource 3
        // $process = new Process("P1", "3 3  1 3  3 5  2 3");
        $process = new Process("P1", "1 1     3  5   1  2  3  5    2 1     2 2   3 3");
                                       

        print("New process:\n");
        print($process);

        $process->setRunning();

        while(!$process->instructionsEmpty())
        {
            print($process);
            $ins = $process->getInstruction();

            switch($ins[self::INSTRUCTION])
            {
                case self::REQUEST:
                    print("Requesting " . $ins[self::ARGUMENT] . "\n");
                    break;
                case self::RELEASE:
                    print("Releasing " . $ins[self::ARGUMENT] . "\n");
                    break;
                case self::COMPUTE:
                    print("Computing " . $ins[self::ARGUMENT] . "\n");
                    $process->setComputeTime($ins[self::ARGUMENT]);

                    while($process->getComputeTime() > 0)
                    {
                        print("computing: " . $process->getComputeTime() . "\n");
                        $process->compute();
                    }
                    break;
                default:
                    break;

            }

            $process->advanceInstructions();
            print("\n");
        }
    }
}

// If we are trying to execute this class directly
if(realpath($argv[0]) == realpath(__FILE__))
{
    exit(Process::main($argv[1]));
}
