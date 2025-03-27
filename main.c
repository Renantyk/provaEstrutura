#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fatura {
    int nFatura;
    char data[50];
    float vFatura;
    char status[10];
    struct Fatura* left;
    struct Fatura* right;
} Fatura;

Fatura* criarFatura(int nFatura, const char* data, float vFatura, const char* status) {
    Fatura* novaFatura = (Fatura*)malloc(sizeof(Fatura));
    novaFatura->nFatura = nFatura;
    strcpy(novaFatura->data, data);
    novaFatura->vFatura = vFatura;
    strcpy(novaFatura->status, status);
    novaFatura->left = NULL;
    novaFatura->right = NULL;
    return novaFatura;
}

Fatura* inserirFatura(Fatura* raiz, int nFatura, const char* data, float vFatura, const char* status) {
    if (raiz == NULL) {
        return criarFatura(nFatura, data, vFatura, status);
    }
    if (nFatura < raiz->nFatura) {
        raiz->left = inserirFatura(raiz->left, nFatura, data, vFatura, status);
    } else {
        raiz->right = inserirFatura(raiz->right, nFatura, data, vFatura, status);
    }
    return raiz;
}

void listarFatura(Fatura* raiz) {
    if (raiz != NULL) {
        listarFatura(raiz->left);
        printf("nFatura: %d | Data: %s | Valor: %.2f | Status: %s\n", raiz->nFatura, raiz->data, raiz->vFatura, raiz->status);
        listarFatura(raiz->right);
    }
}

Fatura* buscaFatura(Fatura* raiz, int nFatura) {
    if (raiz == NULL || raiz->nFatura == nFatura) {
        return raiz;
    }
    if (nFatura < raiz->nFatura) {
        return buscaFatura(raiz->left, nFatura);
    } else {
        return buscaFatura(raiz->right, nFatura);
    }
}

void atualizacaoFatura(Fatura* raiz, int nFatura, const char* novoStatus) {
    Fatura* fatura = buscaFatura(raiz, nFatura);
    if (fatura != NULL) {
        strcpy(fatura->status, novoStatus);
        printf("Status da fatura alterado com sucesso!\n");
    } else {
        printf("Fatura nao encontrada.\n");
    }
}

Fatura* menorFatura(Fatura* raiz) {
    while (raiz->left != NULL) {
        raiz = raiz->left;
    }
    return raiz;
}

Fatura* removerFatura(Fatura* raiz, int nFatura) {
    if (raiz == NULL) {
        return raiz;
    }
    if (nFatura < raiz->nFatura) {
        raiz->left = removerFatura(raiz->left, nFatura);
    } else if (nFatura > raiz->nFatura) {
        raiz->right = removerFatura(raiz->right, nFatura);
    } else {
        if (raiz->left == NULL) {
            Fatura* aux = raiz->right;
            free(raiz);
            return aux;
        } else if (raiz->right == NULL) {
            Fatura* aux = raiz->left;
            free(raiz);
            return aux;
        }
        Fatura* aux = menorFatura(raiz->right);
        raiz->nFatura = aux->nFatura;
        strcpy(raiz->data, aux->data);
        raiz->vFatura = aux->vFatura;
        strcpy(raiz->status, aux->status);
        raiz->right = removerFatura(raiz->right, aux->nFatura);
    }
    return raiz;
}

int main() {
    Fatura* raiz = NULL;
    int opcao, nFatura;
    char data[50], status[10];
    float vFatura;
    
    do {
        printf("\nMenu:\n");
        printf("1. Inserir Fatura\n");
        printf("2. Listar Faturas\n");
        printf("3. Atualizar Status\n");
        printf("4. Remover Fatura\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Numero da Fatura: ");
                scanf("%d", &nFatura);
                printf("Data de Vencimento: ");
                scanf("%s", data);
                printf("Valor da Fatura: ");
                scanf("%f", &vFatura);
                printf("Status (pendente/paga): ");
                scanf("%s", status);
                raiz = inserirFatura(raiz, nFatura, data, vFatura, status);
                break;
            case 2:
                listarFatura(raiz);
                break;
            case 3:
                printf("Numero da Fatura: ");
                scanf("%d", &nFatura);
                printf("Novo Status (pendente/paga): ");
                scanf("%s", status);
                atualizacaoFatura(raiz, nFatura, status);
                break;
            case 4:
                printf("Numero da Fatura a remover: ");
                scanf("%d", &nFatura);
                raiz = removerFatura(raiz, nFatura);
                printf("Fatura removida com sucesso!\n");
                break;
            default:
                printf("Opcao nao existente\n");
        }
    } while (opcao != 4);
    
    return 0;
}