#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"
#include "leercadena.h"
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 80

void func(int sockfd, char buff[MAX]) {
  char **vector;
  TCP_Read_String(sockfd, buff, MAX);
  if (strcmp(buff, "exit") == 0) {
    exit(0);
  } else {
    vector = de_cadena_a_vector(buff);
    execvp(vector[0], vector);
    perror("execvp");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char* argv[]) {

  printf("\033[1;31m");
  printf("*****************************************\n");
  printf("* Bienvenido a la Terminal Remota       *\n");
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
  dup2(connfd, STDOUT_FILENO);
  dup2(connfd, STDERR_FILENO);

  char buff[MAX];

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
      memset(buff, '\0', sizeof(buff));
      func(connfd, buff);
      break;
    } else {
      int status;
      waitpid(pid, &status, 0);
      if (WIFEXITED(status)) {
        printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        memset(buff, '\0', sizeof(buff));
      } else {
        printf("Saliendo de la terminal remota\n");
        // printf("Child process terminated abnormally\n");
        close(connfd);
	      connfd = -1;
      }
    }
  }
  close(connfd);
	close(socket); 
  return 0;
}