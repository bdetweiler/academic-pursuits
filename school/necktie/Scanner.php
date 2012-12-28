<?php
/**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: Scanner.php, Exp $
 * @package Necktie
 */

//{
/**
 * Scans in a NECTJ file and puts it in an array to be parsed by the Parser
 *
 * @package Necktie
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
     * @param string $filename
     *
     * @return string[] $finalArr The entire program as a tokenized array
     */
    public function scan($filename)
    {
        $file = fopen($filename, 'r');

        $programString = "";
        // Break the whole file into lines
        while(($line = fgets($file)) != null)
        {
            $line = trim(strtoupper($line));

            $lineArr = str_split($line);

            // Discard all comments (//)
            $i = 0;
            for(; $i < count($lineArr); ++$i)
                if($lineArr[$i] == '/' && $lineArr[$i + 1] == '/')
                    break;

            // Concatenate the whole program into one big string
            $programString .= substr($line, 0, $i);
        }
        // Break the string into an array of characters, but don't throw away the string yet
        $programArr = str_split($programString);

        $inQuote = false;
        $quotePosArr = array();

        // Now we need to find the position of all valid double quotes (not escaped double quotes)
        // And stick those positions into an array
        for($i = 0; $i < count($programArr); ++$i)
        {
            if($programArr[$i] == '"' && $inQuote == false)
            {
                $inQuote = true;
                array_push($quotePosArr, $i);

            }
            else if(($programArr[$i] == '"' && $programArr[$i - 1] != "\\") && 
                    $inQuote == true)
            {
                $inQuote = false;
                array_push($quotePosArr, $i);
            }
        }

        $tmpArr = array();


        // Now we need to separate strings from the rest of the program,
        // because strings are considered one token regardless of spaces

        // The first case is special
        array_push($tmpArr, substr($programString, 0, $quotePosArr[0]));

        $count = 1;
        $prevPos = $quotePosArr[0];
        for($i = 1; $i < count($quotePosArr); ++$i)
        {
            if($count % 2)
                array_push($tmpArr, substr($programString, $prevPos, ($quotePosArr[$i] - $prevPos) + 1));
            else
                array_push($tmpArr, substr($programString, $prevPos + 1, ($quotePosArr[$i] - $prevPos) - 1));
            ++$count;

            $prevPos = $quotePosArr[$i];
        }

        // The last case is also special
        array_push($tmpArr, substr($programString, $prevPos + 1, (strlen($programString) - $prevPos) - 1));

        // Now loop over the tmp array and put spaces around all the terminal symbols
        // so we can explode it.
        for($i = 0; $i < count($tmpArr); ++$i)
        {
            // Break each element down into a char array
            $tmpElementArr = str_split($tmpArr[$i]);
            // If it's a string, leave it alone
            if($tmpElementArr[0] == '"')
                continue;

            // We will concatenate the elements, adding spaces, to this string.
            $tmpTmpElement = "";
            for($j = 0; $j < count($tmpElementArr); ++$j)
            {
                switch($tmpElementArr[$j])
                {
                    case '(':
                        $tmpTmpElement .= " ( ";
                        break;
                    case ')':
                        $tmpTmpElement .= " ) ";
                        break;
                    case ';':
                        $tmpTmpElement .= " ; ";
                        break;
                    case ':':
                        $tmpTmpElement .= " : ";
                        break;
                    case ',':
                        $tmpTmpElement .= " , ";
                        break;
                    case '=':
                        $tmpTmpElement .= " = ";
                        break;
                    case '+':
                        $tmpTmpElement .= " + ";
                        break;
                    case '-':
                        $tmpTmpElement .= " - ";
                        break;
                    case '*':
                        $tmpTmpElement .= " * ";
                        break;
                    case '/':
                        $tmpTmpElement .= " / ";
                        break;
                    case '%':
                        $tmpTmpElement .= " % ";
                        break;
                    default:
                        $tmpTmpElement .= $tmpElementArr[$j];
                        break;
                }
            }

            // The only potential problem is if ENDFUNC and FUNC get squished together. This fixes that.
            $tmpArr[$i] = ereg_replace("ENDFUNCFUNC", "ENDFUNC FUNC", $tmpTmpElement);
        }

        $finalArr = array();
        foreach($tmpArr as $element)
        {
            $checkForString = str_split($element);
            if($checkForString[0] == '"')
                array_push($finalArr, $element);
            else
            {
                $elementArr = explode(" ", $element);
                foreach($elementArr as $piece)
                {
                    $piece = trim($piece);
                    if(strlen($piece) > 0)
                        array_push($finalArr, $piece);
                }
            }
        }

        // UGH! For SOME EFFING REASON, if the program starts with "FUNC" as it very well may, it's cutting off the "F"
        for($i = 0; $i < count($finalArr); ++$i)
            if($finalArr[$i] == "UNC")
                $finalArr[$i] = "FUNC";

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

        $newScanner = new Scanner($filename);

        $tokenizedProgram = $newScanner->scan($filename);
    
        print_r($tokenizedProgram);
        $reassembledString = implode(" ", $tokenizedProgram);
        print($reassembledString . "\n");
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
