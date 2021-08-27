typedef struct heap *Heap;

Heap Inicializar();
Heap Destruir(Heap h);
int Inserir(Heap p, int chave, void *objeto, int sizeObj);
int Remover(Heap p, int chave, void *objeto, int sizeObj);
void Imprimir(Heap p);
int Existe(Heap p, int chave);
