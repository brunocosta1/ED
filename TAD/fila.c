#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

#define N 100

struct fila{

    int vet[N];
    int ultimo;
    int primeiro;

};


Fila Inicializar(){

    Fila f = (Fila)malloc(sizeof(struct fila));

    for(int i = 0; i < N; i++)
        f->vet[i] = -1;

    f->ultimo = -1;
    f->primeiro = 0;

    return f;
}

Fila Destruir(Fila f){

    free(f);
    return NULL;
}

void Inserir(Fila f, int x){

    if(f->ultimo == N - 1)
        f->ultimo = -1;

    f->ultimo++;
    f->vet[f->ultimo] = x;

}

void Remove(Fila f){

    system("clear");
    printf("Item removido: %d\n", f->vet[f->primeiro]);
    f->vet[f->primeiro] = -1;

    f->primeiro++;
    if(f->primeiro == N)
        f->primeiro = 0;
}

void Imprimir(Fila f){

    system("clear");
    for(int i = 0; i < N; i++){

        if(f->vet[i] != -1)
            printf("| %d |", f->vet[i]);

    }

    printf("\n");
}

