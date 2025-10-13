/**
 * @file mostra.c
 * @author Gustavo Marques (a27962@alunos.ipca.pt)
 * @brief Função que mostra o conteudo do ficheiro passado como parametro
 * @version 0.1
 * @date 2024-04-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char*argv[])
{
    if(argc != 2){ //Numero de argumentos inválidos

        write(STDERR_FILENO,"Uso: mostra ficheiro\n", 22);

        return -1;
    }    

    int fd;

    fd = open(argv[1],O_RDONLY);

    if(fd == -1) // Erro na abertura do ficheiro
    {
        write(STDERR_FILENO,"Erro na abertura do ficheiro\n",29);

        return -1;
    }

    struct stat infFicheiro; //Estrutura que receberá as informações do ficheiro

    stat(argv[1],&infFicheiro);

    char conteudo[infFicheiro.st_size];

    int leitura;

    leitura = read(fd,conteudo,sizeof(conteudo)); //Leitura de todo o conteudo do ficheiro

    write(STDOUT_FILENO,conteudo,leitura); //Escrita na consola de todo o conteudo

    close(fd);

    return 0;
}