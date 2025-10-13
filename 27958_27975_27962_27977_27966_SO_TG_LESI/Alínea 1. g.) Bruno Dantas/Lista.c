#include <stdio.h>
#include <dirent.h>
#include <string.h>

void listDirectory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // Abre o diretório
    dir = opendir(path);
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }

    // Lê cada entrada do diretório
    while ((entry = readdir(dir)) != NULL) {
        // Ignora as entradas "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Verifica se é um diretório
        if (entry->d_type == DT_DIR) {
            printf("%s (diretório)\n", entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *directory;

    // Verifica se um diretório foi especificado
    if (argc == 1) {
        directory = "."; // Diretório atual
    } else if (argc == 2) {
        directory = argv[1]; // Diretório especificado
    } else {
        printf("Uso: %s [directoria]\n", argv[0]);
        return 1;
    }

    // Lista o diretório
    listDirectory(directory);

    return 0;
}
