#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char comando[256];  // Cria um array para armazenar o comando do usu�rio
    pid_t pid_filho;  // Declara uma vari�vel para armazenar o ID do processo filho
    int status;  // Vari�vel para armazenar o status retornado pelo processo filho

    while (1) {  // Loop infinito para manter o shell rodando
        printf("shell> ");  // Exibe o prompt do shell
        fgets(comando, 256, stdin);  // L� o comando do usu�rio

        // Remove o newline do final do comando
        comando[strcspn(comando, "\n")] = 0;

        if (strcmp(comando, "exit") == 0) {  // Se o comando for "exit", encerra o shell
            exit(0);
        }

        pid_filho = fork();  // Cria um novo processo

        if (pid_filho < 0) {  // Verifica se houve um erro ao criar o processo
            perror("Erro no fork");
            exit(1);
        }

        if (pid_filho == 0) {  // C�digo executado pelo processo filho
            char *args[] = {"/bin/sh", "-c", comando, NULL};  // Prepara os argumentos para exec
            execvp(args[0], args);  // Executa o comando
            perror("Erro no exec");  // exec s� retorna em caso de erro
            exit(1);
        } else {  // C�digo executado pelo processo pai
            waitpid(pid_filho, &status, 0);  // Aguarda o processo filho terminar
        }
    }

    return 0;
}
