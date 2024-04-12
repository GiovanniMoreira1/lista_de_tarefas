#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, exportar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[5](tarefas, &pos);
    if(erro != OK){
        pos = 0;
        if (erro == ABRIR) {
            printf("ERRO - Não foi possível abrir o arquivo.\n");
        } else if (erro == FECHAR) {
            printf("ERRO - Não foi possível fechar o arquivo.\n");
        } else if (erro == LER) {
            printf("ERRO - Não foi possível ler o  arquivo.\n");
        }
    }

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        opcao--;
        if(opcao > 3)
            printf("Opcao invalida\n");
        else if(opcao >= 0){
            ERROS ERRO = fs[opcao](tarefas, &pos);
    
            if (ERRO == MAX_TAREFA) {
                printf("ERRO - Máximo de tarefas atingido.\n");
            } else if (ERRO == CRIAR) {
                printf("ERRO - Não foi possível criar o arquivo.\n");
            } else if (ERRO == SEM_TAREFAS) {
                printf("ERRO - Não há nenhuma tarefa escrita.\n");
            } else if (ERRO == NAO_ENCONTRADO) {
                printf("ERRO - Posição não encontrada.\n");
            } else if (ERRO == ABRIR) {
                printf("ERRO - Não foi possível abrir o arquivo.\n");
            } else if (ERRO == FECHAR) {
                printf("ERRO - Não foi possível fechar o arquivo.\n");
            } else if (ERRO == ESCREVER) {
                printf("ERRO - Não foi possível escrever em seu arquivo.\n");
            } else if (ERRO == LER) {
                printf("ERRO - Não foi possível ler o seu arquivo.\n");
            } else if (ERRO == CATEGORIA) {
                printf("ERRO - Categoria não encontrada.\n");
            }
          
        

    }
    else
        printf("Sair...\n");

    } while(opcao >= 0);

    fs[4](tarefas, &pos);
}
