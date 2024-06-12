<?php

	$file = fopen('uploads/PageNo.txt', 'r');
	$line = fgets($file)."</p>";

	while (!feof($file)) {

		$line = $line . fgets($file)."</p>";

	}

	echo $line;

?>