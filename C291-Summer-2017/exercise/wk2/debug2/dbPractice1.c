#include<stdio.h>  //miss stdio.h
int values[20];       //intiaialize the size of the values[] to 20 at first 
double  average(int, double); 
int sum(int); 

int main(void) 
{   
	//using namespace std;  //useless   
    printf( "Debugging Practice 1 - Quiz 3, Q3\n\n");
	printf( "Please enter the number of values to be used: ");
	int n;   //miss n
	scanf("%d", &n);
	printf( "Please enter %d values: ",n);
	int i;   //miss i
	for (i=0; i<n; i++) 
        scanf("%d", &values[i]);   //miss &
	
    int sigma = sum(n);
	double avg = average(n, sigma);   //change avg to double accoring the logic and the return argument of the averge(fun)
	printf( "The average of %d / %d is: %f\n", sigma, n , avg );   //change the last %d to %f
    return 0;
}

double average(int num_scores,  double sum)  //mistaken pass by variable
{
	return sum /(double) num_scores;   //cast the num_scores to double
}

int sum(int num_scores)  
{
	int sum=0,i;   //initialize sum
    for (i =0; i<num_scores; i++)
	    sum += values[i];  //+= 
    return sum;
}
