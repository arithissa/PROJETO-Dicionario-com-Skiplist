#include "dicionario.h"

no *novono(char *palavra, char *definicao, int nivel){  //cria um novo nó
    no *p = (no *) malloc(sizeof(no));  //aloca memória para o nó
    if(p != 0){
        strcpy(p->palavra, palavra);  //armazena a palavra no novo nó da skip list
        strcpy(p->definicao, definicao);  //armazena a definição da palavra
        p->prox = malloc((nivel + 1) * sizeof(no *)); //aloca memória para o nível da skip list
        for(int i = 0; i < nivel + 1; i++)  //inicializa os níveis com 0
            p->prox[i] = NULL;
  }

    return p; //retorna p 
}

skiplist *criar(int max, float p){ //aloca memoria para uma nova skiplist
    skiplist *sl = malloc(sizeof(skiplist));
    if(sl != NULL){
        sl->nivelmax = max;
        sl->p = p;
        sl->nivel = 0;
        sl->inicio = novono("-1", "-1", max); //inicializa o primeiro nó da skip list com -1
    }

    return sl;
}

float randomnum(){
    float result = 0.0;
    
    result = ((float) rand()) / (float)(RAND_MAX);
    
    return result;
}

int randomlvl(){    //gera um nível aleatório
    int result = 1;
    
    while(randomnum() < P && result < maxnivel)
        result++;
        
    return result;
}

int busca(skiplist *sl, char *palavra){ //faz a busca de uma palavra e imprime com sua definição
    if(sl == NULL)
        return 1; //erro

    no *p = sl->inicio; 
    for(int i = sl->nivel; i >= 0; i--){  //faz uma busca nos níveis da skip list 
        while(p->prox[i] != NULL && strcmp(p->prox[i]->palavra, palavra) < 0)
            p = p->prox[i];
    }

    p = p->prox[0]; //p aponta para a posição da palavra sendo buscada

    if(p != NULL && strcmp(p->palavra, palavra) == 0){  //se a palavra foi encontrada
        printf("%s%s", p->palavra, p->definicao);
        return 0; //sucesso
    } else{
        printf("OPERACAO INVALIDA\n");
        return 1; //não encontrado
    }
}

int inserir(skiplist *sl, char *palavra, char *definicao){  //insere uma palavra e sua definição na skip list
    if(sl == NULL)
        return 1; //erro

    no *p = sl->inicio;
    no **aux;
    aux = malloc((sl->nivelmax + 1) * sizeof(no *));
    for(int i = 0; i < sl->nivelmax; i++) //inicializa os níveis com NULL 
        aux[i] = NULL;

    for(int i = sl->nivel; i >= 0; i--){  //faz uma busca nos níveis da melhor posição para inserir a palavra
        while(p->prox[i] != NULL && strcmp(p->prox[i]->palavra, palavra) < 0){  //procura a posição
            if(strcmp(p->prox[i]->palavra, palavra) == 0){  //se a palavra já existir na skip list 
                printf("OPERACAO INVALIDA\n");
                return 1; //erro
            } else
                p = p->prox[i];
        }
        aux[i] = p; //guarda o nó que será atualizado
    }

    p = p->prox[0]; //p aponta para a próxima posição na qual a palavra será inserida
    if(p == NULL || strcmp(p->palavra, palavra) != 0){  //se p for nulo ou a palavra ainda não estiver na skip list
        int nivel = randomlvl(); //sorteia o novo nível
        no *novo = novono(palavra, definicao, nivel); //cria um novo nó
        if(novo == NULL){
            free(aux);
            return 1; //erro na inserção
        }

        if(nivel > sl->nivel){  //atualiza os níveis 
            for(int i = sl->nivel + 1; i <= nivel; i++)
                aux[i] = sl->inicio;
            sl->nivel = nivel;
        }

        for(int i = 0; i <= nivel; i++){  //faz a inserção 
            novo->prox[i] = aux[i]->prox[i];
            aux[i]->prox[i] = novo;
        }
    }

    free(aux);
    return 0; //elemento inserido
}

int remover(skiplist *sl, char *palavra){ //remove uma palavra da skip list 
    if(sl == NULL)
        return 1; //erro

    no *p = sl->inicio;
    no **aux;
    aux = malloc((sl->nivelmax + 1) * sizeof(no *));
    for(int i = 0; i <= sl->nivelmax; i++)  //inicializa os níveis com NULL 
        aux[i] = NULL;

    for(int i = sl->nivel; i >= 0; i--){  //percorre os níveis procurando a palavra
        while(p->prox[i] != NULL && strcmp(p->prox[i]->palavra, palavra) < 0)
            p = p->prox[i];
        aux[i] = p;
    }

    p = p->prox[0]; //p aponta para o nível 0 do próximo nó
    if(p != NULL && strcmp(p->palavra, palavra) == 0){  //se a palavra foi encontrada
        for(int i = 0; i < sl->nivel; i++){
            if(aux[i]->prox[i] != p)
                break;
            aux[i]->prox[i] = p->prox[i];   //atualiza os ponteiros
        }

        while(sl->nivel > 0 && sl->inicio->prox[sl->nivel] == NULL) //remove os níveis que não possuem elemento
            sl->nivel--;

        free(p->prox);
        free(p);
        free(aux);
        return 0; //elemento removido
    } else{
        printf("OPERACAO INVALIDA\n");
        free(aux);
        return 1; //elemento não encontrado
    }
}

int alterar(skiplist *sl, char *palavra, char *alteracao){  //altera a definição da palavra 
    if(sl == NULL)
        return 1; //erro

    no *p = sl->inicio; 
        for(int i = sl->nivel; i >= 0; i--){  //faz uma busca nos níveis da skip list 
            while(p->prox[i] != NULL && strcmp(p->prox[i]->palavra, palavra) < 0)
                p = p->prox[i];
        }

        p = p->prox[0]; //p aponta para a posição da palavra sendo buscada

        if(p != NULL && strcmp(p->palavra, palavra) == 0){  //se a palavra foi encontrada
            p->definicao[0] = '\0';
            strcpy(p->definicao, alteracao);
            return 0;   //sucesso
        } else{
            printf("OPERACAO INVALIDA\n");
            return 1;   //erro
        }
}

void imprimir(skiplist *sl, char ch){ //imprime todas as palavras iniciadas por determinado caractere em ordem alfabética
    if(sl == NULL)
        return; //erro
    int cont = 0, i;
  
    no *p = sl->inicio;
    for(i = 0; i < (sl->nivel); i++){ //percorre os níveis 
        while(p->prox[i] != NULL){
            if(p->prox[i]->palavra[0] == ch){ //se a palavra inicia com o caractere ch 
                printf("%s%s", p->prox[i]->palavra, p->prox[i]->definicao);
                cont = 1;
            }
        p = p->prox[i];
        }
    }

    if(cont == 0)
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", ch);

    return;
}

void liberar(skiplist *sl){ //desaloca a memória e destrói a skip list
    if(sl == NULL)
        return;
  
    no *p, *atual;
    atual = sl->inicio->prox[0];
    while(atual != NULL){
        p = atual;
        atual = atual->prox[0];
        free(p->prox);
        free(p);
    }

    free(sl->inicio);
    free(sl);
}
