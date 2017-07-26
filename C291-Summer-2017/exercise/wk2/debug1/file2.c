/*Debugging quiz - File No: 2 */
/* The program should correctly print the stored variable values */

#include<stdio.h>  //miss #

int main(){
	int new_default = 3.14,b = 9;  //not create variable with the start of number or keyword
	char alphabet = 'd';
	printf("%Lf\n",&new_default);  //miss ;
	printf("%u\n",&b);
	printf("The ASCII value of character 'd' is : %d\n",alphabet); //should be alaphabet
	return 0;
}
