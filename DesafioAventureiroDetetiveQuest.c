// biblioteca padrão de entrada/saida
#include <stdio.h>   // biblioteca padrão de entrada/saida
#include <stdlib.h>  // biblioteca alocar e desalocar memória 
#include <string.h>  // biblioteca para manipular strings

// Definição da estrutura de pistas (bst)
typedef struct NoBst {
    char pista[100];
    struct NoBst *esquerda;
    struct NoBst *direita;    
    
}NoBst;

// Inserir pista na Bst
NoBst* inserirPistas(NoBst* raiz, const char* pista) {
    if (raiz == NULL) {
        NoBst* novo = (NoBst*)malloc(sizeof(NoBst));
        // copia o contéudo do parâmetro pista para a Bst
        strcpy(novo->pista, pista);
        // inicializa os nós dir. e esq. como nulos
        novo->esquerda = NULL; 
        novo->direita = NULL;
        return novo;
    }
    // compara as strings de pista se vão para dir. ou esq. conforme o tamanho
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPistas(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPistas(raiz->direita, pista);
    }
    
    return raiz;
        
}

// Exibir pistas em ordem (alfabética)
void exibirPistas(NoBst* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Definição da estrutura da árvore da mansão
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;

} Sala;

// Criar sala
Sala* criarSalas(const char* nome, const char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(*nova)); // alocação dinâmica de memória
    if(nova == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1); // encerra o programa se houver erro de memória
    }
    
    strcpy(nova->nome, nome);   
    strcpy(nova->pista, pista); 

    nova->esquerda = NULL; // inicializa filho esquerda como nulo
    nova->direita = NULL;  // inicializa filho direita como nulo
    return nova;
}

// Explorar salas e pistas
void explorar(Sala* atual, NoBst** pistas) {  // NoBst** armazena o end. de memória de um ponteiro simples.
    char opcao;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);
        // se houver pista, mostrar e inserir na Bst
        if(strlen(atual->pista) > 0) {
            
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPistas(*pistas, atual->pista);
            printf("------------------------\n");
            
        }
        printf("Escolha uma opcao\n");
        printf("------------------------\n");
        printf("(e) - esquerda\n");
        printf("(d) - direita\n");
        printf("(s) sair\n");
        
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Nao ha sala a esquerda!\n");    
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Nao ha sala a direita!\n");
        }
        else if (opcao == 's') {
            break;
        }
        else {
            printf("opcao invalida!");
        }
    }
}
// ------------- Função principal MAIN ----------------
int main() {

    // ------ Montar a mansão --------
    Sala* raiz = criarSalas("Hall de Entrada", "Pegadas suspeitas");

    raiz->esquerda = criarSalas("Sala de Estar", "Copo quebrado");
    raiz->direita = criarSalas("Cozinha", "Faca suja");

    raiz->esquerda->esquerda = criarSalas("Biblioteca", "Livro rasgado");
    raiz->esquerda->direita = criarSalas("Escritorio", "Computador quebrado"); 

    raiz->direita->esquerda = criarSalas("Despensa", "Caixa aberta");
    raiz->direita->direita = criarSalas("Quarto", "Cama baguncada");

    raiz->esquerda->esquerda->esquerda = criarSalas("Jardim", "Buraco no centro");
    raiz->esquerda->esquerda->direita = criarSalas("Jardim", "Grama cortada");

    // ------------ Bst de pistas -----------
    NoBst* pistas = NULL;

    // ------------ Exploração --------------
    explorar(raiz, &pistas);

    // ------------ Resultado final ---------
    printf("\nPistas coletadas em ordem alfabetica:\n");
    exibirPistas(pistas);

    return 0;
    
}