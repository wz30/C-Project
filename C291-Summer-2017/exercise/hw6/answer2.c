/*
name: answer2.c
author: Wei Zhang
date: 6/13/2017 
*/

#include<stdio.h>

//write the file
void write_file(FILE *cfPtr,int number[],char **str) {
  int i,j,k,l,m,n,o;
  int count = 0;
  for(i = 0; i<3; i++) {
    for(j = 0; j<3; j++) 
      for(k = 0; k<3; k++) 
        for(l = 0; l<3; l++) 
          for(m = 0; m<3; m++) 
	    for(n = 0; n<3; n++) 
	      for(o = 0; o<3; o++) 
	fprintf(cfPtr,"%d: %c%c%c%c%c%c%c\n",count++,str[number[0]][i],str[number[1]][j],str[number[2]][k]
						,str[number[3]][l],str[number[4]][m],str[number[5]][n],str[number[6]][o]);
   }
  
}

int main() {
  char *str[8] = {"ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"};
//  printf("%c",str[0][1]);    
  int i;
  int number[7];
  char str_num[7];
  FILE *cfPtr; //cfPtr
  int count = 1;
  if((cfPtr = fopen("test.txt","w+")) == NULL) {
     puts("File could not be opened");
  }
  else {//use the file pointer
    for(i = 0; i<7 ; i++) {
      scanf("%c",&str_num[i]);
      if(str_num[i]=='0'||str_num[i]=='1')
         {printf("no 0 or 1\n");i--;continue;}
      number[i] = str_num[i]-50;
//      printf("%d\n",number[i]);
    }
    write_file(cfPtr,number,str);
  }//else
  
  fclose(cfPtr); //close the file
  return 0;
}
