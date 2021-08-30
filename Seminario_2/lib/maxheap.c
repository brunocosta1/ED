#include "maxheap.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define N 10

int totalElementos = 0;

typedef struct item{

    int chave;
    void *obj;

}Item;

struct heap{

    Item vet[N];

};

Heap Inicializar(){

    Heap h = (Heap)malloc(sizeof(struct heap));

    for(int i = 0; i < N; i++){

        h->vet[i].obj = NULL;
        h->vet[i].chave = 0;

    }

    return h;

}

Heap Destruir(Heap h){

    for(int i = 0; i < totalElementos; i++)
        free(h->vet[i].obj);

    free(h);
    return NULL;

}


//Funcoes auxiliares de indice

int indiceFilhoEsq(int x){
	
	int indice=(2*x)+1;
	
	if(x >= totalElementos || indice>=totalElementos){
		return -1;
	}
	else{
		return indice;
	}
}

int indiceFilhoDir(int x){
	
	int indice=(2*x)+2;
	
	if(x>=totalElementos || indice>=totalElementos){
		return -1;
	}
	else{
		return indice;
	}
}

int indicePai(int x){
	
	int indice= (int)(floor((x-1) / 2));
	
	if(x<=0 || x>= totalElementos){
		return -1;
	}
	else{
		return indice;
	}
}

void swap(Heap heap, int pos1, int pos2){

    int aux = heap->vet[pos1].chave;
    heap->vet[pos1].chave = heap->vet[pos2].chave;
    heap->vet[pos2].chave = aux;

    void *temp = heap->vet[pos1].obj;
    heap->vet[pos1].obj = heap->vet[pos2].obj;
    heap->vet[pos2].obj = temp;

}

//Inserir e ajustar a heap


void AjustarSubindo(Heap heap, int pos){
	
	if(pos!=-1){
		int pai=indicePai(pos);
	
		if(pai!=-1){
			if(heap->vet[pos].chave > heap->vet[pai].chave){ //verifica se o no eh menor que o pai

                swap(heap, pos, pai);
				AjustarSubindo(heap,pai);

			}
		}
	}
}

int Inserir(Heap heap, int chave, void *objeto, int sizeObj){
	
    if(totalElementos == N)
        return 0;


    heap->vet[totalElementos].chave = chave;
    heap->vet[totalElementos].obj = malloc(sizeObj);
    memcpy(heap->vet[totalElementos].obj, objeto, sizeObj);
	totalElementos++;
	
	AjustarSubindo(heap, totalElementos-1);

    return 1;
}
//Remover e ajustar a heap

void AjustarDescendo(Heap heap, int pos){
	
	if(pos!=-1 && indiceFilhoEsq(pos) != -1){
		
		//Descobre qual o maior filho
		int indiceMaiorFilho=indiceFilhoEsq(pos);
		
		if(indiceFilhoDir(pos)!= -1 && heap->vet[indiceFilhoDir(pos)].chave > heap->vet[indiceMaiorFilho].chave){
			indiceMaiorFilho=indiceFilhoDir(pos);
		}
		
		//Verifica se existe filho maior que o no atual
		if(heap->vet[indiceMaiorFilho].chave > heap->vet[pos].chave){

            swap(heap, pos, indiceMaiorFilho);
			AjustarDescendo(heap,indiceMaiorFilho);

		}
	}
}

int Remover(Heap heap, void *objeto, int sizeObj){
	
	if(totalElementos==0){
		return -1;
	}
	else{
        
		int retorno = heap->vet[0].chave;


        //Copiando o objeto a ser removido.

        memcpy(objeto, heap->vet[0].obj, sizeObj);

        //Trocando 
        swap(heap, 0, totalElementos-1);

        //Removendo
        
        heap->vet[totalElementos-1].chave = 0;
        free(heap->vet[totalElementos-1].obj);
        heap->vet[totalElementos-1].obj = NULL;

		totalElementos--;

		AjustarDescendo(heap,0);

		return retorno;
	}
}

void Imprimir(Heap heap){

    printf("Chaves: |");
    for(int i = 0; i < N; i++){
        printf(" %d |", heap->vet[i].chave);
    }

    printf("\n");

}

int Existe(Heap h, int chave){

    for(int i = 0; i < totalElementos; i++)
        if(h->vet[i].chave == chave)
            return 1;

    return 0;

}

