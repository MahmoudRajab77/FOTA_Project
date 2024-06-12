<?php 

	$LocalDir = 'Apps';
	global $options;

	if ($handle = opendir($LocalDir))
	{
		while (false !== ($file = readdir($handle))) 
		{
			if ($file != '.' && $file != '..')
			{
				$AppName = explode('.', $file);
				$AppName = $AppName[0];
				$options = $options."<option value=$file>$AppName</option>"; 
			}
		}
	}

 ?>

<!DOCTYPE html>
<html>
<head>
	<title>FOTA</title>
	<link rel="shortcut icon" type="image/png" href="favicon.png">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="UploadStyle.css">
</head>
<body>

	<img src="Logo.png" width="400" id="Logo"
				title="Logo">

	<div class="Wrapper">

		<div class="Intro" >
			<h1>Introduction</h1>

			<h3>
				<p>This website is implemented by: Abdelaziz Elmasry, Abdurrahman Anani, Yassmin Refaat, Osama Metwally, Yassmen Askr.</p>

				<p>To Burn your Application using Flashig Over The Air.</p>
				
				<p>We hope you enjoy it.</p>
			</h3>
		</div>

		<form action="Burn.php" method="POST" enctype="multipart/form-data">

			<select name="File_Name" class="select_menu">
        		<option disabled selected>Select File</option>
            	<?php echo $options;?>
        	</select>

			<button type="submit" name="submit" id="burn-button">Burn your file</button>

		</form>
	</div>

</body>
</html>