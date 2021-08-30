#include <stdio.h>
#include "../lib/maxheap.h"

typedef struct produto{

    char nome[15];
    float preco;
    int codigo;

}Produto;

int main(){

    Heap h = Inicializar();

    for(int i = 0; i < 3; i++){

        Produto p;

        printf("Forneça as informações do produto:\n");
        printf("Nome: ");
        scanf("%s", p.nome);
        printf("Preço: ");
        scanf("%f", &p.preco);
        printf("Codigo: ");
        scanf("%d", &p.codigo);
        putc('\n', stdin);

        if(!Existe(h, p.codigo))
            Inserir(h, p.codigo, &p, sizeof(p));

    }

    Imprimir(h);

    for(int i = 0; i < 3; i++){

        int key;
        Produto obj;

        key = Remover(h, &obj, sizeof(obj));

        printf("\n Chave: %d\t Objeto: (%s, %.2f)\n", obj.codigo, obj.nome, obj.preco);
        Imprimir(h);
        printf("\n");

    }


    h = Destruir(h);

    return 0;

}
