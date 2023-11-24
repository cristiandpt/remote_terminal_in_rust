INCLUDE = -I./lib
CFLAGS = -std=c11

all: basic_client shell_client file_client archivo leercadena

basic_client: tcp.o
	gcc $(CFLAGS) $(INCLUDE) -o basic_client basic_client.c tcp.o


file_client: tcp.o
	gcc $(CFLAGS) $(INCLUDE) -o file_client file_client.c tcp.o

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
# Para compilar el shell_client
#

shell_client: leercadena.o archivo.o tcp.o
	gcc $(CFLAGS) $(INCLUDE) -o shell_client shell_client.c leercadena.o archivo.o tcp.o

clean:
	rm -f tcp.o basic_client file_client  leercadena_main leercadena.o shell_client archivo_main archivo.o
