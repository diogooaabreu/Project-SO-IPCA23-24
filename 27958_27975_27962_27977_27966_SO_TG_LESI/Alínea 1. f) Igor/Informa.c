/*
 * Informa.c
 * Comando para obter informações de um ficheiro
 * Igor a27977@alunos.ipca.pt
 */ 

#define _GNU_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER 1024
#define DATEBUFFER 24
#define USERBUFFER 32

//Função para obter o tamanho de uma string
int GetLenght(char *string){
	int lenght = 0;
	while (string[lenght] != '\0'){
		lenght++;
	}
	return lenght;
}

//Função para converter valores int para string
void IntToString(char *str, int num) {
    int i = 0;
    int temp = num;
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (temp != 0) {
        temp /= 10;
        i++;
    }
    str[i] = '\0';
    while (num != 0) {
        str[--i] = '0' + (num % 10);
        num /= 10;
    }
}

//Função para obter o dono do ficheiro
char* GetOwner(int uid){
	struct passwd *pw = getpwuid(uid);
	if (pw == NULL) {
		write(STDERR_FILENO, "Erro: Não foi possível obter o dono do ficheiro\n", 51);
		return NULL;
	}
	
	return pw->pw_name;
}

int main(int argc, char *argv[ ] ){
	//Valida os argumentos input do utilizador
	if(argc != 2 || argv[1] == NULL){
		write(STDERR_FILENO, "Erro: Argumentos inválidos\n", 29);
	        return -1;	
	}

	int fileHandler;
	struct stat statHandler;
	
	//Verifica se o ficheiro existe
	fileHandler = open(argv[1], O_RDONLY);
	if(fileHandler == -1){
		write(STDERR_FILENO, "Erro: Ficheiro não existe ou inválido\n", 41);
		return -1;
	}
	close(fileHandler);
	
	//Carrega as informações do ficheiro na estrutura stat e verifica se funcionou corretamente
	if (stat(argv[1], &statHandler) == -1) {
        	write(STDERR_FILENO, "Erro: Não foi possível obter as informações do ficheiro\n", 61);
        	return -1;
    	}
	//Indica o tipo de ficheiro
	write(STDOUT_FILENO, "Tipo de ficheiro: ", 19);
	switch (statHandler.st_mode & S_IFMT) {
    		case S_IFBLK:  write(STDOUT_FILENO, "Bloco de dispositivos\n", 23);            break;
    		case S_IFCHR:  write(STDOUT_FILENO, "Bloco de caracteres\n", 21);              break;
    		case S_IFDIR:  write(STDOUT_FILENO, "Diretório\n", 12);                        break;
    		case S_IFIFO:  write(STDOUT_FILENO, "Tubo/FIFO\n", 11);                        break;
    		case S_IFLNK:  write(STDOUT_FILENO, "Link simbólico\n", 17);                   break;
    		case S_IFREG:  write(STDOUT_FILENO, "Ficheiro regular\n", 18);                 break;
    		case S_IFSOCK: write(STDOUT_FILENO, "Socket\n", 8);                            break;
    		default:       write(STDOUT_FILENO, "Desconhecido\n", 14);                     break;
    }
	
	//I-node a qual o ficheiro está localizado
	char iNodeString[20];
	IntToString(iNodeString, statHandler.st_ino);
	write(STDOUT_FILENO, "Número I-node: ", 17);
	write(STDOUT_FILENO, iNodeString, GetLenght(iNodeString));
	write(STDOUT_FILENO, "\n", 1);

	//Dono do ficheiro
	int uid = statHandler.st_uid;
	char ubuf[USERBUFFER];

	write(STDOUT_FILENO, "Dono do ficheiro: ", 18);
	write(STDOUT_FILENO, GetOwner(uid), GetLenght(GetOwner(uid)));
	write(STDOUT_FILENO, "\n", 1);

	//Datas de criação, leitura e modificação
	char buf[DATEBUFFER];

	struct statx stx;
	//Chama a função statx para obter a data de criação do ficheiro
	if (statx(AT_FDCWD, argv[1], AT_STATX_SYNC_AS_STAT, STATX_BTIME, &stx) == -1) {
        write(STDERR_FILENO, "Erro: Falha ao extrair a data de criação do ficheiro\n", 55);
        return 1;
    }
	//Converte a data de criação para o formato time_t e depois para o formato tm
	time_t bornTime = (time_t)stx.stx_btime.tv_sec;
	struct tm *bornTimeTm = localtime(&bornTime);
	if (bornTimeTm == NULL) {
		write(STDERR_FILENO, "Erro: Falha ao converter a data de criação do ficheiro\n", 57);
		return 1;
	}
	write(STDOUT_FILENO, "Data de criação: ", 20);
	strftime(buf, DATEBUFFER, "%H:%M:%S %d-%m-%Y", bornTimeTm);
	write(STDOUT_FILENO, buf, GetLenght(buf));
	write(STDOUT_FILENO, "\n", 1);

	write(STDOUT_FILENO, "Data de leitura: ", 18);
	strftime(buf, DATEBUFFER, "%H:%M:%S %d-%m-%Y", localtime(&statHandler.st_atime));
	write(STDOUT_FILENO, buf, GetLenght(buf));
	write(STDOUT_FILENO, "\n", 1);

	write(STDOUT_FILENO, "Data de modificação: ", 24);
	strftime(buf, DATEBUFFER, "%H:%M:%S %d-%m-%Y", localtime(&statHandler.st_mtime));
	write(STDOUT_FILENO, buf, GetLenght(buf));
	write(STDOUT_FILENO, "\n", 1);
	return 0;
}
	
