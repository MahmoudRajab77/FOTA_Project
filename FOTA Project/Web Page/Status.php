<?php

	$file = fopen('uploads/ProgStatus.txt', 'r');
	$line = fgets($file)."</p>";

	while (!feof($file)) {

		$line = $line . fgets($file)."</p>";

	}

	echo $line;

?>