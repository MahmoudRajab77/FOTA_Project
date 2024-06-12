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

		<form action="upload.php" method="POST" enctype="multipart/form-data">
			<input type="file" name="file" id="real-file" hidden="hidden">
			
			<div class="box" >
				<button type="button" id="choose-button">Choose a hex file</button>

				<span id="custom-text">  No file chosen.</span>
			</div>

			<button type="submit" name="submit" id="upload-button">Upload</button>

			<script type="text/javascript">
				
				const realFileBtn = document.getElementById("real-file");

				const customBtn = document.getElementById("choose-button");

				const customTxt = document.getElementById("custom-text");

				customBtn.addEventListener("click", function(){

					realFileBtn.click();
				});

				realFileBtn.addEventListener("change", function(){
					if(realFileBtn.value){
						customTxt.innerHTML = realFileBtn.value.match(/[\/\\]([\w\d\s\.\-\(\)]+)$/)[1];
					} else {
						customTxt.innerHTML = "No file chosen.";
					}
				});

			</script>

		</form>
	</div>

</body>
</html>