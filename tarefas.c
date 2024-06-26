#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
if(*pos >= TOTAL)
return MAX_TAREFA;

    do {
  printf("Entre com a prioridade |1 - 10|: ");
  scanf("%d", &tarefas[*pos].prioridade);
  } while (tarefas[*pos].prioridade > 10 || tarefas[*pos].prioridade < 1);
  
    clearBuffer();
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, T_CATEGORIA, stdin);
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';
    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, T_DESCRICAO, stdin);
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';

*pos = *pos + 1;

return OK;
}
ERROS deletar(Tarefa tarefas[], int *pos){
// teste se existem tarefas
if(*pos == 0)
return SEM_TAREFAS;

// verifica se a tarefa escolhida existe
int pos_deletar;
printf("Entre com a posicao da tarefa a ser deletada: ");
scanf("%d", &pos_deletar);
pos_deletar--; // garantir posicao certa no array
if(pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

for(int i = pos_deletar; i < *pos; i++){
    tarefas[i].prioridade = tarefas[i+1].prioridade;
    strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
    strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
}

*pos = *pos - 1;

return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
if(*pos == 0)
return SEM_TAREFAS;
char categoria[100];
printf("Digite a categoria que voce quer listar: ");
fgets(categoria, 100, stdin);
categoria[strcspn(categoria, "\n")] = '\0';

int categoriaEncontrada = 0;


for(int i=0; i<*pos; i++){
    int comp = strcmp(categoria, tarefas[i].categoria);
    if (comp == 0 || categoria[0] == '\0') {
    categoriaEncontrada = 1;
    printf("Prioridade: %d\t", tarefas[i].prioridade);
    printf("Descricao: %s\n", tarefas[i].descricao);
    }
}
 if (!categoriaEncontrada && categoria[0] != '\0') {
        printf("Não existem tarefas na categoria '%s'.\n", categoria);
    }


return OK;
}

ERROS exportar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    FILE *arq;
    char arqName[25];
    printf("Digite o nome do arquivo: "); // Pede o nome do arquivo a ser criado para o usuário
    scanf("%s", arqName);
    clearBuffer();

    arq = fopen(arqName, "wt");  // Cria um arquivo texto para gravação
    if (arq == NULL) // Se não conseguiu criar
    {
        return CRIAR;
    }
    // Busca de Categoria
    char categoria[T_CATEGORIA];
    printf("Digite a categoria: ");
    fgets(categoria, T_CATEGORIA, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    if(categoria[0] == '\0'){
        for(int i=0; i<*pos; i++){
            int result = fprintf(arq, "Pos: %d\tPrioridade: %d\tCategoria: %s\tDescricao: %s\n", i+1, tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
            if(result == EOF){
                return ESCREVER;
            }
        }
    }else {
        int contCategoria = 0;
        for(int i=0; i<*pos; i++){
            if(strcmp(tarefas[i].categoria, categoria) == 0){
                contCategoria+=1;
                int result = fprintf(arq, "Pos: %d\tPrioridade: %d\tCategoria: %s\tDescricao: %s\n", i+1, tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
                if(result == EOF){
                    return ESCREVER;
                }
            }
        }
        if(contCategoria == 0){
            fclose(arq);
            return CATEGORIA;
        }
    };


    fclose(arq);

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
FILE *f = fopen("tarefas.bin", "wb");
if(f == NULL)
return ABRIR;

int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
if(qtd == 0)
    return ESCREVER;

qtd = fwrite(pos, 1, sizeof(int), f);
if(qtd == 0)
    return ESCREVER;

if(fclose(f))
    return FECHAR;

return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
FILE *f = fopen("tarefas.bin", "rb");
if(f == NULL)
return ABRIR;

int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
if(qtd == 0)
    return LER;

qtd = fread(pos, 1, sizeof(int), f);
if(qtd == 0)
    return LER;

if(fclose(f))
    return FECHAR;

return OK;
}

void clearBuffer(){
int c;
while ((c = getchar()) != '\n' && c != EOF);
}