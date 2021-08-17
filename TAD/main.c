// Alunos: Bruno Costa dos Passos, Raphael Yoshiki, Kamile Novaes

// Para compilar o programa com o gcc, basta usar o comando: gcc main.c fila.c -o main -lm
// Ou então com os seguintes comandos:
// gcc -c main.c
// gcc -c fila.c
// gcc -o main main.o fila.o

#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação do menu do outro programador usando a fila.h


void Menu(){

    int opc = -1, temp;
    Fila fila = Inicializar();

    while(opc != 4){

        printf("Opções:\n");

        printf("[0] - Inserir elemento na fila.\n");
        printf("[1] - Remover elemento da fila.\n");
        printf("[2] - Imprimir fila.\n");
        printf("[3] - Sair.\n");

        scanf("%d", &opc);


        switch(opc){

            case 0:

                printf("Digite o elemento a ser inserido:\n");
                scanf("%d", &temp);
                Inserir(fila, temp);
                system("clear");
                break;
            
            case 1:
                Remove(fila);
                break;

            case 2:
                Imprimir(fila);
                break;
            case 3:
                exit(0);
                break;
        }
    }
}

int main(){

    Menu();

    return 0;

}
