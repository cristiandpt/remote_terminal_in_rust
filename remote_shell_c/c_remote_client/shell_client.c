#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include "leercadena.h"
#include "tcp.h"
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  printf("\033[1;36m"); 
  printf("*****************************************\n");
  printf("* Bienvenido a la Terminal Remota       *\n");
  printf("* Para salir escriba 'exit'             *\n");
  printf("*****************************************\n");
  printf("\033[0m");

  char comando[BUFSIZ];
  char salida[BUFSIZ];
  int i;
  char *host;
  int sockfd, port;

  if ( argc != 3 ) {
    printf("Uso: %s <host> <puerto>\n", argv[0]);
    return 1;
  }

  host = argv[1];
  port = atoi(argv[2]);
  sockfd = TCP_Open(Get_IP(host), port);

  int quiebre = 1;
  while(1){
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      memset(comando, '\0', sizeof(comando));
      printf("Ingrese un comando: ");
      leer_de_teclado(BUFSIZ, comando);
      TCP_Write_String(sockfd, comando);
      if (strcmp(comando,"exit") == 0) {
        printf("\033[1;36m");
        printf("Saliendo de la terminal remota\n");
        printf("\033[0m");
        quiebre = 0;
        exit(0);
      }
      exit(0);
    } else {
      if (quiebre == 0) {
        exit(0);
      }
      int status;
      waitpid(pid, &status, 0);
      if (WIFEXITED(status)) { 
        memset(salida, '\0', sizeof(salida));
        TCP_Read_String(sockfd, salida, BUFSIZ);
        memset(salida, '\0', sizeof(salida));
        TCP_Read_String(sockfd, salida, BUFSIZ);
        printf(salida);
        // printf("Child process exited with status: %d\n", WEXITSTATUS(status));
      } else {
        // printf("Child process terminated abnormally\n");
      }
    }
  }  
  return 0;
}