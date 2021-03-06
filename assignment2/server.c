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
    if(argc>1){
        printf("I am re-exec server called by execvp()\n");
        //setuid
        //nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
        int s = setuid(65534);
        //printf("setuid result is: %d\n",s );
        printf("Real user id = %d, Effective User id = %d\n",getuid(),geteuid());
        if(s ==-1){
            perror(" Error with setuid() - errno " + errno);
        }
        //printf("\n");
        printf("argument:  %s\n",argv[1]);
        //printf("\n");
        int fd = atoi(argv[1]);
        printf("int fd: %d\n",fd);
        //printf("\n");
        char buffer[1024] = {0}; 
        char *hello = "Hello from server"; 
        //then read from client and print
        int valread = read( fd , buffer, 1024); 
        printf("%s\n",buffer ); 
        send(fd , hello , strlen(hello) , 0 ); 
        printf("Hello message sent from exec\n"); 
    }
else {
    printf("I am original server\n");
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    int pid = fork(); 
	if(pid ==0)
	{
        char fdStr[20];
        //sprintf(fdStr, "%d", new_socket);
        snprintf(fdStr,20, "%d", new_socket);
        printf("fd to string: %s\n", fdStr);
        printf("server calling again name: %s\n",argv[0]);
        printf("Calling server using execvp\n");
        //char *args[]={"./serverChild",fdStr,NULL};
        char *args[]={argv[0],fdStr,NULL};
        execvp(args[0],args);

	}
	else if(pid ==-1)
	{
		printf("Error - unable to fork!\n"); 
	}
	else {
		//printf("Hello from parent!\n"); 
	}
}
    return 0; 
} 
