/*****************************************************/
/********************INSTALLATION*********************/
/*****************************************************/

Run the the 'install.sh' bash script in a terminal.

	....<dir>$ ./install.sh

(INSTALLATION FILES CAN BE DELETED AFTER BUILDING)



/**************************************************/
/******************** RUNNING *********************/
/**************************************************/

1) Run ./roscore on a separate terminal
2) Navigate to workspace directory in current terminal
3) Execute the 'run.sh' script in the terminal

	....<dir>/sudoku_bot_ws$ ./run.sh

4) After initialisation, enter 1 to send starting grid
   to the 'num_grids/vector' topic
  ( The process starts to move the bot grid by grid )



/**************************************************/
/******************** CLOSING *********************/
/**************************************************/

1) Execute the 'terminate.sh' script to close 
   processes that are running in the background.
2) Terminate 'roscore'.
