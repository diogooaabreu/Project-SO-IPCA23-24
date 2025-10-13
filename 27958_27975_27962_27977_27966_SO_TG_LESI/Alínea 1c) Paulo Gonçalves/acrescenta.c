#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void error(char *msg) {
    write(STDERR_FILENO, msg, strlen(msg));
    exit(1);
}

int main(int argc, char *argv[]) {
    // verifica o numero de argumentos
    if (argc != 3) {
        error("Uso: acrescenta origem destino");
    }

    
    int origem_fd = open(argv[1], O_RDONLY);
    if (origem_fd == -1) { // verifica se abriu
        error("Erro ao abrir o ficheiro de origem");
    }

    int destino_fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (destino_fd == -1) { // verifica se abriu
        error("Erro ao abrir ou criar o ficheiro de destino");
    }

    // Leitura e escrita
    char buffer[4096];
    ssize_t bytes_lidos, bytes_escritos;

    while ((bytes_lidos = read(origem_fd, buffer, sizeof(buffer))) > 0) {
        bytes_escritos = write(destino_fd, buffer, bytes_lidos);
        if (bytes_escritos != bytes_lidos) {
            error("Erro ao escrever no ficheiro de destino");
        }
    }

    // Verifica erros de leitura
    if (bytes_lidos == -1) {
        error("Erro ao ler o ficheiro de origem");
    }
    // Fecha os ficheiros
    if (close(origem_fd) == -1 || close(destino_fd) == -1) {
        error("Erro ao fechar os ficheiros");
    }

    return 0;
}
