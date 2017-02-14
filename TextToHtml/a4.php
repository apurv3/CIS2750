<?php
// Start the session
session_start();
?>
<!DOCTYPE html>
<html>
<head>

    <script type="text/javascript">
      <!--
          function toggle_visibility(id) {
             var e = document.getElementById(id);
             if(e.style.display == 'block')
                e.style.display = 'none';
             else
                e.style.display = 'block';
          }
      //-->
    </script>

    <style type="text/css">

      #popupBoxOnePosition{
        top: 0; left: 0; position: fixed; width: 100%; height: 120%;
        background-color: rgba(0,0,0,0.7); display: none;
      }
      #popupBoxTwoPosition{
        top: 0; left: 0; position: fixed; width: 100%; height: 120%;
        background-color: rgba(0,0,0,0.7); display: none;
      }#popupBoxThreePosition{
        top: 0; left: 0; position: fixed; width: 100%; height: 120%;
        background-color: rgba(0,0,0,0.7); display: none;
      }
      .popupBoxWrapper{
        width: 550px; margin: 50px auto; text-align: left;
      }
      .popupBoxContent{
        background-color: #FFF; padding: 15px;
      }
      #convert{
        float: right;
        width: 50%;
        height: 50%;
      }
      #DB_store{
        float: right;
        width: 50%;
        height: 50%;
      }
    </style>


<title>a4.php</title>

<style type="text/css">
#box {
    background-color: #ffccdd;
    width: 300px;
    border: 25px solid white;
    border-radius: 8px;
    padding: 25px;
    margin: 25px;
}

.inputfile {
  /* visibility: hidden etc. wont work */
  width: 700px;
  height: 100px;
  background-color: #ffccdd;
  opacity:0 ;
  overflow: hidden;*/
  position: absolute;
  z-index: -1;
}
.inputfile:focus + label {
   keyboard navigation 
  outline: 1px dotted #000;
  outline: -webkit-focus-ring-color auto 5px;*/
}
.inputfile + label * {
  pointer-events: none;
}


#fileToUpload {
    display:none;
}

</style>




</head>

<body background= "r2.jpg">

<div >


<div id="popupBoxOnePosition">
      <div class="popupBoxWrapper">
        <div class="popupBoxContent">
          <?php
  $fileList = array();
  if ($handle = opendir('./files'))
  {
    while (false !== ($file = readdir($handle))) 
    {
        if ($file != "." && $file != ".." && $file[0] != "."
        && substr($file,-strlen(".DS_Store")) != ".DS_Store" 
        && substr($file,-strlen(".html")) != ".html" 
        && substr($file,-strlen(".info")) != ".info" 
        && $file != "") 
        {
            $fileList[] = $file;
        }
    }
  natcasesort($fileList); // sort.
  closedir($handle);
  }
  foreach($fileList as $file) 
  {
    ?>
        <form action="" method="post">
        <input type="radio" name="radio1" value="<?php echo $file; ?>"><?php echo $file;?><br />    

    <?php
  }
  ?>
  <input type="submit" name="submit1" value="OK" />
  </form>
  <div>
  <?php
      if (isset($_POST['submit1'])) {
      if(isset($_POST['radio1']))
      {
        exec('./a4 files/'.$_POST['radio1']);
      }
    }
    ?>
  </div>

         <button href="javascript:void(0)" onclick="toggle_visibility('popupBoxOnePosition');">Cancel</button> 
        </div>
      </div>
    
    </div>



    <div >


<div id="popupBoxTwoPosition">
      <div class="popupBoxWrapper">
        <div class="popupBoxContent">
          <?php
  $fileList = array();
  if ($handle = opendir('./files'))
  {
    while (false !== ($file = readdir($handle))) 
    {
        if ($file != "." && $file != ".." && $file[0] != "."
        && substr($file,-strlen(".DS_Store")) != ".DS_Store" 
        && substr($file,-strlen(".html")) != ".html" 
        && substr($file,-strlen(".info")) != ".info" 
        && $file != "")  
        {
            $fileList[] = $file;
        }
    }
  natcasesort($fileList); // sort.
  closedir($handle);
  }
  foreach($fileList as $file) 
  {
    ?>
        <form action="" method="post">
        <input type="radio" name="radio" value="<?php echo $file; ?>"><?php echo $file;?><br />    

    <?php
  }
  ?>
  <input type="submit" name="submit" value="OK" />
  </form>
  <div>
  <?php
      if (isset($_POST['submit'])) {
      if(isset($_POST['radio']))
      {
        exec('./a4 files/'.$_POST['radio']);
        exec('./a4 files/'.$_POST['radio'].' 1');
        unlink ('files/'.$_POST['radio'].'.html');
      }
    }
    ?>
  </div>

         <button href="javascript:void(0)" onclick="toggle_visibility('popupBoxTwoPosition');">Cancel</button> 
        </div>
      </div>
    
    </div>

  
    <div id="wrapper" style:"width:100%; height:30%">

    <button href="javascript:void(0)" id="convert" onclick="toggle_visibility('popupBoxOnePosition');" style="width:33%;">Convert</button> 
    <button href="javascript:void(0)" id="DB_store" onclick="toggle_visibility('popupBoxTwoPosition');" style="width:33%;">DB Store</button> 
    <form action="upload.php" method="post" enctype="multipart/form-data">
    <input type="file" name="fileToUpload" id ="fileToUpload" onchange="javascript:this.form.submit();">
    <input type="button" onclick="document.getElementById('fileToUpload').click()" value="Upload" style="width:33%;"/>
    </form>
    
    </div><!-- wrapper end -->
<!--<input type="file" name="file" id="file" class="inputfile" /></button>
<button type = "button"><label for="file"><h1>Upload</h1></label></button>-->


<!--<button id="button2" style="width:700px;height:100px;"><H1>Upload</H1></button>-->



<script type = "text/javascript">

function closeScreen(){
	  $('#dialog2').dialog('close')
}

function closeScreen1(){
	  $('#dialog').dialog('close')
}

//This is for Convert button
$(function() {
  // this initializes the dialog (and uses some common options that I do)
  $("#dialog").dialog({
    autoOpen : false, modal : true, show : "blind", hide : "blind"
  });
  // next add the onclick handler
  $("#button").click(function() {
    $("#dialog").dialog("open");
    return false;
  });
});


//This is for UPLOAD button
$(function() {
  // this initializes the dialog (and uses some common options that I do)
  $("#dialog2").dialog({
    autoOpen : false, modal : true, show : "blind", hide : "blind"
  });
  // next add the onclick handler
  $("#button2").click(function() {
    $("#dialog2").dialog("open");
    return false;
  });
});
</script>
</div>



<!--UPLOAD DIALOG-->
<div id="dialog" title="Upload">
 
 <form action="uploads.php" method="post" enctype="multipart/form-data">
</form>
 

</div>
       


<!--TEXT FILE BOX-->

<div id = "box">
<?php
	 $files = array(); 
	if ($handle = opendir('./files'))
	{
		while (false !== ($file = readdir($handle))) 
		{
    		if ($file != "." && $file != ".." && $file[0] != "."
    		&& substr($file,-strlen(".DS_Store")) != ".DS_Store" 
    		&& substr($file,-strlen(".html")) != ".html" 
    		&& substr($file,-strlen(".info")) != ".info" 
    		&& $file != "") 
    		{
    			//print("<a href=\"./files/".$file."\">".$file."</a><br />\n");
          $files[] = $file; // put in array.
    		}
		}
    natcasesort($files); // sort.
    foreach($files as $file) {
      echo("<a href=\"./files/".$file."\">".$file."</a><br />\n");
    }
	//echo '<br /><br /><a href=".."></a>';
	closedir($handle);
	}
?>
</div>


<!--HTML FILE BOX-->
<div id = "box">
	<?php
		

  $files = array(); 
  if ($handle = opendir('./files'))
  {
    while (false !== ($file = readdir($handle))) 
    {
      if ($file != "." && $file != ".." 
      && substr($file,-strlen(".html")) == ".html" 
      && $file != "") 
      {
        $files[] = "<a href= files/".$file.">".$file."</a><br />\n";//$file; // put in array.
      }
    }

    $output= shell_exec("./output");
    $keywords = preg_split("/[\s,]+/",$output);
    foreach($keywords as $output){
    $test= ("output.php/?var=$output");
    $files[] = "<a href='$test'>$output<br> </a>\n";
    
    }
   
    $fruit = array_pop($files);
    natcasesort($files); // sort.
    foreach($files as $file) {
      echo($file);
    }

    closedir($handle);
  }

	?>
</div>



</body>

</html>