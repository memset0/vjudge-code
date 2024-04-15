<?php
$n = trim(file_get_contents("php://stdin"));
echo ($n + 1) * ($n + 2) * ($n + 3) * ($n + 4) / 24;