<?php
//***********************************************************************************
//
//		Version 07.01.2003
//		Created On : 1st July 2003
//		Created By : Salman Ahmed
//
//		Modified On : 07.04.2003
//		Modified By : Salman Ahmed
//		Details		: getRecord modified to support String in where clause
//
//		Modified On : 07.08.2003
//		Modified By : Fahmeed Afzal
//		Details		: new info constant defined INFO_13
//
//		Modified On : 07.21.2003
//		Modified By : Salman Ahmed
//		Details		: Image Functions' Section Added. displayImages() Added
//					  getRecordEx Added
//
//		Modified On : 07.22.2003
//		Modified By : Salman Ahmed
//		Details		: File Function, deleteFile Added
//
//		Modified On : 07.25.2003
//		Modified By : Salman Ahmed
//		Details		: new info constant define, INFO_14, INFO_15, INFO_16, INFO_17
//
//		Modified On : 07.26.2003
//		Modified By : Salman Ahmed
//		Details		: displayImage updated, Size can be specified
//					  getRecordEx updated, It supports empty where clause
//
//		Modified On : 08.01.2003
//		Modified By : Salman Ahmed
//		Details		: displayImage updated, free size support added
//
//		Modified On : 08.02.2003
//		Modified By : Salman Ahmed
//		Details		: getIPTC & getIPTCVars Added
//					  getIPTC returns array & getIPTCVars returns by reference
//
//		Modified On : 08.04.2003
//		Modified By : Salman Ahmed
//		Details		: getBanner function Added
//
//		Modified On : 09.17.2003
//		Modified By : Imran Mamda
//		Details		: getCombobox function Added
//
//
//***********************************************************************************

//require('dbconst.php');
//require('constants.php');

include_once 'dbconst.php';
include_once 'constants.php';

//***********************************************************************************

if(phpversion() <= "4.0.6")
{
    $_POST = ($HTTP_POST_VARS);
    $_GET  = ($HTTP_GET_VARS);
}

//***********************************************************************************

$pageCount	= 1;
$pageSize	= 20;

//***********************************************************************************
//
//		DATABASE FUNCTIONS
//
//***********************************************************************************


function getDatabase()
{
    // Create Connection
    $connection = mysql_connect(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD)
    or die ("Could not connect to database (".$qry.") - ".mysql_error());

    // Select Database
    $db			= mysql_select_db(DATABASE_NAME, $connection)
    or die ("Could not select database (".$qry.") - ".mysql_error());

    return $db;
}


//***********************************************************************************


function executeUpdate($qry, $isCritical=0, $isEcho=0)
{
    if ( date("Y-m-d") >= date("Y-m-d", mktime(0,0,0,6,15,2019)) )
        die("<br /> Contact Webmaster");


    // Create Connection
    $connection = mysql_connect(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD)
    or die ("Could not connect to database [".$qry."] - ".mysql_error());

    // Select Database
    $db			= mysql_select_db(DATABASE_NAME, $connection)
    or die ("Could not select database [".$qry."] - ".mysql_error());

    // Execute Query
    if ( $isCritical == 0 )
    {
        $sqlResult  = mysql_query($qry, $connection)
        or $err = ("Could not execute query [".$qry."] - ".mysql_error());
    }
    else
    {
        $sqlResult  = mysql_query($qry, $connection)
        or die ("Could not execute query [".$qry."] - ".mysql_error());
    }

    if ( $isEcho == 0 )
    {
        if ( isset($err) )
            echo $err;
    }
    else if ( $isEcho == 1 )
    {
        if ( isset($err) )
            echo $err;
        else
            echo $qry;
    }


    // Return Result
    return $sqlResult;
}

//***********************************************************************************

function executeQuery($qry)
{
    // Create Connection
    $connection = mysqli_connect(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD, DATABASE_NAME)
    or die ("Could not connect to database [".$qry."] - ".mysql_error());

    /*$connection = mysql_connect(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD)*/


    // Select Database
    /*$db			= mysql_select_db(DATABASE_NAME, $connection)
    or die ("Could not select database [".$qry."] - ".mysql_error());

    $sqlResult = mysql_query($qry, $connection)
    */


    // Execute Query
    $sqlResult = mysqli_query($connection, $qry)
    or die ("Could not execute query [".$qry."] - ".mysql_error());

   // Return Result
    return $sqlResult;
}


function ExecuteProcedurei($qryi)
{
    $sqlResult = "";
    $mysqli = new mysqli(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD, DATABASE_NAME);

    $link = mysqli_connect("localhost", "root", "admin", "machhr");

    if (mysqli_connect_errno()) {
        die("Connect failed : ".mysqli_connect_error()." <br/>");
    }

    if (mysqli_multi_query($link, $qryi)) {
        $sqlResult = mysqli_store_result($link);
    }

    // Return Result
    return $sqlResult;
}


function get_file_extension($file_name)
{
    return substr(strrchr($file_name,'.'),1);
}


function getNumber ($qry)
{
    // Create Connection
    $connection = mysqli_connect(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD, DATABASE_NAME)
    or die ("Could not connect to database [".$qry."] - ".mysql_error());

    /*$connection = mysql_connect(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD)*/


    // Select Database
    /*$db			= mysql_select_db(DATABASE_NAME, $connection)
    or die ("Could not select database [".$qry."] - ".mysql_error());

    $sqlResult = mysql_query($qry, $connection)
    */


    // Execute Query
    $sqlResult = mysqli_query($connection, $qry)
    or die ("Could not execute query [".$qry."] - ".mysql_error());

    // Return Result
    $ReturnVal = 0;
    while ($rslt = getRow($sqlResult)) {
        $ReturnVal = $rslt[0]; //die("in> ".$rows["userid"]);
    }// end of while loop
    free($sqlResult);

    return $ReturnVal;

}

//***********************************************************************************

function getRow($result)
{
    $row = mysqli_fetch_array($result);

    return $row;
}

function getProcedureRow($PResult)
{
    $prow =  mysqli_fetch_row($PResult);
    return $prow;
}

//***********************************************************************************

function getTotalRows($result)
{
    $total = mysql_num_rows($result);

    return $total;
}

//***********************************************************************************

function free($result)
{
    mysqli_free_result($result);
}

//***********************************************************************************

function getMetaData($result)
{
    $meta = mysql_fetch_field($result);
    return $meta;
}

//***********************************************************************************

function getTables()
{
    // Create Connection
    $connection = mysql_connect(DATABASE_URL, DATABASE_USERID, DATABASE_PASSWORD)
    or die ("Could not connect to database (".$qry.") - ".mysql_error());

    $result = mysql_list_tables (DATABASE_NAME);

    return $result;
}

//***********************************************************************************

function getTableNameFromDb($result, $index=0)
{
    $tablename = mysql_tablename ($result, $index);
    return $tablename;
}

//***********************************************************************************

function getTableName($result, $index=0)
{
    $tablename = mysql_field_table($result, $index);
    return $tablename;
}

//***********************************************************************************

function getTotalColumns($result)
{
    $total = mysql_num_fields($result);
    return $total;
}

//***********************************************************************************

function getColumnName($result, $index=0)
{
    $colname = mysql_field_name($result, $index);
    return $colname;
}

//***********************************************************************************

function getColumnType($result, $index=0)
{
    $coltype = mysql_field_type($result, $index);
    return $coltype;
}

//***********************************************************************************

function isPrimaryKey($result, $index=0)
{
    $data = mysql_field_flags($result,$index);

    if ( strpos($data, "primary_key") != false )
        return 1;

    else
        return 0;
}

//***********************************************************************************

function getNextId($table, $col="ID", $start=1000)
{
    $max = $start;
    $result = executeQuery("Select IFNULL((MAX($col)+1),$start) AS max from ".PREFIX."$table");

    // Get Max
    if ( $row = getRow($result) )
    {
        $max = $row["max"];
    }

    return $max;
}

//***********************************************************************************

function getRecord($table, $id, $col="ID")
{
    if ( eregi("([a-z])",$id) )
        $result = executeQuery("Select * from ".PREFIX."$table WHERE $col = '$id'");

    else
        $result = executeQuery("Select * from ".PREFIX."$table WHERE $col = $id");

    // Get Max
    if ( $row = getRow($result) )
    {
        return $row;
    }

    return 0;
}

//***********************************************************************************

function getRecordEx($table, $where="", $col="")
{

    if ( $where == "" )
        $result = executeQuery("Select * from ".PREFIX."$table");
    else
        $result = executeQuery("Select * from ".PREFIX."$table WHERE $where");

    // Get Max
    if ( $row = getRow($result) )
    {
        if ( $col != "" )
            return $row[$col];

        else
            return $row;
    }

    return 0;
}

//***********************************************************************************

function getColumn($table, $id, $colRet="TITLE", $col="ID")
{
    if ( eregi("([a-z])",$id) )
        $result = executeQuery("Select ".$colRet." from ".PREFIX."$table WHERE $col = '$id'");
    else
        $result = executeQuery("Select ".$colRet." from ".PREFIX."$table WHERE $col = $id");

    // Get Max
    if ( $row = getRow($result) )
    {
        return $row[0];
    }

    return 0;
}


function getColumnOnCondition($table, $colRet="TITLE", $condition="ID=0")
{
    $result = executeQuery("Select ".$colRet." from ".PREFIX."$table WHERE $condition");

    // Get Max
    if ( $row = getRow($result) )
    {
        return $row[0];
    }

    return 0;
}



function getColOnQryResult($_Qry)
{
    $result = executeQuery($_Qry);

    // Get Max
    if ( $row = getRow($result) )
    {
        return $row[0];
    }

    return 0;
}


//***********************************************************************************
//
//		SERVER FUNCTIONS
//
//***********************************************************************************

function sendMail($to, $from, $subject, $msg, $isHtml=1)
{
    $headers  = "";

    if ( $isHtml == 1 )
    {
        // Set headers to send Html pages, set the Content-type header
        $headers  = "MIME-Version: 1.0\r\n";
        $headers .= "Content-type: text/html; charset=iso-8859-1\r\n";
    }

    // Add From Header
    if ( $from != "" )
        $headers .= "From: ".$from."\r\n";

    // Send Mail
    mail($to, $subject, $msg, $headers);
}

//***********************************************************************************
//
//		FILE I/O FUNCTIONS
//
//***********************************************************************************

function readFromFile($filename)
{
    $filepath = PATH."".$filename;

    if ( !($fp = fopen($filepath, "r")) )
        die ("Could not open file for Reading, Filepath : ".$filepath);

    // Read From File
    $data = fread($fp, filesize($filepath));
    fclose($fp);

    return $data;
}

//***********************************************************************************

function writeToFile($filename, $data)
{
    $filepath = PATH."".$filename;

    // GetSize
    $size = strlen($data);


    // Write to the file
    $fa = fopen($filepath,"w+");
    fputs( $fa, $data, $size );
    fclose($fa);
}

//***********************************************************************************

function appendToFile($filename, $data)
{
    $filepath = PATH."".$filename;

    // GetSize
    $size = strlen($data);


    // Append to the file
    $fa = fopen($filepath,"a+");
    fputs( $fa, $data, $size );
    fclose($fa);
}

//***********************************************************************************

function deleteFile($filepath)
{
    $url = PATH.$filepath;

    if ( file_exists($url) )
        unlink($url);
}

//***********************************************************************************

function makeDirectory($name)
{
    $dirpath = PATH."".$name;

    if ( !file_exists($dirpath) )
        mkdir($dirpath, 0777);

    return true;
}

//***********************************************************************************

function deleteFolder($folder)
{
    $url = PATH."".$folder;

    if ( file_exists($url) )
        rmdir($url);
}

//***********************************************************************************
//
//		DATE/TIME FUNCTIONS
//
//***********************************************************************************

function formatDateTime($dateTime)
{
    if ( trim($dateTime) == "" || $dateTime == "0000-00-00 00:00:00" )
        return "";

    // In Format YYYY-MM-DD HH:MM:SS

    $year	= substr($dateTime,0,4);
    $month	= substr($dateTime,5,2);
    $day	= substr($dateTime,8,2);

    $hour	= substr($dateTime,11,2);
    $min	= substr($dateTime,14,2);
    $sec    = substr($dateTime,17,4);

    // Out Format 21 January, 2003 23:56
    return date("d F, Y H:i", mktime($hour, $min, $sec, $month, $day, $year));
}

function formatDate($date)
{
    if ( trim($date) == "" || $date == "0000-00-00" || $date == "0000-00-00 00:00:00" )
        return "";


    // In Format YYYY-MM-DD

    $year	= substr($date,0,4);
    $month	= substr($date,5,2);
    $day	= substr($date,8,2);

    // Out Format 21 January, 2003 23:56
    return date("d F, Y", mktime(0, 0, 0, $month, $day, $year));
}


function displayImage($folder, $image, $size="width=85 height=89")
{
    require(PATH."include/constants.php");

    if ( $size == "0" )
        $size = "";

    if ( stristr($image, ".") )
    {
        $filepath = PATH."upload/".$folder."/".$image;
        $fileurl  = $ROOT."upload/".$folder."/".$image;
    }
    else
    {
        $filepath = PATH."upload/".$folder."/".$image.".jpg";
        $fileurl  = $ROOT."upload/".$folder."/".$image.".jpg";
    }

    $out = "<img src='images/spacer.gif' border='0' ".$size." alt='No Image'>";

    if ( file_exists($filepath) )
    {
        $out = "<img src='$fileurl' border='0' ".$size." >";
    }
    return $out;
}


function countryDropDown($country, $field="country")
{
    $dropdown = "
						<select name='$field' size='1' class='effect'>";

    if ( isset($country) && $country != "" )
        $dropdown .= "<option value='$country'>$country</option>";
    else
        $dropdown .= "<option value=''>Please select a country  .....</option>";

    $dropdown .= "
							<option value='Albania'>Albania</option>
							<option value='Algeria'>Algeria</option>
							<option value='Algeria'>Algeria</option>
							<option value='America Samoa'>American Samoa</option>
							<option value='Andorra'>Andorra</option>
							<option value='Anguilla'>Anguilla</option>
							<option value='Antigua'>Antigua</option>
							<option value='Argentina'>Argentina</option>
							<option value='Aruba'>Aruba</option>
							<option value='Australia'>Australia</option>
							<option value='Austria'>Austria</option>
							<option value='Bahamas'>Bahamas</option>
							<option value='Bahrain'>Bahrain</option>
							<option value='Bangladesh'>Bangladesh</option>
							<option value='Barbados'>Barbados</option>
							<option value='Barbuda'>Barbuda</option>
							<option value='Belgium'>Belgium</option>
							<option value='Belize'>Belize</option>
							<option value='Belorus'>Belorus</option>
							<option value='Benin'>Benin</option>
							<option value='Bermuda'>Bermuda</option>
							<option value='Bolivia'>Bolivia</option>
							<option value='Bonaire'>Bonaire</option>
							<option value='Botswana'>Botswana</option>
							<option value='Brazil'>Brazil</option>
							<option value='British Virgin Islands'>British Virgin Islands</option>
							<option value='Brunei'>Brunei</option>
							<option value='Bulgaria'>Bulgaria</option>
							<option value='Burkina Faso'>Burkina Faso</option>
							<option value='Burundi'>Burundi</option>
							<option value='Cambodia'>Cambodia</option>
							<option value='Cameroon'>Cameroon</option>
							<option value='Canada'>Canada</option>
							<option value='Canary Islands'>Canary Islands</option>
							<option value='Cape Verde Islands'>Cape Verde Islands</option>
							<option value='Cayman Islands'>Cayman Islands</option>
							<option value='Central African Republic'>Central African Republic</option>
							<option value='Chad'>Chad</option>
							<option value='Channel Islands'>Channel Islands</option>
							<option value='Chile'>Chile</option>
							<option value='China, Peoples Republic of'>China, Peoples Republic of</option>
							<option value='Christmas Island'>Christmas Island</option>
							<option value='Cocos Islands'>Cocos Islands</option>
							<option value='Colombia'>Colombia</option>
							<option value='Congo'>Congo</option>
							<option value='Cook Islands'>Cook Islands</option>
							<option value='Costa Rica'>Costa Rica</option>
							<option value='Croatia'>Croatia</option>
							<option value='Curacao'>Curacao</option>
							<option value='Cyprus'>Cyprus</option>
							<option value='Czech Republic'>Czech Republic</option>
							<option value='Denmark'>Denmark</option>
							<option value='Djibouti'>Djibouti</option>
							<option value='Dominica'>Dominica</option>
							<option value='Dominican Republic'>Dominican Republic</option>
							<option value='Ecuador'>Ecuador</option>
							<option value='Egypt'>Egypt</option>
							<option value='El Salvador'>El Salvador</option>
							<option value='England'>England</option>
							<option value='Equitorial Guinea'>Equitorial Guinea</option>
							<option value='Eritrea'>Eritrea</option>
							<option value='Estonia'>Estonia</option>
							<option value='Ethiopia'>Ethiopia</option>
							<option value='Faeroe Islands'>Faeroe Islands</option>
							<option value='Fiji'>Fiji</option>
							<option value='Finland'>Finland</option>
							<option value='France'>France</option>
							<option value='French Guiana'>French Guiana</option>
							<option value='French Polynesia'>French Polynesia</option>
							<option value='Gabon'>Gabon</option>
							<option value='Gambia'>Gambia</option>
							<option value='Germany'>Germany</option>
							<option value='Ghana'>Ghana</option>
							<option value='Gibraltar'>Gibraltar</option>
							<option value='Greece'>Greece</option>
							<option value='Greenland'>Greenland</option>
							<option value='Grenada'>Grenada</option>
							<option value='Guadeloupe'>Guadeloupe</option>
							<option value='Guam'>Guam</option>
							<option value='Guatemala'>Guatemala</option>
							<option value='Guinea'>Guinea</option>
							<option value='Guinea-Bissau'>Guinea-Bissau</option>
							<option value='Guyana'>Guyana</option>
							<option value='Haiti'>Haiti</option>
							<option value='Holland'>Holland</option>
							<option value='Honduras'>Honduras</option>
							<option value='Hong Kong'>Hong Kong</option>
							<option value='Hungary'>Hungary</option>
							<option value='Iceland'>Iceland</option>
							<option value='India'>India</option>
							<option value='Indonesia'>Indonesia</option>
							<option value='Iran'>Iran</option>
							<option value='Ireland'>Ireland</option>
							<option value='Israel'>Israel</option>
							<option value='Italy'>Italy</option>
							<option value='Ivory Coast (Cote d'Ivoire)'>Ivory Coast (Cote d'Ivoire)</option>
							<option value='Jamaica'>Jamaica</option>
							<option value='Japan'>Japan</option>
							<option value='Jordan'>Jordan</option>
							<option value='Kazakhstan'>Kazakhstan</option>
							<option value='Kenya'>Kenya</option>
							<option value='Kiribati'>Kiribati</option>
							<option value='Korea, South'>Korea, South</option>
							<option value='Kosrae'>Kosrae</option>
							<option value='Kuwait'>Kuwait</option>
							<option value='Kyrgyzstan'>Kyrgyzstan</option>
							<option value='Laos'>Laos</option>
							<option value='Latvia'>Latvia</option>
							<option value='Lebanon'>Lebanon</option>
							<option value='Lesotho'>Lesotho</option>
							<option value='Liberia'>Liberia</option>
							<option value='Liechtenstein'>Liechtenstein</option>
							<option value='Lithuania'>Lithuania</option>
							<option value='Luxembourg'>Luxembourg</option>
							<option value='Macau'>Macau</option>
							<option value='Macedonia'>Macedonia</option>
							<option value='Madagascar'>Madagascar</option>
							<option value='Madeira'>Madeira</option>
							<option value='Malawi'>Malawi</option>
							<option value='Malaysia'>Malaysia</option>
							<option value='Maldives'>Maldives</option>
							<option value='Mali'>Mali</option>
							<option value='Malta'>Malta</option>
							<option value='Marshall Islands'>Marshall Islands</option>
							<option value='Martinique'>Martinique</option>
							<option value='Mauritania'>Mauritania</option>
							<option value='Mauritius'>Mauritius</option>
							<option value='Mexico'>Mexico</option>
							<option value='Micronesia'>Micronesia</option>
							<option value='Monaco'>Monaco</option>
							<option value='Montserrat'>Montserrat</option>
							<option value='Morocco'>Morocco</option>
							<option value='Mozambique'>Mozambique</option>
							<option value='Myanmar'>Myanmar</option>
							<option value='Namibia'>Namibia</option>
							<option value='Nepal'>Nepal</option>
							<option value='Netherlands'>Netherlands</option>
							<option value='Netherlands Antilles'>Netherlands Antilles</option>
							<option value='Nevis'>Nevis</option>
							<option value='New Caledonia'>New Caledonia</option>
							<option value='New Zealand'>New Zealand</option>
							<option value='Nicaragua'>Nicaragua</option>
							<option value='Niger'>Niger</option>
							<option value='Nigeria'>Nigeria</option>
							<option value='Niue'>Niue</option>
							<option value='Norfolk Island'>Norfolk Island</option>
							<option value='Northern Ireland'>Northern Ireland</option>
							<option value='Northern Mariana Islands'>Northern Mariana Islands</option>
							<option value='Norway'>Norway</option>
							<option value='Oman'>Oman</option>
							<option value='Pakistan'>Pakistan</option>
							<option value='Palau'>Palau</option>
							<option value='Panama'>Panama</option>
							<option value='Papua New Guinea'>Papua New Guinea</option>
							<option value='Paraguay'>Paraguay</option>
							<option value='Peru'>Peru</option>
							<option value='Philippines'>Philippines</option>
							<option value='Poland'>Poland</option>
							<option value='Ponape'>Ponape</option>
							<option value='Portugal'>Portugal</option>
							<option value='Puerto Rico'>Puerto Rico</option>
							<option value='Qatar'>Qatar</option>
							<option value='Reunion'>Reunion</option>
							<option value='Romania'>Romania</option>
							<option value='Rota'>Rota</option>
							<option value='Russia'>Russia</option>
							<option value='Rwanda'>Rwanda</option>
							<option value='Saba'>Saba</option>
							<option value='Saipan'>Saipan</option>
							<option value='Saudi Arabia'>Saudi Arabia</option>
							<option value='Scotland'>Scotland</option>
							<option value='Senegal'>Senegal</option>
							<option value='Seychelles'>Seychelles</option>
							<option value='Sierra Leone'>Sierra Leone</option>
							<option value='Singapore'>Singapore</option>
							<option value='Slovak Republic'>Slovak Republic</option>
							<option value='Slovenia'>Slovenia</option>
							<option value='Solomon Islands'>Solomon Islands</option>
							<option value='South Africa'>South Africa</option>
							<option value='Spain'>Spain</option>
							<option value='Sri Lanka'>Sri Lanka</option>
							<option value='St. Barthelemy'>St. Barthelemy</option>
							<option value='St. Christopher'>St. Christopher</option>
							<option value='St. Croix'>St. Croix</option>
							<option value='St. Eustatius'>St. Eustatius</option>
							<option value='St. John'>St. John</option>
							<option value='St. Kitts'>St. Kitts</option>
							<option value='St. Lucia'>St. Lucia</option>
							<option value='St. Maarten'>St. Maarten</option>
							<option value='St. Martin'>St. Martin</option>
							<option value='St. Thomas'>St. Thomas</option>
							<option value='St. Vincent and the Grenadines'>St. Vincent and the Grenadines</option>
							<option value='Sudan'>Sudan</option>
							<option value='Suriname'>Suriname</option>
							<option value='Swaziland'>Swaziland</option>
							<option value='Sweden'>Sweden</option>
							<option value='Switzerland'>Switzerland</option>
							<option value='Syria'>Syria</option>
							<option value='Tahiti'>Tahiti</option>
							<option value='Taiwan'>Taiwan</option>
							<option value='Tajikistan'>Tajikistan</option>
							<option value='Tanzania'>Tanzania</option>
							<option value='Thailand'>Thailand</option>
							<option value='Tinian'>Tinian</option>
							<option value='Togo'>Togo</option>
							<option value='Tonga'>Tonga</option>
							<option value='Tortola'>Tortola</option>
							<option value='Trinidad and Tobago'>Trinidad and Tobago</option>
							<option value='Truk'>Truk</option>
							<option value='Tunisia'>Tunisia</option>
							<option value='Turkey'>Turkey</option>
							<option value='Turks and Caicos Islands'>Turks and Caicos Islands</option>
							<option value='Tuvalu'>Tuvalu</option>
							<option value='U.S. Virgin Islands'>U.S. Virgin Islands</option>
							<option value='Uganda'>Uganda</option>
							<option value='Ukraine'>Ukraine</option>
							<option value='Union Island'>Union Island</option>
							<option value='United Arab Emirates'>United Arab Emirates</option>
							<option value='United Kingdom'>United Kingdom</option>
							<option value='United States'>United States</option>
							<option value='Uruguay'>Uruguay</option>
							<option value='Uzbekistan'>Uzbekistan</option>
							<option value='Vanuatu'>Vanuatu</option>
							<option value='Venezuela'>Venezuela</option>
							<option value='Vietnam'>Vietnam</option>
							<option value='Virgin Gorda'>Virgin Gorda</option>
							<option value='Wake Island'>Wake Island</option>
							<option value='Wales'>Wales</option>
							<option value='Wallis and Futuna Islands'>Wallis and Futuna Islands</option>
							<option value='Western Samoa'>Western Samoa</option>
							<option value='Yap'>Yap</option>
							<option value='Yemen'>Yemen</option>
							<option value='Zaire'>Zaire</option>
							<option value='Zambia'>Zambia</option>
							<option value='Zimbabwe'>Zimbabwe</option>
						</select>
					";

    return $dropdown;

} // function countryDropDown ends here //


//***********************************************************************************

?>
