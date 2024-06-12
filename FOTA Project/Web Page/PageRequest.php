<?php

$Page_Number='';
if(isset($_GET['PageNo'])){ /*  Check if There Is Any Variable Called PageNo    */

    $Page_Number=$_GET['PageNo'];   /*  Get the Value of Variable Called PageNo-->Send By URL   */
    // $NewLine="\r\n";
    /*   file_get_contents return file as a string  */
    //$HexFile=file_get_contents("http://osama-a-c-f-f-4.freevar.com/uploads/App.txt")    /*  file_get_contents --> Return the Whole Content of File Or False In ERROR Case    */
    $HexFile= file("uploads/App.txt");/*  Return File As An Array */
    //$line= strtok($HexFile, $NewLine); /*  strtok() splits a string (HexFile) into smaller strings (Line)  */
    //$line= fgets()
    if($HexFile !== false){
        $LineNo = $Page_Number*30;/* 400 is the No. Of Lines In One Page  */
        $CurrentPage = fopen('uploads/LastPage.txt', 'w');
        $File_With_Requested_Page = fopen("uploads/RequestedPage.txt","w");/*    Empty File To Save The Requested Page in It */
        /*18000/45 == 400   
          Page Size == 18000 --> Max Record Size= 43==>45*/
        while ( $LineNo < (30+($Page_Number*30)) ) {
            /*  Update the Line To Get Next Line  */
            //$line = strtok( $separator );   /* Works On HexFile From First Call */
            if($HexFile[$LineNo]==""){
                fwrite($File_With_Requested_Page ,"LO\r");/*End File */
                fwrite($CurrentPage ,"LO\r\n");
                /* Put 0 In Status File to Indicate MCU Burned the App */
                $Status_Fila=fopen("uploads/Status_File.txt","w");
                fwrite($Status_Fila , "0");
                fclose($Status_Fila);
                /*******************************************************/
                break;
            }
            fwrite($File_With_Requested_Page ,$HexFile[$LineNo]);   /*  Append Lines In RequestedPage.txt   */
            fwrite($CurrentPage, $HexFile[$LineNo]);
            $LineNo++;
        }
        fwrite($File_With_Requested_Page,"LY\r");/*End Page */

        $PageNo = fopen('uploads/PageNo.txt', 'w');
        fwrite($PageNo, $Page_Number);
        fclose($PageNo);
    }
    fclose($File_With_Requested_Page);

}
else{
    echo "ERROR..No Page Number Received!!";
}


?>