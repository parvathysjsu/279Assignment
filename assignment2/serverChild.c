// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <errno.h>
#define PORT 80 

int main(int argc, char const *argv[]) 
{ 
    printf("I am serverchild.c called by execvp() ");
    printf("\n");
    printf("argument:  %s",argv[1]);
    printf("\n");
    int fd = atoi(argv[1]);
    printf("int: %d",fd);
    printf("\n");
     return 0; 
}