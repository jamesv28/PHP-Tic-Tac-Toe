<?php
session_start();

//reset the game
foreach($_SESSION as $key => $value){
    unset($_SESSION[$key]);
}
session_destroy();

?><!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Sign up</title>
        <link rel ='stylesheet' type='text/css' href='style.css'>
	<script type="text/javascript" src="http://code.jquery.com/jquery-2.0.3.js"></script>
        <script type="text/javascript" src="http://malsup.github.com/jquery.cycle.lite.js"></script>
        <script type="text/javascript">
            $(document).ready(function() {
                $('.slideshow').cycle({
		fx: 'fade' ,
                speed: 25,
                random: 0
	});
});
</script>
    </head>
    <body>
        <div id ="content">
            <div class="slideshow">
           <img src="images/image01.jpg" alt="landscape">
           <img src="images/image02.jpeg" alt="landscape">
           <img src="images/image03.jpg" alt="landscape">
           <img src="images/image04.jpg" alt="landscape">
       	   <img src="images/image05.jpg" alt="landscape">
			</div><!--ends the images-->
           <div id= "welcome">
            <h1> Sign in to Battle! </h1>
            <form action='playground.php' method='POST'>
                Player 1: <input type ='text' name ='player1'> <br>
                Player 2:<input type='text' name ='player2'> <br>
                <label> Game Size: </label>
                <select name ='gameSize' id='gameSize'>
                   <?php 
                  
                   for($i = 3; $i <= 10; $i++){
                       echo ("<option value='" . $i . "'> " . $i . " x " . $i . " </option>");
                   }
                   
                   ?>
                </select><br>
               <input type="submit" value="Start" name="start">

            </form>
        </div>
    </body>
</html>
