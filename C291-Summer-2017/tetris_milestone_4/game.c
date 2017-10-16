/* game.c --- 
 * 
 * Filename: game.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Tue Sep  6 11:08:59 2016
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2016 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <unistd.h> 
#include <ncurses.h>
#include <time.h>
#include "highscore.h"
#include "game.h"
#include "well.h"
#include "tetris.h"
#include "tetromino.h"
#include "key.h"

void init_game(void) {
  int x,y;
}

highscore_t *game(highscore_t *highscores) {
  static int state = INIT;
  tetromino_t *next = NULL;
  tetromino_t *current = NULL;
  well_t *w;
  int x,y;
  int c;
  int arrow;
  struct timespec tim = {0,1000000};
  struct timespec tim_ret;
  int move_counter = 0;
  int move_timeout = 500;
  int status;
  int counter = 0;
  int lines_cleared = 0;  //the number of the cleared lines
  int score = 0;   //the score
  char str[80];  
  char initial_name[3];
  int tag=0;
  //int lines_cleared = 0; //*deriving from the prune_well
  //int previous_score = 0; //* previous score
  while(1) {
    switch(state) {
    case INIT:               // Initialize the game, only run one time 
      initscr();
      noecho();              // Do not echo input characters 
      getmaxyx(stdscr,y,x);  // Get the screen dimensions 
      w = init_well(((x/2)-(WELL_WIDTH/2)),3,WELL_WIDTH,WELL_HEIGHT);
      //control the splash screen
      mvprintw(10,x/2-25,"Splash screen: hit any button to start the game!!");

      nodelay(stdscr,FALSE);  // Do not wait for characters using getch.  
      getch();    
      nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
      mvprintw(10,x/2-25,"                                                 ");      
//      start_color();
//      init_pair(1, COLOR_RED, COLOR_BLACK);

      draw_well(w);
      srand(time(NULL));     // Seed the random number generator with the time. Used in create tet. 
      display_score(score, w->upper_left_x-15,w->upper_left_y);  
      state = ADD_PIECE;
      break;
    case ADD_PIECE:          // Add a new piece to the game

      if (next) {
	current = next;
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      else {
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      //show the next piece
//         mvprintw(10,20," %d  ",tag++);
      undisplay_next_tetromino(current);
//      attron(COLOR_PAIR(1));
      display_next_tetromino(next);
//      attroff(COLOR_PAIR(1));

      if(check_collision(current) == COLLIDE ) state = GAME_OVER; //check the current situation(on top: game over)
      else {
        display_tetromino(current);
        state = MOVE_PIECE;
      }
//      status = move_tet(current,current->upper_left_x,current->upper_left_y+1);
      
//      if(status == MOVE_FAILED) state = GAME_OVER; 

      break;
    case MOVE_PIECE:         // Move the current piece 	

      if ((arrow = read_escape(&c)) != NOCHAR) {
	if (arrow == UP) {
	  undisplay_tetromino(current);
	  rotate_ccw(current);
	  display_tetromino(current);
	}
	else if (arrow == DOWN) {
	  undisplay_tetromino(current);
	  rotate_cw(current);
	  display_tetromino(current);
	}
	else if (arrow == LEFT) {
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x-1,current->upper_left_y);
	  display_tetromino(current);
	}
	else if (arrow == RIGHT) {
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x+1,current->upper_left_y);
	  display_tetromino(current);
	}
      	else if (arrow == REGCHAR) {
	  if (c == ' ') {
	    move_timeout = DROP_RATE;
 	  }
	  if (c == 'q') {
	    state = GAME_OVER;
 	  }
	}
      } 
      if (move_counter++ >= move_timeout) {
	counter++;
	undisplay_tetromino(current);
	status = move_tet(current,current->upper_left_x,current->upper_left_y+1);
	display_tetromino(current);
	if (status == MOVE_FAILED) {
	  lines_cleared = prune_well(w);  //*prune well
          score = compute_score(score, lines_cleared);  //compute the score
          display_score(score, w->upper_left_x-15,w->upper_left_y);  //display

//          mvprintw(10,10," %d  ",score);
	  state = ADD_PIECE;
	  move_timeout = BASE_FALL_RATE;
	}
	move_counter = 0;
      }
      break;
    case GAME_OVER:
      nodelay(stdscr,FALSE);
      clear();
      getmaxyx(stdscr,y,x);
      mvprintw(1,x/2-5,"  GAME_OVER  ");
      mvprintw(2,x/2-5,"score:   %d",score);//***
	//input score
      char *fp = "score.txt" ;
      
      //load the score in the fule first
      highscore_t *list;
      list = load_scores(fp);      
      
      if(compare_highscore(list, score, 10)) {
      //insert currrent score based on the case: num of scores<=10
      mvprintw(3,x/2-5,"Awesome!Input your name:");
      mvscanw(3,x/2-5+26,"%s",&initial_name);
      mvprintw(3,x/2-5+26,"%s",initial_name);
      //insert score      
      list = insert_score(list, initial_name, score);
      store_scores(fp, list);
      }
      //list = load_scores(fp);      
      print_score_list(list,  x/2-5, 4, 10);

      mvprintw(16,x/2-5,"Hit q to exit");
      //
      //scanf("%d",&tag);
      getch(); // Wait for a key to be pressed. 
      getch(); // Wait for a key to be pressed. 
      state = EXIT;
      break;
    case EXIT:
      return(highscores);  // Return the highscore structure back to main to be stored on disk. 
      break;
    }
    refresh();
    nanosleep(&tim,&tim_ret);
  }
}

/* game.c ends here */
