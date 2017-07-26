/*
name: answer1.c
author: Wei Zhang
date: 6/13/2017 
*/

#include<stdio.h>

//clean quote 
//return string
char *clean_quotes(char *str, char *dest) {
  memset(dest, '\0', sizeof(dest));
  strcpy(dest, str);
  int i = 0; 
  int k = 0; 
  for(; str[i]!='\0'; i++) {
    if(str[i]!='"' && str[i]!='\'')
      dest[k++] = str[i];
  }
  dest[k] = '\0';
//  printf("%s\n",str);
//  printf("%s\n",dest);
  return dest;
}

int main() {
  char dest[50];  //string dest
  char *str = (char *)malloc(50);  //string str
  gets(str); //input string
//  printf("'\n",str);

  str = clean_quotes(str,dest);  // clean quotes function
  printf("%s\n",str);  //print the result after function
  return 0;
}
