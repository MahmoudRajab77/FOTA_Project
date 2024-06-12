<?php

if (isset($_POST['submit']))
{
	$file = $_FILES['file'];
	//print_r($file);
	$fileName = $_FILES['file']['name'];	// To get the file name from the uploaded file
	$fileTmpName = $_FILES['file']['tmp_name'];	// To get file tmp name
	$fileSize = $_FILES['file']['size'];	// To get file size
	$fileError = $_FILES['file']['error'];	// To get error if there is any
	$fileType = $_FILES['file']['type'];	// To get file type

	// LED.hex --> LED  hex
	$fileExt = explode('.', $fileName);	// To seperate the file name and it's extention
	$fileActualExt = strtolower(end($fileExt));	// To get the file extention
	$fileActualName = strtolower($fileExt[0]);	// To get the file extention

	$allowed = array('hex', 'txt');

	if (in_array($fileActualExt, $allowed)) {

		if ($fileError === 0)
		{
			$FileTempDestination = 'uploads/Uploded_App.txt';
			move_uploaded_file($fileTmpName, $FileTempDestination);

			if( Check_Size() ){/*Means No Errors */
				if( Record_CheckSum() ){/*Means No Errors */
					/*	Encrypt Data Before Saving In App.txt */
					Encrypt_Data();

					/*Copy Uploded_App after checking */
					$FileFinalDestination = 'Apps/'.$fileActualName.'.txt';
					copy($FileTempDestination , $FileFinalDestination);
					header("Location: hostindex.html");

					/*	Creat File = Status File To Save 1 If Burn Button Is Set */
					/*
					$Status_File = fopen("uploads/Status_File.txt","w+");
					fwrite($Status_File , "1");
					fclose($Status_File);*/
					
				}
				else{
					/*Error Message On Server */
				}
			}
			else{
				/*Error Message On Server */
			}

			echo "File Uploaded Successfully.";
		}
		else 
		{
			echo "There was an error uploading your file.";
		}

	} 
	else 
	{
		echo "You cannot upload files of this type.";
	}
}
else{
	echo "No Sumbitting";
}


/*Return 1 If Suitable Size, 0 If Larger Than 54K */
function Check_Size(){
	$Returned_Value=0;

	$HexFile= file("uploads/Uploded_App.txt");/*  Return File As An Array */
	/*Loop On Evry Line To Get Start And Last Of (Lower Address Part)  */
	$First_ADDRESS_LowPart="";
	$Last_ADDRESS_LowPart="";
	$LineNo=1;/*=1 --> To Neglict First Line  */


	$First_ADDRESS_LowPart = substr($HexFile[1],3,4);/*1 Is The Line Index, 3 Is The Start , 4 Is The Length */
	$First_ADDRESS_LowPart = hexdec($First_ADDRESS_LowPart);/*Convert Hex To Decimal */
	while($HexFile[$LineNo][8] == 0 ){/*Loop On Lines To Reach Last Data Record Line*/
		$LineNo++;
	}
	$Last_ADDRESS_LowPart = substr($HexFile[$LineNo-1],3,4);/*$LineNo-1 Is The Last Data Line Index, 3 Is The Start , 4 Is The Length */
	$Last_ADDRESS_LowPart = hexdec($Last_ADDRESS_LowPart);
	$Size = ($Last_ADDRESS_LowPart-$First_ADDRESS_LowPart);

	if($Size <= 55296){
		$Returned_Value = 1;
	}
	else{
		$Returned_Value = 0;
		/*Print Message To Server */
	}


	return $Returned_Value;

}/*	Check_Size */

/*	Return 1 In Case Of Correct Record OR 0 In Case Of ERROR	*/
function Record_CheckSum(){
	
	$Checksum   = 0;
	$RecChecksum= 0;
	$Char_Counter =    1;
	$LineNo =0;
	$FirstChar   = 0;
	$SecondChar  = 0;
	$Returned_Value = 1;

	$HexFile= file("uploads/Uploded_App.txt");/*  Return File As An Array */
	
	/*	Checksum Safety On Every Record If Correct 	*/
	while($HexFile[$LineNo] != ""){
		while("\r" != $HexFile[$LineNo][$Char_Counter+2]){/*	i+2 To Avoid Summing Of Last 2 Character In Record--> Received CS	*/
			$FirstChar = hexdec($HexFile[$LineNo][$Char_Counter]);
			$SecondChar= hexdec($HexFile[$LineNo][$Char_Counter+1]);
			$Checksum += ( ($FirstChar<<4) | ($SecondChar) );
			$Char_Counter+=2;
			
		}

		$Checksum = 0x01 + ((~$Checksum) & 0xFF)&0xFF;


		$FirstChar = hexdec($HexFile[$LineNo][$Char_Counter]);
		$SecondChar= hexdec($HexFile[$LineNo][$Char_Counter+1]);
		$RecChecksum = (( ($FirstChar << 4) | ($SecondChar) ) & 0xFF);

		if( $Checksum != $RecChecksum){
			$Returned_Value=0;
			break;
		}
		$RecChecksum=0;
		$Checksum=0;
		$Char_Counter=1;
		$LineNo++;
	}


	return $Returned_Value;

}//Record_CheckSum


function Encrypt_Data(){
	$LineNo=0;
	$Char_Counter=1;
	$Key=9;
	
	$HexFile= file("uploads/Uploded_App.txt");/*  Return File As An Array */
	$File=fopen("uploads/Uploded_App.txt" , "w");
	while($HexFile[$LineNo] != ""){
		while("\r" != $HexFile[$LineNo][$Char_Counter]){
			$HexFile[$LineNo][$Char_Counter] = dechex(hexdec($HexFile[$LineNo][$Char_Counter]) ^ $Key) ;
			// $HexFile[$LineNo][$Char_Counter] = dechex(hexdec($HexFile[$LineNo][$Char_Counter]) ^ $Key) ;
			$HexFile[$LineNo][$Char_Counter] = strtoupper($HexFile[$LineNo][$Char_Counter]);
			$Char_Counter++;	
		}
		fwrite($File , ($HexFile[$LineNo]));
		$Char_Counter=1;
		$LineNo++;
	}
}

?>