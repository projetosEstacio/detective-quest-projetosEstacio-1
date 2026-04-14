// biblioteca padrão de entrada/saida
#include <stdio.h>   // biblioteca padrão de entrada/saida
#include <stdlib.h>  // biblioteca alocar e desalocar memória 
#include <string.h>  // biblioteca para manipular strings

// Definição da estrutura da árvore
typedef struct Sala {
    char valor[50];
    struct Sala* esquerda;
    struct Sala* direita;

} Sala;

// Função para criar nó, criando aloca memória dinâmica, define um valor e inicializa
// os ponteiros dos filhos como nulos.

Sala* criarNo(const char* valor) {
    Sala* novo = (Sala*)malloc(sizeof(*novo)); // alocação dinâmica de memória
    if(novo == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1); // encerra o programa se houver erro de memória
    }
    strcpy(novo->valor, valor); // copia a string valor para o campo do valor da estrutura Sala
    novo->esquerda = NULL; // inicializa filho esquerda como nulo
    novo->direita = NULL;  // inicializa filho direita como nulo
    return novo;
}   

// Função recursiva para inserir um novo valor na árvore binária. 
// A ordem alfabética organiza os valores dos nós. 
// Se o valor for menor que o nó atual vai para subarvore da esquerda
// Se o valor for maior qie o nó atual vai para sbuarvore da direita

Sala* inserirNo(Sala* raiz, const char* valor) {
    if (raiz == NULL) {
        // Se a árvore ou subarvore estiver vazia, cria um novo nó 
        return criarNo(valor);

    }
    if (strcmp(valor, raiz->valor) < 0) {
        // insere na subarvore esquerda
        raiz->esquerda = inserirNo(raiz->esquerda, valor);
    } else {
        // insere na subarvore direita
        raiz->direita = inserirNo(raiz->direita, valor);
    }
    return raiz;
}   

// Função preOrdem - percorre e imprime a árvore em pre-ordem (raiz, esquerda, direita)

void preOrdem(Sala* raiz) {
    if(raiz != NULL) {
        printf("%s ", raiz->valor); // visita o nó atual (raiz)
        printf(" - ");              // caracter para separar nós na impressão
        preOrdem(raiz->esquerda);   // visita a subarvore esqueda
        preOrdem(raiz->direita);    // visita a subarvore direita
    }
}

// Função ordem - percorre e imprime a árvore em ordem (esquerda, raiz, direita)

void emOrdem(Sala* raiz) {
    if(raiz != NULL) {
        emOrdem(raiz->esquerda);    // visita subarvore esquerda
        printf(" - ");              // caracter para separar nós na impressão
        printf("%s ", raiz->valor); // visita no raiz
        emOrdem(raiz->direita);     // vista subarvore direita
    }
}

// Função pos ordem - percorre e imprime a árvore (esquerda, direita, raiz)

void posOrdem(Sala* raiz) {
    if(raiz != NULL) {
        posOrdem(raiz->esquerda);    // visita subarvore esquerda
        printf(" - ");              // caracter para separar nós na impressão
        posOrdem(raiz->direita);        // vista subarvore direita
        printf("%s ", raiz->valor); // visita no raiz
    }
}

// Função para liberar memória, libera recursivamente toda a memória para a árvore

void liberaMemo(Sala* raiz) {
    if(raiz != NULL) {
        liberaMemo(raiz->esquerda);
        liberaMemo(raiz->direita);
        free(raiz); // libera nó atual
    }
}

/* Função principal main() - montar a árvore - menu de opções para percorrer a árvore
   em ordem, pela esquerda ou pela direita
*/    

int main() {

    Sala* raiz = NULL; // Inicializa a árvore como vazia

    char opcao; // opção de menu

    // criando a árvore
    raiz = inserirNo(raiz, "Hall de Entrada");
    raiz = inserirNo(raiz, "Sala de Estar");
    raiz = inserirNo(raiz, "Cozinha");
    raiz = inserirNo(raiz, "Biblioteca");
    raiz = inserirNo(raiz, "Escritorio");
    raiz = inserirNo(raiz, "Despensa");
    raiz = inserirNo(raiz, "Quarto");
    raiz = inserirNo(raiz, "Jardim");
    
    // menu de opções
    do {

        printf("-----------------------------\n");
        printf("   Escolha uma opcao \n");
        printf("-----------------------------\n");
        printf("\no - Percorrer por ordem");
        printf("\ne - Percorrer pela esquerda");
        printf("\nd - Percorrer pela direira\n");
        printf("s - Sair\n");
        printf("-----------------------------\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);
        
        getchar(); // limpa enter

        if (opcao == 'o') {

            printf("Pecorrendo por ordem (raiz, e, d)\n");
            preOrdem(raiz);
            printf("\n");

        }else if(opcao == 'e') {

            printf("Percorrendo pela esquerda (e, raiz, d)\n");
            emOrdem(raiz);
            printf("\n");

        }else if(opcao == 'd') {
            
            printf("Percorrendo pela direita (e ,d , raiz)\n");
            posOrdem(raiz);
            printf("\n");

        }else if(opcao == 's') {
            printf("Saindo...");
        }else {
            printf("Opcao invalida!");    
        }
            printf("\n");

    }while (opcao != 's');

    liberaMemo(raiz);

    return 0;
    
}
