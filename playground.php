<?php
session_start();
include 'board.inc';
if (isset($_POST['gameSize'])){
    $Board1 = new Board($_POST['player1'], $_POST['player2'], $_POST['gameSize']);
    $_SESSION['board1'] = serialize($Board1);
} else if (isset($_SESSION['board1'])) {
    $Board1 = unserialize($_SESSION['board1']);
}
if(isset($_POST['squareSubmit'])){
  $Board1->Update($_POST['squareSubmit']);
   $_SESSION['board1'] = serialize($Board1);
}
?><!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>playground </title>
        <link rel ='stylesheet' type='text/css' href='style.css'>
        <script type="text/javascript" src="http://code.jquery.com/jquery-2.0.3.js"></script>
        <script type="text/javascript" src="http://malsup.github.com/jquery.cycle.lite.js"></script>
        <script type="text/javascript">
            $(document).ready(function() {
    $('.slideshow').cycle({
		fx: 'fade',
                speed: 25
                
	});
});
</script>
    </head>
    <body>
        <div id='content'>
             <div class="slideshow">
           <img src="images/image01.jpg" alt="landscape">
           <img src="images/image02.jpeg" alt="landscape">
           <img src="images/image03.jpg" alt="landscape">
           <img src="images/image04.jpg" alt="landscape">
       	   <img src="images/image05.jpg" alt="landscape">
			</div><!--ends the images-->
            <div id='board'>
            <h1> Battle Time </h1>
            <?php $Board1->Messages(); ?>
            <div id='playground'>
           <?php $Board1->Build(); ?>
           
            </div><!--Ends the game area-->
            <a href="index.php">New Game </a>
            </div>
            </div><!--ends the content div-->
    </body>
</html>
