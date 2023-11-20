all: basic_server shell_server file_server archivo leercadena



basic_server: tcp.o
	gcc -o basic_server basic_server.c tcp.o


file_server: tcp.o
	gcc -o file_server file_server.c tcp.o

tcp.o:
	gcc -c tcp.c

# ---
# Para compilar la prueba de leercadena
#
leercadena: leercadena.o 
	gcc -o leercadena_main leercadena_main.c leercadena.o

leercadena.o:
	gcc -c leercadena.c

# ---

# ---
# Para compilar archivo_main
#
archivo: archivo.o
	gcc -o archivo_main archivo_main.c archivo.o

archivo.o:
	gcc -c archivo.c

# ---



# ---
# Para compilar el shell_server
#

shell_server: leercadena.o archivo.o tcp.o
	gcc -o shell_server shell_server.c leercadena.o archivo.o tcp.o


clean:
	rm -f tcp.o  basic_server  file_server leercadena_main leercadena.o  shell_server archivo_main archivo.o
