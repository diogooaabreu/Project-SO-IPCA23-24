/**
 * @file copia.c
 * @author Gustavo Marques (a27962@alunos.ipca.pt)
 * @brief Função que cria um novo ficheiro onde o seu conteudo é a copia do ficheiro passado como parametro
 * @version 0.1
 * @date 2024-04-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "string.h"

int main(int argc, char*argv[])
{
    if(argc != 2){ //Numero de argumentos inválidos

        write(STDERR_FILENO,"Uso: copia ficheiro\n", 21);

        return -1;
    }   
    
    int fdOrigem;

    fdOrigem = open(argv[1],O_RDONLY);

    if(fdOrigem == -1) // Erro ao abrir o ficheiro
    {
        write(STDERR_FILENO,"Erro ao abrir o ficheiro\n",25);
    } 

    struct stat infFicheiro;

    if(stat(argv[1],&infFicheiro) == -1)
    {
        write(STDERR_FILENO,"Erro a obter as informações do ficheiro\n", 40);

        return -1; 
    }

    int fdDestino, leitura;

    char conteudo[infFicheiro.st_size];

    leitura = read(fdOrigem, conteudo, infFicheiro.st_size);

    fdDestino = open(strcat(argv[1],".copia"), O_CREAT | O_WRONLY, S_IRUSR | S_IXUSR | S_IWUSR);

    if(fdDestino == -1) // Erro ao criar o ficheiro
    {
        write(STDERR_FILENO,"Erro ao abrir o ficheiro\n",25);
    } 

    write(fdDestino,conteudo,infFicheiro.st_size);

    close(fdOrigem);
    close(fdDestino);

    return 0;
}