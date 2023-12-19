#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"
#include <sys/types.h>

#define MAX 80

int func(int sockfd) 
{ char **vector;
	char buff[MAX]; 
	bzero(buff,MAX);
	TCP_Read_String(sockfd, buff, MAX); 
	printf("Se leyo %s\n",buff);
  if (strcmp(buff, "exit\x0") == 0) {
      return -1;  
  }
  vector = de_cadena_a_vector(buff);
  int i = 0;
  while (vector[i]) 
    printf("%s\n",vector[i++]);
  execvp(vector[0],vector);
  return 1;

} 

int main(int argc, char* argv[]) {

  printf("\033[1;31m");
  printf("*****************************************\n");
  printf("* Bienvenido a la Terminal Remota       *\n");
  printf("* Para salir escriba 'exit'             *\n");
  printf("*****************************************\n");
  printf("\033[0m"); 

  int socket, connfd;  
	int puerto;

	if (argc != 2) {
		printf("Uso: %s <puerto>\n",argv[0]);
		return 1;
	}
	
	puerto = atoi(argv[1]);

	socket = TCP_Server_Open(puerto);
	
connfd = TCP_Accept(socket);
	// Function for chatting between client and server 
	//configurar bucle del servidor
  while(1){
    
    if (connfd < 0) {
      printf("\033[1;36m");
      printf("Error al aceptar la conexion\n");
      printf("\033[0m"); 
      continue;
    }
    pid_t pid = fork();
        if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Redirect standard output to the socket
          if(func(connfd)<0){
            printf("\033[1;36m");
            printf("Saliendo de la terminal remota\n");
            printf("\033[0m"); 
            break;
      //   if (dup2(connfd, STDOUT_FILENO) == -1) {
      //       perror("dup2"); 
         }
    }
   

  }
 close(connfd);
	// After chatting close the socket 
	close(socket); 
  return 0;
}

    // Fork to create a child process
    

