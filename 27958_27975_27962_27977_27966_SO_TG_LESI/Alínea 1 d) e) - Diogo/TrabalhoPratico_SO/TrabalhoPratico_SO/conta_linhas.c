#include <unistd.h>  // Biblioteca para as funções de sistema, como write e read
#include <fcntl.h>   // Biblioteca para as constantes de controle de arquivo, como O_RDONLY

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos é diferente de 2 (nome do programa + nome do arquivo)
    if (argc != 2) {
        write(2, "Uso: conta_linhas <nome_do_ficheiro>\n", 36);  // Escreve mensagem de uso no stderr
        return 1;  // Retorna código de erro 1
    }

    // Abre o arquivo fornecido como argumento apenas para leitura
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {  // Verifica se houve erro ao abrir o arquivo
        write(2, "Erro: O ficheiro não existe.\n", 29);  // Escreve mensagem de erro no stderr
        return 1;  // Retorna código de erro 1
    }

    int num_linhas = 0;  // Variável para contar o número de linhas
    char c;  // Variável para armazenar cada caractere lido do arquivo

    // Lê o arquivo caractere por caractere até o final
    while (read(fd, &c, 1)) {
        if (c == '\n') {  // Verifica se o caractere lido é uma nova linha
            num_linhas++;  // Incrementa o contador de linhas
        }
    }
    
    close(fd);  // Fecha o arquivo após a leitura

    // Formata uma string com o nome do arquivo e o número de linhas
    char buffer[100];
    int len = snprintf(buffer, sizeof(buffer), "O ficheiro %s tem %d linhas.\n", argv[1], num_linhas);

    // Escreve a string formatada no stdout
    write(1, buffer, len);

    return 0;  // Retorna 0 para indicar sucesso
}
