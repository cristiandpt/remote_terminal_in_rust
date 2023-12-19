#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include "leercadena.h"
#include "tcp.h"

int kbhit(void) {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int main(int argc, char* argv[]) {

  //char input[1024];
  //int index = 0;
  //char indicators[] = {'/', '-', '|', '\\'};
  //int indicatorIndex = 0;

 

  char comando[BUFSIZ];
  char **comando_vector;
  int i;
  char *host;
  int sockfd, port;  

   if ( argc != 3 ) {
    printf("Uso: %s <host> <puerto>\n", argv[0]);
    return 1;
  }

  printf("\033[1;36m"); 
  printf("*****************************************\n");
  printf("* Bienvenido a la Terminal Remota       *\n");
  printf("* Para salir escriba 'exit'             *\n");
  printf("*****************************************\n");
  printf("\033[0m"); 
  host = argv[1];
  port = atoi(argv[2]);
	sockfd = TCP_Open(Get_IP(host), port);

 
  while(1){
    
    printf("Ingrese un comando: ");
    leer_de_teclado(BUFSIZ, comando);
    TCP_Write_String(sockfd, comando); 
    //printf("Comando ingresado: %s\n",  comando);
    //puts(comando)
    if (strcmp(comando,"exit") == 0) {
      printf("\033[1;36m");
      printf("Saliendo de la terminal remota\n");
      printf("\033[0m"); 
      break;
    }

  }



 //fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

 //while (1) {
 //    if (kbhit()) {
 //        char ch = getchar();
 //        if (ch == '\n') {
 //            input[index] = '\0';
 //            printf("\nUsted escribió: %s\n", input);
 //            index = 0;
 //            memset(input, 0, sizeof(input));
 //        } else if (ch != EOF) {
 //            input[index++] = ch;
 //        }
 //    }

 //    // Imprimir el indicador
 //    printf("\rIngrese un comando:%c", indicators[indicatorIndex]);
 //    fflush(stdout);
 //    indicatorIndex = (indicatorIndex + 1) % 4;

 //    // Pausa antes de la siguiente actualización
 //    usleep(200000); // 200 milisegundos
 //}

  return 0;
}