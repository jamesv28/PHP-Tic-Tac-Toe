<?php
class Board {
    public $player1;
    public $player2;
   public $grid_size;
   public $board_size;
   public $squares = array();
   public $turn;
   public $winner;
   public $tie;
   
   
   public function __construct($p1, $p2, $grid = 3) {
       $this->player1 = $p1;
       $this->player2 = $p2;
       
       if (is_numeric($grid)){
           $this->grid_size = intval($grid);
       }else{
           die('you messed up.  Grid gotta be a number! ');
       }
       $this->board_size = $this->grid_size * $this->grid_size;
       $this->winner = 'none';
       $this->tie = FALSE;
       $this->turn = (rand(0,1))? "X" : "O";
       //create a variable to increment the squares
       $row = 1;
       $col = 1;
       
       for ($i = 0; $i <$this->board_size; $i++){
           $this->squares[$i]['contents'] = 'button';
           
           $this->squares[$i]['row'] = $row;
           $this->squares[$i]['col'] = $col;

            if ($col == $this->grid_size){
                $row++;
                $col = 0;        
            }
            $col++;
            
            
       } // end for loop
   } //end constructor
   
   public function Build(){
       
       echo ("<form method =\"POST\" action=\"" . $_SERVER['PHP_SELF'] . "\">");
       echo ("\n\t\t<table border=\"1\" bordercolor=\"#FFCC00\" width=\"500px\" cellpadding=\"1\" cellspacing=\"0\">");
       echo ("\n\t\t\t<tr>");
       
       for ($i = 0; $i < $this->board_size; $i++){
           echo("\n\t\t\t\t<td>");
                switch($this->squares[$i]['contents']){
                    case 'button':
                        echo("<input type=\"submit\" value=\"" . $i  . "\" name=\"squareSubmit\" />");
                        break;
                    case 'X':
                        echo("X");
                        break;
                    case 'O':
                        echo('O');
                        break;
                    case 'clear':
                        echo('&nbsp;');
                        break;
                    default :
                         echo("<input type=\"submit\" value=\"" . $i  . "\" name=\"" . $i  . "\" />");
                        break;
                }
           
           echo("</td>");
           
           $n = $i + 1;
           if (($n % $this->grid_size) == 0 && $n != $this->board_size){
               echo ("\n\t\t\t</tr><tr>");
           }
           
       }// end for loop
       
       
       echo ("\n\t\t\t</tr>");
       echo ("\n\t\t</table>");
       echo ("\n\n\t</form>");
   
} // end build function

public function Update($updated_button) {
    if(is_numeric($updated_button)==FALSE){
        die("You must submit a numeric value");
    }
    
    $updated_button = intval($updated_button);

    $this->squares[$updated_button]['contents']= $this->turn;
    
    if($this->turn=='X'){
        $this->turn='O';
    } elseif($this->turn=='O'){
         $this->turn='X';
    }
    self::_WinCheck($updated_button);
    if($this->winner == "none"){
        self::_tieCheck();
    }
} // end Update


protected function _WinCheck($updated_button){
    
     if($this->turn=='X'){
        $last_turn = 'O';
    } elseif($this->turn=='O'){
         $last_turn='X';
    }
    $check_row = $this->squares[$updated_button]['row'];
    $check_col = $this->squares[$updated_button]['col'];
    $row_counter = 0;
    $col_counter = 0;
    
    for($i = 0; $i < $this->board_size; $i++){
        if($this->squares[$i]['row'] == $check_row && $this->squares[$i]['contents'] == $last_turn){
           $row_counter++; 
        }
        
        if($this->squares[$i]['col'] == $check_col && $this->squares[$i]['contents'] == $last_turn){
           $col_counter++; 
        }
        
    }//end for loop
    
    
    
    $diag1_counter = 0;
    $diag2_counter = 0;
    $row_count_up = 1;
    $row_count_down = $this->grid_size;
    $col_count_across = 1;
    
    for($n = 0; $n < $this->board_size; $n++){
        
        for($i = 0; $i < $this->board_size; $i++){
            
            if($this->squares[$i]['row']== $row_count_up &&
               $this->squares[$i]['col']== $col_count_across &&
               $this->squares[$i]['contents']== $last_turn ){
                    $diag1_counter++;
            }//ends the if statement
            
            if($this->squares[$i]['row']== $row_count_down &&
               $this->squares[$i]['col']== $col_count_across &&
               $this->squares[$i]['contents']== $last_turn ){
                    $diag2_counter++;
            }//ends the if statement
            
        }//ends for inner loop
        
        $row_count_up++;
        $row_count_down--;
        $col_count_across++;
        
    }//ends outer loop
    
    self::_Winner($row_counter, $last_turn);
    self::_Winner($col_counter, $last_turn);
    self::_Winner($diag1_counter, $last_turn);
    self::_Winner($diag2_counter, $last_turn);
    
    
    
    if($this->winner != "none"){
        for($i = 0; $i < $this->board_size; $i++){
            if($this->squares[$i]['contents']=='button'){
                $this->squares[$i]['contents']= 'clear';
            }
        }
    }
    
}//end _winCheck

    protected function _Winner($counters, $last_turn){
         if($this->winner == "none"){
            if($counters == $this->grid_size){
                if($last_turn == 'X'){
                    $this->winner = $this->player1;
                }elseif($last_turn == 'O'){
                    $this->winner = $this->player2;
                }
            }
         }
    }//ends the winner function

protected function _tieCheck(){
    $play_count = 0;
    for($i = 0; $i < $this->board_size; $i++){
        if($this->squares[$i]['contents'] != "button"){
            $play_count++;
        }else{
            break;
        }//end if statement
    }//end for
    if($play_count == $this->board_size){
        $this->tie = TRUE;
    }//ends if statement
    
}//ends _tieCheck

public function Messages(){
    if($this->turn == 'X'){
        $name = $this->player1;
        $winner_name = $this->player2;
    }elseif($this->turn == 'O'){
        $name = $this->player2;
        $winner_name = $this->player1;
    }//ends if
    
    if($this->tie == FALSE && $this->winner == "none"){
        echo ("<h3>It's your turn " . $name . "</h3>");
    }elseif($this->tie == FALSE && $this->winner != "none"){
        echo ("<h3>You Win " . $winner_name . "!</h3>");
    }elseif($this->tie == TRUE && $this->winner == "none"){
        echo ("<h3>It's a TIE!</h3>");
    }
    
}//ends Messages 
    
} // end class Board

?>
