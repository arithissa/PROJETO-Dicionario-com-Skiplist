#include "dicionario.h"

int main(){
    char ch, op[10];
    char *str = (char *) malloc(40 * sizeof(char));
    char *str2 = (char *) malloc(140 * sizeof(char));
    skiplist *sl = criar(maxnivel, P);
    
    srand((time(NULL)));
    
    while(scanf(" %s", op) != EOF){
        if(strcmp(op, "insercao") == 0){    //insere a palavra str e sua definição
            scanf(" %s", str);
            fgets(str2, 140, stdin);
            inserir(sl, str, str2);
        } else if(strcmp(op, "alteracao") == 0){    //altera a definição de str para str2
            scanf(" %s", str);
            fgets(str2, 140, stdin);
            alterar(sl, str, str2);
        } else if(strcmp(op, "remocao") == 0){  //remove a palavra str do dicionário
            scanf(" %s", str);
            remover(sl, str);
        } else if(strcmp(op, "busca") == 0){    //busca e imprime a definição da palavra str
            scanf(" %s", str);
            busca(sl, str);
        } else{ //imprime todas as palavras iniciadas pelo caractere ch e suas definições
            scanf(" %c", &ch);
            imprimir(sl, ch);
        }
    }

    liberar(sl);
    return 0;
}
