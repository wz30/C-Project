/*
name: q4.c
author: Wei Zhang
date: 5/22/2017
explain: answer for question 4
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52
#define Hands 5 //5 poker in hands
 
//prototypes
void shuffle(unsigned int wDeck[][FACES]); //shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], const char *wFace[], 
	const char *wSuit[]); //dealing doesn't modify the arrays
void deal_Poker(int matrix[2][5]);  //deal the five-ard poker hand

int main(void){
	//initialie deck array
	unsigned int deck[SUITS][FACES] = {0};

	srand(time(NULL)); //seed random-number generator
	shuffle(deck);  //shuffle the deck
	//initialize suit array
	const char *suit[SUITS] = 
		{"Hearts", "Diamond", "Clubs", "Spades"};
	
	//initialize face array
	const char *face[FACES] = 
		{"Ace", "Deuce", "Three", "Four", 
		 "Five", "Six", "Seven", "Eight",
		 "Nine", "Ten", "Jack", "Queen", "King"};
	deal(deck, face, suit); //deal the deck
}

//shuffle cards in the deck
void shuffle(unsigned int wDeck[][FACES]){
	size_t card;
	//for each of the cards, choose slot of deck randomly
	for( card = 1; card <=CARDS; ++card){
	size_t row; //row number
	size_t column; //column number;
	
	//choose new random location until unoccupied slot found
	do{
	  row = rand() % SUITS;
	  column = rand() % FACES;
	  }while(wDeck[row][column] != 0);
	
	//place card number in chosen slot of deck
	wDeck[row][column] = card;
	}
}


//deal cards in deck
void deal (unsigned int wDeck[][FACES], const char *wFace[],
	const char *wSuit[])
{
        //store the face and suit of the card 
        int matrix[2][5]={0}; 
	size_t card, row, column;
	//deal each of the cards
	for(card = 1; card<= 5; ++card){
	  //loop through rows of wDeck
	  for(row = 0;row<SUITS; ++row) {
	    //loop through columns of wDeck for current row
	    for(column = 0; column < FACES; ++column) {
	 	//if slot contains current card, display card
		if(wDeck[row][column] == card) {
		  printf("%5s of %-8s%c", wFace[column], wSuit[row], 
		  	card%2 == 0 ? '\n' : '\t');  //2-colum format
                  matrix[0][card-1] = column;  //cache the faces 
                  matrix[1][card-1] = row;   //cache the suit
		}
	    } 
	  }
	}
        printf("\n");	
        //use the matrix as five-card poker to judge
        deal_Poker(matrix);	  
}

//accoring the hand poker to judge the result
void deal_Poker(int matrix[2][5]){
	printf("\n");
	int i=0; int j=0;
	int counts[FACES] = {0};  //couts the frequency of face
	for(i = 0; i<Hands; i++){
	  counts[matrix[0][i]]++;
	}
	int tag = 0;
	for(i =0; i<FACES; i++){
	  if(counts[i]==2){//a pair
        	for(j =i+1; j<FACES; j++){
	          if(counts[j]==2){  //a pair or two pairs
			 printf("the hand contains two pairs\n");
			 tag++;
		  }		
		}
		if(tag!=1)
		printf("the hand contains one pair\n");
	  }
	  else if(counts[i]==3){ //three of a kind
	    printf("the hand contains three of a kind\n");
	  }
	  else if(counts[i]==4){ //four of a kind
	    printf("the hand contains four of a kind\n");
	   }	
	  else if(counts[i]==1){ //consecutive faces
	    if(counts[i+1]==1&&counts[i+2]==1&&counts[i+3]==1&&counts[i+4]==4)
	    printf("the hands contains a straight\n");
	  }
	}

	printf("\n");
	//judge the suit with matrix[1]
	int countSuit[SUITS] = {0};
	for(i = 0; i<Hands; i++){
	  //printf("%d", matrix[1][i]);
 	  countSuit[matrix[1][i]]++;
	}        	
	for(i = 0 ;i<SUITS; i++){
 	  if(countSuit[i]==5)   //all five cards have the same suit
		printf("the hand contains a flush\n");
	}
}
