INCLUDE = -I./lib
CFLAGS = -std=c11

all: clean tcp.o leercadena.o archivo leercadena basic_server shell_server file_server 

basic_server: tcp.o
	gcc $(CFLAGS) $(INCLUDE) -o basic_server basic_server.c tcp.o


file_server: tcp.o
	gcc $(CFLAGS) $(INCLUDE) -o file_server file_server.c tcp.o

tcp.o:
	gcc $(CFLAGS) $(INCLUDE) -c ./lib/tcp.c

# ---
# Para compilar la prueba de leercadena
#
leercadena: leercadena.o 
	gcc $(CFLAGS) $(INCLUDE) -o leercadena_main ./lib/leercadena_main.c leercadena.o

leercadena.o:
	gcc $(CFLAGS) $(INCLUDE) -c ./lib/leercadena.c

# ---

# ---
# Para compilar archivo_main
#
archivo: archivo.o
	gcc $(CFLAGS) $(INCLUDE) -o archivo_main ./lib/archivo_main.c archivo.o

archivo.o:
	gcc $(CFLAGS) $(INCLUDE) -c ./lib/archivo.c

# ---



# ---
# Para compilar el shell_server
#

shell_server: leercadena.o archivo.o tcp.o
	gcc $(CFLAGS) $(INCLUDE) -o shell_server shell_server.c leercadena.o archivo.o tcp.o


clean:
	rm -f tcp.o  basic_server  file_server leercadena_main leercadena.o  shell_server archivo_main archivo.o
