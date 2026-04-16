#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================= Estruturas ===============================

// Árvore de salas
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda; 
    struct Sala *direita;
} Sala;

// Bst de pistas
typedef struct NoBst {
    char pista[50];
    struct NoBst *esq;
    struct NoBst *dir;
} NoBst;

// Table hash
#define TAM_HASH 10

typedef struct Itemhash {
    char pista[50];
    char suspeito[50];
    struct Itemhash *prox;
} Itemhash;

Itemhash* tabelaHash[TAM_HASH];

// ======================== FUNÇÕES ================================

// Criar sala - cria dinamicamente um cômodo
Sala* criarSala(char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Função que retorna a pista associada à sala
char* obterPista(char* sala) {

    if (strcmp(sala, "Sala de Estar") == 0)
        return "pegada";

    if (strcmp(sala, "Biblioteca") == 0)
        return "livro";

    if (strcmp(sala, "Despensa") == 0)
        return "livro";  // ← segunda pista do mordomo

    if (strcmp(sala, "Cozinha") == 0)
        return "faca";

    if (strcmp(sala, "Escritorio") == 0)
        return "documento";

    if (strcmp(sala, "Jardim") == 0)
        return "veneno";
        
    return NULL;

}

// Inserir pista na Bst
NoBst* inserirPista(NoBst* raiz, char* pista) {

    if (raiz == NULL) {
        NoBst* novo = (NoBst*)malloc(sizeof(NoBst));
        strcpy(novo->pista, pista);
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirPista(raiz->dir, pista);
        
    return raiz;    
}

// Função hash simples
int funcaoHash(char* chave) {
    int soma = 0;
    for(int i = 0; chave[i] != '\0'; i++)
        soma += chave[i];
    return soma % TAM_HASH;    
}

// Inserir na hash - associa pista a suspeito
void inserirHash(char* pista, char* suspeito) {

    int idx = funcaoHash(pista);

    Itemhash* novo = (Itemhash*)malloc(sizeof(Itemhash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = tabelaHash[idx];
    tabelaHash[idx] = novo;
}

// Encontra suspeito, busca suspeito pela pista
char* encontrarSuspeito(char* pista) {

    int idx = funcaoHash(pista);

    Itemhash* atual = tabelaHash[idx];

    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;

        atual = atual->prox;    
    }

    return NULL;
}

// Explorar salas - navega na árvore e coleta pistas
void explorarSalas(Sala* atual, NoBst** pistas) {  // NoBst** permite alterar o ponteiro da BST

    char op;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        char* pista = obterPista(atual->nome);

        if (pista != NULL) {
            char* suspeito = encontrarSuspeito(pista);

            printf("Pista encontrada: %s", pista);

            if (suspeito != NULL) {
                printf(" -> Suspeito: %s", suspeito);
            }

            printf("\n");

            *pistas = inserirPista(*pistas, pista);
        } else {
            printf("Nenhuma pista encontrada!\n");
        }

        printf("(e) - esquerda\n");
        printf("(d) - direita\n");
        printf("(s) - Sair\n");
        scanf(" %c", &op);

        if (op == 'e') {
            atual = atual->esquerda;
        } else if (op == 'd') {
            atual = atual->direita;
        } else if (op == 's') {
            printf("\nEncerrando exploracao...\n");
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }
}

// Mostrar pistas coletadas em ordem
void mostrarPistas(NoBst* raiz) {
    if (raiz != NULL) {
        mostrarPistas(raiz->esq);
        printf("%s\n", raiz->pista);
        mostrarPistas(raiz->dir);
    }
}

// Contar quantas pistas apontam para o suspeito
int contarPistas(NoBst* raiz, char* suspeito) {

    if (raiz == NULL)
        return 0;

    int count = 0;
    
    char* s = encontrarSuspeito(raiz->pista);

    if (s != NULL && strcmp(s, suspeito) == 0)
        count++;

    return count + contarPistas(raiz->esq, suspeito) + contarPistas(raiz->dir, suspeito);    
}

// Verificar suspeito final - julgamento
void verificarSuspeitoFinal(NoBst* pistas) {

    char suspeito[50];

    printf("\nDigite o nome do suspeito (ex: mordomo, advogado...): ");
    scanf("%s", suspeito);

    int total = contarPistas(pistas, suspeito);

    if (total >= 2)
        printf("Culpado Confirmado!\n");
    else
        printf("Provas insuficientes.\n");    
}

// ================== FUNÇÃO MAIN ===============================
int main() {

    // inicializar tabela hash
    for (int i = 0; i < TAM_HASH; i++)
        tabelaHash[i] = NULL;

    // Criar árvore da mansão
    Sala* raiz = criarSala("Hall de Entrada");

    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Cozinha");

    raiz->esquerda->esquerda = criarSala("Biblioteca");
    raiz->esquerda->direita = criarSala("Escritorio");

    raiz->direita->esquerda = criarSala("Despensa");
    raiz->direita->direita = criarSala("Jardim");

    

    // inserir associaçoes pista -> suspeito
    inserirHash("pegada", "mordomo");
    inserirHash("livro", "mordomo");
    inserirHash("faca", "cozinheiro");
    inserirHash("documento", "advogado");
    inserirHash("veneno", "garcon");

    // BST de pistas coletadas
    NoBst* pistas = NULL;

    
    // Exploração
    explorarSalas(raiz, &pistas);

    printf("\n=== FASE FINAL: ANALISE DAS PISTAS ===\n");

    // Mostrar pistas coletadas
    printf("\nPistas coletadas:\n");
    mostrarPistas(pistas);

    // Julgamento final
    verificarSuspeitoFinal(pistas);

    printf("\nFim do jogo!\n");

    return 0;

}