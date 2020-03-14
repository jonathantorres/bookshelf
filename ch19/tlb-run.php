<?php

for ($i=1; $i <= 1000; $i++) {
    $output = [];
    exec('./tlb ' . ($i+2) . ' ' . ($i+4), $output);
    foreach ($output as $line) {
        echo $line . PHP_EOL;
    }
}

?>
