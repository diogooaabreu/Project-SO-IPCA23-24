#include <unistd.h>      // para chamadas de sistema e constantes
#include <syscall.h>     // para chamar funções do sistema diretamente

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos é válido
    if (argc != 2) {
        // Escreve a mensagem de uso no stderr (descritor 2)
        syscall(SYS_write, 2, "Uso: apaga <nome_do_ficheiro>\n", 29);
        return 1;  // Retorna 1 para indicar um erro
    }

    // Usa a chamada de sistema unlink para remover o arquivo
    if (syscall(SYS_unlink, argv[1]) == -1) {
        // Se houver um erro ao apagar, escreve a mensagem de erro no stderr
        syscall(SYS_write, 2, "Erro ao apagar o ficheiro.\n", 28);
        return 1;  // Retorna 1 para indicar um erro
    }

    return 0;  // Retorna 0 para indicar sucesso
}
