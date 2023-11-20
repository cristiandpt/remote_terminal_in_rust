FROM gcc:4.9
COPY . /usr/src/server_shell
RUN ["mkdir", "-R", "/usr/src/server_shell/lib"]
WORKDIR /usr/src/server_shell
RUN gcc -o server_shell main.c
CMD ["./server_shell"]