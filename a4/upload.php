<?php

error_reporting(E_ALL);
ini_set("display_errors", 1);

$target_dir = "files/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);

// Check if image file is a actual image or fake image
if(empty($_POST["submit"]))
{
    $uploadOk = 1;
}

// Check file size
if($_FILES["fileToUpload"]["size"] > 5000000)
{
    echo "Sorry, your file is too large."; 
    $uploadOk = 0;
}

echo "[{$target_file}]";

// Check if $uploadOk is set to 0 by an error
if ($uploadOk === 0)
{
    echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
}
else
{
    if(move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file))
    {
        header("Location: a4.php");
        exit;
    } else {
        echo "Sorry, there was an error uploading your file.";
    }
}
