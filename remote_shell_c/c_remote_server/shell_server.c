#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 80

char* func(int sockfd) {
    char **vector;
    char buff[MAX];
    bzero(buff, MAX);
    TCP_Read_String(sockfd, buff, MAX);
    if (strcmp(buff, "exit") == 0) {
        printf("Saliendo de la terminal remota\n");
        return buff;
    } else {
        vector = de_cadena_a_vector(buff);
        execvp(vector[0], vector);
        perror("execvp");  // Print an error message if execvp fails
        exit(EXIT_FAILURE);  // Terminate the child process if execvp fails
    }
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
  char* command;
	// Function for chatting between client and server 
	//configurar bucle del servidor
  while(1){
    pid_t pid;
    if (connfd < 0) {
      break;
    } else {
      pid = fork();
    }

    if (pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
      dup2(connfd, STDOUT_FILENO);
      command = func(connfd);
      dup2(STDOUT_FILENO, STDOUT_FILENO);
      // close(connfd);  // Close the file descriptor in the child process
      break;
    } else {
      if (strcmp(command, "exit") == 0) {
        printf("Saliendo de la terminal remota\n");
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
          printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
          printf("Child process terminated abnormally\n");
        }
        close(connfd);
        connfd = -1;
        break;
      }
    }
  }
  close(connfd);
	close(socket); 
  return 0;
}
    

