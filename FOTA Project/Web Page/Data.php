<?php

	$file = fopen('uploads/LastPage.txt', 'r');
	$line = fgets($file)."</p>";
	$Flag = 0;

	while (!feof($file)) {

		$line = $line . fgets($file)."</p>";

	}

	echo $line;

?>