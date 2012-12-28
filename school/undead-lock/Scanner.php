<?php
/**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: Scanner.php, Exp $
 * @package undead-lock
 */

//{
/**
 * Scans in a NECTJ file and puts it in an array to be parsed by the Parser
 *
 * @package undead-lock
 */

class Scanner
{

    /**
     * Constructs a Scanner
     *
     */
    public function __construct()
    {;;;}
    
    /**
     * Destructs the Scanner
     *
     */
    public function __destruct()
    {;;;}
        

    /**
     * Returns a textual representation
     *
     * @return string A string.
     */
    public function __toString()
    {
        // Nothing to print
        return "";
    }

    /**
     * Scans the file and returns it as an array.
     *
     * @note Each simulation begins with two integers.
     *       "0 0" or EOF ends the program.
     *       Here is some sample input:
     *
     *   1 2
     *   5    1 1     1 2    3 10     2 1    2 2
     *   3 3
     *   5    1 1     1 2    3 2   2 1     2 2
     *   5    1 1     1 2    3 2   2 1     2 2
     *   4    1 3     3 5    2 3   3 2
     *   2 2
     *   5    1 1     1 2    3 2   2 1     2 2
     *   5    1 2     1 1    3 2   2 2     2 1
     *   3 3
     *   6    1 1   3 3    1 2    3 3   2 1    2 2
     *   6    1 2   3 3    1 3    3 3   2 2    2 3
     *   6    1 3   3 3    1 1    3 3   2 3    2 1
     *   7 6
     *   7    1 1     3  5   1  2  3  5    2 1     2 2   3 3
     *   4    3 3     1  3   3  5  2  3
     *   5    3 3     1  2   3  2  2  2    3 3
     *   6    1 4     3  6   1  3  2  4    3 2     2 3
     *   6    1 3     3  5   1  5  2  3    2 5     3 2
     *   7    1 6     3  5   1  2  3  2    2 2     2 6   3 3
     *   7    1 5     3  2   1  4  3  5    2 5     3 2   2 4
     *   0 0
     * @param string $filename
     *
     * @return string[] $finalArr The entire program as a tokenized array
     */
    public function scan($filename)
    {
        $finalArr = array();

        $tmpArr = array();

        $file = fopen($filename, 'r');

        // Break the whole file into lines
        while(($line = fgets($file)) != null)
        {
            $line = trim($line);
           
            $lineArr = explode(" ", $line);
           
            // Line with no white space
            $lineNoWsArr = array();

            // Remove spaces so we just have a tokenized array of data
            foreach($lineArr as $element)
                if(trim($element) != null)
                    array_push($lineNoWsArr, $element);

            if(count($lineNoWsArr) > 0)
            {

                if((count($lineNoWsArr) == 2) && count($tmpArr) > 1)
                {
                    array_push($finalArr, $tmpArr);

                    while(count($tmpArr))
                        array_pop($tmpArr);

                    array_push($tmpArr, $lineNoWsArr);
                }
                else
                {
                    // Right now, $tmpArr holds all the lines of the current simulation
                    array_push($tmpArr, $lineNoWsArr);
                }

            }
        }

        // Get the last one
        array_push($finalArr, $tmpArr);

        return $finalArr;
    }


    /**
     * Main program.
     *
     * @return integer Zero on success; non-zero on failure.
     */
    public static function main($filename)
    {
        printf("Scanner testing.\n");
        
        $status = 0;

        if(is_file($filename) && is_readable($filename))
            $file = fopen($filename, 'r');
        else
            $status = 1;

        $newScanner = new Scanner();

        $tokenizedProgram = $newScanner->scan($filename);
    
        print_r($tokenizedProgram);

        return $status;
    }
}

// If we are trying to execute this class directly
if(realpath($argv[0]) == realpath(__FILE__))
{
    // No CLI argument
    if($argc != 2)
    {
        echo "Please specify a file\n";
        exit(1);
    }

    exit(Scanner::main($argv[1]));
}
?>
