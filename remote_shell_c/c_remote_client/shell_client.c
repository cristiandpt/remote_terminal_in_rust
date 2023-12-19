#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include "leercadena.h"
#include "tcp.h"

int main(int argc, char* argv[]) {

  printf("\033[1;36m"); 
  printf("*****************************************\n");
  printf("* Bienvenido a la Terminal Remota       *\n");
  printf("* Para salir escriba 'exit'             *\n");
  printf("*****************************************\n");
  printf("\033[0m");

  char comando[BUFSIZ];
  char salida[BUFSIZ];
  // bzero(comando);
  char **comando_vector;
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

  while(1){
    printf("Ingrese un comando: ");
    leer_de_teclado(BUFSIZ, comando);
    TCP_Write_String(sockfd, comando);
    // printf(comando);
    //printf("Comando ingresado: %s\n",  comando);
    //puts(comando)
    if (strcmp(comando,"exit") == 0) {
      printf("\033[1;36m");
      printf("Saliendo de la terminal remota\n");
      printf("\033[0m"); 
      break;
    }
    // dup2(STDOUT_FILENO, sockfd);
    TCP_Read_String(sockfd, salida, BUFSIZ);
    printf(salida);
    // dup2(STDOUT_FILENO, STDOUT_FILENO);
  }
  return 0;
}