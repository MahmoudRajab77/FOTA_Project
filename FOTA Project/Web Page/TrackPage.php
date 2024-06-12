<!DOCTYPE html>
<html>
<head>
	<title>FOTA</title>
	<link rel="shortcut icon" type="image/png" href="favicon.png">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="LastPStyle.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

	<script type="text/javascript">

		$(document).ready(function(){

			setInterval(function(){
				$("#data").load("Data.php");
				$("#PageNo").load("PageNo.php");
				$("#Status").load("Status.php");

				//refres();
			}, 2000);
			

		});

	</script>

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

	<div class="data-box">

		<h4 id="data-title">
			Page being processed
		</h4>

		<h5 id="data-style">
			<div id="data"></div>
		</h5>
	</div>

	<h4 id="page-title">
		Page Number
	</h4>
	<div class="Page-box">
		<h5 id="Page-style">
			<div id="PageNo"></div>
		</h5>
	</div>

	<h4 id="status-title">
		Status
	</h4>
	<div class="Status-box">
		<h5 id="Status-style">
			<div id="Status"></div>
		</h5>
	</div>
		

	</div>

</body>
</html>