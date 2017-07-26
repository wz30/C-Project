/*
name: answer3.c
author: Wei Zhang
date: 6/13/2017 
*/

#include<stdio.h>
#include<string.h>
int main() {
  int a[5000];
  int i=0;
  char str[20];
  char input[20]; 
  FILE *ftp;  //file pointer
  printf("input the word: ");
  gets(input);
  if((ftp = fopen("test.txt","r"))==NULL) {
    puts("File could not be opened");
  }
  else {  //read account
    while(!feof(ftp)) {
      fscanf(ftp,"%d: %s",&a[i++],str);
     // printf("%s\n",str);
      if(strcmp(str,input)==0) //find the word
	printf("find the word's position:%d\n",i-1);
    }
  }
  return 0;
}
