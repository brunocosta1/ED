#ifndef MAXHEAP_H
#define MAXHEAP_H 

typedef struct heap *Heap;

Heap Inicializar();
Heap Destruir(Heap h);
int Inserir(Heap p, int chave, void *objeto, int sizeObj);
int Remover(Heap p, int *chave, void *objeto, int sizeObj);
void Imprimir(Heap heap);
int Existe(Heap p, int chave);

#endif
