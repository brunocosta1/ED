#ifndef MAXHEAP_H
#define MAXHEAP_H 

typedef struct heap *Heap;

Heap Inicializar();
Heap Destruir(Heap h);
int Inserir(Heap h, int chave, void *objeto, int sizeObj);
int Remover(Heap h, void *objeto, int sizeObj);
void Imprimir(Heap heap);
int Existe(Heap h, int chave);

#endif
