<?php

for($c = 5; $c < 1000; ++$c)
    for($b = $c - 1; $b > 0; --$b)
        for($a = $b - 1; $a > 0; --$a)
            if((pow($a, 2) + pow($b, 2)) == pow($c, 2))
                if(($a + $b + $c) == 1000)
                    echo $a . " * " . $b . " * " . $c . " = " . ($a * $b * $c) . "\n";

?>
