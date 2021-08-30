#include <stdio.h>
#include "../lib/maxheap.h"

typedef struct moto{

    char marca[15];
    char modelo[20];
    int ano;
    int renavam;

}Moto;

int main(){

    Heap h = Inicializar();

    for(int i = 0; i < 3; i++){

        Moto m;

        printf("Forneça as informações da moto:\n");
        printf("Marca: ");
        scanf("%s", m.marca);
        printf("Modelo: ");
        scanf("%s", m.modelo);
        printf("Ano: ");
        scanf("%d", &m.ano);
        putc('\n', stdin);
        printf("Renavam: ");
        scanf("%d", &m.renavam);
        putc('\n', stdin);

        if(!Existe(h, m.renavam))
            Inserir(h, m.renavam, &m, sizeof(m));
    }

    Imprimir(h);

    for(int i = 0; i < 3; i++){

            int key;
            Moto obj;

            key = Remover(h, &obj, sizeof(obj));

            printf("\nChave: %d\t Objeto: (%s, %s, %d)\n", obj.renavam, obj.modelo, obj.marca, obj.ano);
            Imprimir(h);
            printf("\n");

    }

    h = Destruir(h);

    return 0;
}
