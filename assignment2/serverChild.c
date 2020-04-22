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
     //setuid
        //nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
        int s = setuid(65534);
        //printf("setuid result is: %d\n",s );
    printf("Real user id = %d, Effective User id = %d\n",getuid(),geteuid());
        if(s ==-1){
            perror(" Error with setuid() - errno " + errno);
        }
    //printf("\n");
    printf("argument:  %s",argv[1]);
    //printf("\n");
    int fd = atoi(argv[1]);
    printf("int: %d",fd);
    //printf("\n");
         char buffer[1024] = {0}; 
          char *hello = "Hello from server"; 
        //then read from client and print
        int valread = read( fd , buffer, 1024); 
        printf("%s\n",buffer ); 
        send(fd , hello , strlen(hello) , 0 ); 
        printf("Hello message sent from exec\n"); 
        //printf("Real user id = %d, Effective User id = %d\n",getuid(),geteuid());

     return 0; 
}