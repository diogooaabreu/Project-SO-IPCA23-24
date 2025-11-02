# 💻 Trabalho Prático — Gestão de Processos e de Ficheiros

Este repositório contém a **resolução completa** do **Trabalho Prático** da unidade curricular de **Sistemas Operativos**, cujo objetivo é aplicar os conceitos de **gestão de processos**, **gestão de ficheiros** e **interpretação de comandos em C (Linux)**.

---

## 📘 Enunciado Resumido

O trabalho prático divide-se em **três partes principais**, avaliando diferentes competências no uso de **chamadas ao sistema (syscalls)**, **manipulação de processos** e **configuração de sistemas de ficheiros**.

---

## ⚙️ Parte 1 — Manipulação de Ficheiros (10,5 valores)

Implementação de um conjunto de **comandos personalizados**, utilizando apenas **chamadas ao sistema (system calls)** do Linux.  
> ⚠️ Não é permitida a utilização de `system()`, `fopen`, `fread`, `fwrite`, `fseek`, etc.

### 🔧 Comandos Implementados

| Comando | Descrição | Funções do sistema utilizadas |
|----------|------------|-------------------------------|
| `mostra ficheiro` | Apresenta no ecrã o conteúdo completo de um ficheiro. | `open`, `read`, `write`, `close` |
| `copia ficheiro` | Cria uma cópia de um ficheiro com o nome `ficheiro.copia`. | `open`, `read`, `write`, `close` |
| `acrescenta origem destino` | Acrescenta o conteúdo do ficheiro origem no final do destino. | `open`, `read`, `write`, `lseek`, `close` |
| `conta ficheiro` | Conta o número de linhas num ficheiro. | `open`, `read`, `close` |
| `apaga ficheiro` | Remove o ficheiro indicado. | `unlink` |
| `informa ficheiro` | Mostra informações do ficheiro (tipo, inode, dono, datas, etc.). | `stat`, `getpwuid`, `localtime` |
| `lista [diretoria]` | Lista todos os ficheiros e diretórios existentes. | `opendir`, `readdir`, `closedir` |

Cada comando é executado como um **programa independente**, que pode ser chamado pelo **interpretador** desenvolvido na Parte 2.

---

## 💬 Parte 2 — Interpretador de Linha de Comandos (4 valores)

Implementação de um **interpretador de comandos** personalizado que substitui o **Bash shell**.

### 🧠 Funcionamento:
- Mostra o símbolo `%` à espera de um novo comando;
- Lê a linha introduzida pelo utilizador;
- Cria um novo **processo filho** com `fork()` e **executa o comando** com `execve()` ou `exec()`;
- O processo pai espera a conclusão com `wait()`;
- Exibe o **código de terminação** (sucesso ou erro);
- Termina apenas quando o utilizador escreve o comando `termina`.

### 🧩 Exemplo de execução:
$ ./interpretador
% lista /home/user/Desktop
<conteúdo da diretoria>
Terminou comando lista com código 0
% apaga /home/user/Desktop/file.txt
Terminou comando apaga com código 1
% termina
$

---

## 💽 Parte 3A — Gestão de Sistemas de Ficheiros (3,5 valores)

Configuração prática de volumes e sistemas de ficheiros num **ambiente virtual Linux**.

### Passos principais:
1. Adicionar um **disco de 10 GB** (alocado dinamicamente);
2. Criar uma **partição** e dois **volumes lógicos** de 5 GB;
3. Criar sistemas de ficheiros **ext4** e **ext3** em cada volume;
4. Montar permanentemente em `/mnt/ext4` e `/mnt/ext3`;
5. Criar ficheiro `<números-alunos>.txt` com permissões específicas:
   - Dono: leitura e escrita;
   - Grupo: sem permissões;
   - Outros: leitura.

---

## 🧾 Parte 3B — Análise de Sistemas de Ficheiros (2 valores)

Análise do ficheiro `fs.img`, respondendo às seguintes questões:

- Identificação dos **blocos de início dos ficheiros regulares**;
- Leitura e exibição do **conteúdo do ficheiro `ipca.txt`**.

---

## 🧰 Chamadas ao Sistema Utilizadas

### Gestão de Ficheiros
- `open`, `read`, `write`, `close`
- `dup`, `dup2`, `pipe`
- `stat`
- `opendir`, `readdir`, `closedir`

### Gestão de Processos
- `fork`
- `execve` / `exec`
- `wait`

---

## 📂 Estrutura do Repositório

Gestao_Processos_Ficheiros/
│
├── comandos/
│ ├── mostra.c
│ ├── copia.c
│ ├── acrescenta.c
│ ├── conta.c
│ ├── apaga.c
│ ├── informa.c
│ └── lista.c
│
├── interpretador/
│ └── interpretador.c
│
├── parte3/
│ ├── configuracao_dispositivos.md
│ ├── analise_fs.md
│ └── screenshots/
│
├── relatorio.pdf
└── README.md


---

## 🧑‍💻 Grupo de Trabalho
| Nome | Número |
|------|---------|
| Bruno Dantas | 27958 |
| Diogo Abreu | 27975 |
| Gustavo Marques | 27962 |
| Igor Costa | 27977 |
| Paulo Gonçalves | 27966 |

> No relatório (`relatorio.pdf`) está indicado o contributo de cada elemento em cada alínea.

---

## 🧠 Objetivo Geral

Este trabalho visa consolidar os conhecimentos sobre:
- Manipulação de ficheiros e diretórios via **system calls**;
- Criação e gestão de **processos** com **fork/exec/wait**;
- Estrutura e gestão de **sistemas de ficheiros Linux (ext3/ext4)**;
- Interpretação de comandos e **execução em ambiente controlado**.

---

## 🏫 Instituição

**Instituto Politécnico do Cávado e do Ave (IPCA)**  
Curso: **Engenharia de Sistemas Informáticos**  
Unidade Curricular: **Sistemas Operativos**

---
