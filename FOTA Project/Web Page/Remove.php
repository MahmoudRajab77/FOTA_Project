<?php

if (isset($_POST['submit']))
{

	$SelectedFile = $_POST['File_Name'];

	$SelectedFile = 'Apps/'.$SelectedFile;

	if (!unlink($SelectedFile))
	{
		echo "Error";
	}
	else
	{
		header("Location: hostindex.html?App_Deleted");
	}
}

 ?>