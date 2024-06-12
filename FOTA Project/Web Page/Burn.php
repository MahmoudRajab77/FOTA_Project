<?php

if (isset($_POST['submit']))
{

	$SelectedFile = $_POST['File_Name'];

	$SelectedFile = 'Apps/'.$SelectedFile;
	
	$file = fopen($SelectedFile, 'r');

	$file2 = fopen('uploads/App.txt', 'w');

	while (!feof($file))
	{
		$line = fgets($file);
		fwrite($file2, $line);
	}

	fclose($file);
	fclose($file2);

	$BurnStatus = fopen('uploads/Status_File.txt', 'w');

	fwrite($BurnStatus, '1');

	fclose($BurnStatus);

	$LastPage = fopen('uploads/LastPage.txt', 'w');
	fclose($LastPage);

	$LastPage = fopen('uploads/PageNo.txt', 'w');
	fclose($LastPage);

	$LastPage = fopen('uploads/ProgStatus.txt', 'w');
	fclose($LastPage);

	//echo "File Burning";
	header("Location: TrackPage.php");
}

 ?>