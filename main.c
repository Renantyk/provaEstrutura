#include <stdio.h>
#include <stdlib.h>

typedef struct Fatura
{
    int nFatura;
    char data[50];
    float vFatura;
    char status[10];
    struct Fatura* left;
    struct Fatura* right;
} Fatura;

Fatura* criarFatura(int nFatura, const char* data, float vFatura, const char* status){
    Fatura* novaFatura = (Fatura*)malloc(sizeof(Fatura));
    novaFatura->nFatura = nFatura;
    strcpy(novaFatura->data, data);
    novaFatura->vFatura = vFatura;
    strcpy(novaFatura->status, status);
    novaFatura->left = NULL;
    novaFatura->right = NULL;
    return novaFatura;
}

Fatura* inserirFatura(Fatura* raiz, int nFatura, const char* data, float vFatura, const char* status){

    if(raiz == NULL){
        return criarFatura(nFatura, data, vFatura, status);
    }

    if(strcmp(nFatura, raiz->nFatura) < 0) {
        raiz->left = inserirFatura(raiz->left, nFatura, data, vFatura, status);
    } else {
        raiz->right = inserirFatura(raiz->left, nFatura, data, vFatura, status);
    }

    return raiz;
}

Fatura* buscaFatura(Fatura* raiz, int nFatura) {

    if(raiz == NULL || strcmp(raiz->nFatura, nFatura) == 0){
        return raiz;
    }

    if(strcmp(raiz->nFatura, nFatura) > 0){
        return buscaFatura(raiz->left, nFatura);
    }else{
        return buscaFatura(raiz->right, nFatura);
    }
}

void atualizacaoFatura(Fatura* raiz, int nFatura, char novoStatus) {
    Fatura* fatura = buscaFatura(raiz, nFatura);

    if(fatura !=NULL) {
        fatura-> status = novoStatus;
        printf("Status da fatura alterado com sucesso!");
    }else {
        printf("Fatura nao encontrada");
    }
}

Fatura* removerFatura(Fatura* raiz, int nFatura){
    if(raiz == NULL){
        return raiz;
    }

    if(strcmp(nFatura, raiz->nFatura) < 0){
        raiz->left = removerFatura(raiz->left, nFatura);
    }else if(strcmp(nFatura, raiz->nFatura) > 0){
        raiz->right = removerFatura(raiz->right, nFatura);
    }else{
        if(raiz->left == NULL){
            Fatura* aux = raiz->right;
            free(raiz);
            return aux;
        }else if(raiz->right == NULL){
            Fatura* aux = raiz->left;
            free(raiz);
            return aux;
        }

        Fatura* aux = menorFatura(raiz->right);
        strcpy(raiz->nFatura, aux->nFatura);
        raiz->data = aux->data;
        raiz->vFatura = aux->vFatura;
        raiz->status = aux->status;
        raiz->right = removerFatura(raiz->right, aux->nFatura);
    }
    return raiz;
}

void listarFatura(Fatura* raiz){
    if(raiz != NULL){
        listarFatura(raiz->right);
        printf("nFatura: %d | data: %s | vFatura: %f | status: %s \n",raiz->nFatura, raiz->data, raiz->vFatura, raiz->status);
        listarFatura(raiz->left);
    }
}

int main(){

    

    return 0;
}