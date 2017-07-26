#include<stdio.h>   //miss the include
int main(void) 
{   
    int size=5, Matrix1[size][size];
	int i,j;   //definiation firstly  
	for (i=0; i<size; i++) //the size of the row is size==5 
 	    for (j=0; j<size; j++)   //the size of the column is 5 
            Matrix1[i][j]=i+j;
	display(Matrix1,5);   //  shoud pass Matrix 
    return 0;    //return int
}

void display(int Matrix1[][5],int size)   //the second bracket should have some numbers
{   
    //int size = 6;    //out of the boundry
	int i,j;    //def firstly
	for (i=0; i<size; i++) {
 	    for (j=0; j<size; j++) 
            printf("%d ,", Matrix1[i][j]);
        printf("\n");
        }
    return;
}
