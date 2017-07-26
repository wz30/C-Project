/*
name: hello.c
author: Wei Zhang
date: 5/16/2017
explain: print Hello, world every 3 seconds
*/

#include<stdio.h>
#include<unistd.h>

int main(){
  while(1){
  printf("Hello, world\n");
  sleep(3);
  }
  return 0;
}
