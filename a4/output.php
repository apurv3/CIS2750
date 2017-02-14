<?php 

session_start();

$str = shell_exec("./filecontents ".$_GET["var"]);

echo htmlspecialchars_decode($str);

// note that here the quotes aren't converted
//echo htmlspecialchars_decode($str, ENT_NOQUOTES);
 ?>