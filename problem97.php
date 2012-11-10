<?php

for($i = 1; $i <= 16; ++$i) {
    if(!($i & ($i - 1)))
        echo "Power of Two!: $i\n";
}

?>
