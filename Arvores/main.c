// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{

    int info;
    struct arvore *esq;
    struct arvore *dir;

}arvore;

// Código para verificar qual sistema operacional está rodando.

#ifdef __unix__
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
    #include <windows.h>
#endif

// Função para deixar o menu mais dinâmico.

void Pausa(){

    #ifdef OS_Windows
        system("timeout 1");
        system("cls");
    #else
        system("sleep 1");
        system("clear");
    #endif

}

//

arvore *CriaElemento(int info){

    arvore *nova = (arvore*)malloc(sizeof(arvore));
    nova->info = info;
    nova->dir = NULL;
    nova->esq= NULL;

    return nova;

}
// Função para ler árvore a partir de um arquivo

arvore *LerArvore(FILE *arq){

    char c;
    int num;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    if(num == -1){
        fscanf(arq, "%c", &c);
        return NULL;
    }else{

        arvore *a = CriaElemento(num);
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

// Função para contar o número de elementos na árvore

int Contador(arvore *a){

    if(a != NULL)
        return 1 + Contador(a->dir) + Contador(a->esq);
    else
        return 0;
}

// Função para verificar se um elemento existe na árvore

int Existe(arvore *a, int info){

    if(a == NULL)
        return 0;
    else if(a->info == info)
        return 1;
    else{

        if(Existe(a->esq, info) || Existe(a->dir, info))
            return 1;
        else
            return 0;

    }
}


// Funções de impressão da árvore

void ImprimePreOrdem(arvore *a){

    if(a != NULL){
        printf("%d ", a->info);
        ImprimePreOrdem(a->esq);
        ImprimePreOrdem(a->dir);
    }

}

void ImprimeEmOrdem(arvore *a){

    if(a != NULL){
        ImprimeEmOrdem(a->esq);
        printf("%d ", a->info);
        ImprimeEmOrdem(a->dir);
    }
}

void ImprimePosOrdem(arvore *a){

    if (a != NULL){
        ImprimePosOrdem(a->esq);
        ImprimePosOrdem(a->dir);
        printf("%d ", a->info);
    }

}

void ImprimirNoFolha(arvore *a){

    if(a != NULL){

        if(a->dir == NULL && a->esq == NULL)
            printf("%d ", a->info);

        ImprimirNoFolha(a->esq);
        ImprimirNoFolha(a->dir);

    }
}

// Funções do menu

void MenuDeImpressao(arvore *a){

    int opc = 0;
    
    while(opc != 3){

        printf("Digite a forma de impressão: \n");
        printf("[0] - Pré-ordem\n");
        printf("[1] - Em-ordem\n");
        printf("[2] - Pós-ordem\n");
        printf("[3] - Voltar\n");
        printf("[4] - Sair\n\n");
        printf("Opção :");
        scanf("%d", &opc);

        switch(opc){

            case 0:
                printf("Pré-ordem: ");
                ImprimePreOrdem(a);
                break;
            case 1:
                printf("Em-ordem: ");
                ImprimeEmOrdem(a);
                break;
            case 2:
                printf("Pós-ordem: ");
                ImprimePosOrdem(a);
                break;
            case 3:
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                Pausa();
                break;
        }
    }

}

void Menu(arvore *a){

    int opc = 0, info = 0;
    char *nome_arquivo;
    FILE *arq;

    while(opc != 5){

        printf("[0] - Ler uma árvore de um arquivo.\n");
        printf("[1] - Imprimir árvore\n");
        printf("[2] - Verificar se um elemento existe na árvore\n");
        printf("[3] - Contar o número de um elemento na árvore.\n");
        printf("[4] - Imprimir os nós folhas da árvore\n");
        printf("[5] - Sair.\n\n");

        switch(opc){

            case 0:

                printf("Digite o nome do arquivo: ");
                scanf("%s", nome_arquivo);
                arq = fopen(nome_arquivo, "rt");
                a = LerArvore(arq);
                fclose(arq);
                printf("Arquivo lido.\n");
                Pausa();
                break;

            case 1:

                MenuDeImpressao(a);
                break;

            case 2:

                printf("Digite o valor a ser procurado: ");
                scanf("%d", &info);
                if(Existe(a, info))
                    printf("Existe!\n");
                else
                    printf("Não existe!\n");
                Pausa();
                break;

            case 3:

                printf("Número de elementos na árvore: %d\n", Contador(a));
                Pausa();
                break;

            case 4:
                printf("Nós folhas: ");
                ImprimirNoFolha(a);
                Pausa();
                break;

            case 5:
                exit(0);
                break;

            default:
                printf("Opção inválida, digite novamente\n");
                break;

        }


    }
}



//



arvore *DestruirArvore(arvore *a){

    if(a != NULL){
        a->esq = DestruirArvore(a->esq);
        a->dir = DestruirArvore(a->dir);
        free(a);
    }

    return NULL;

}

int main(){

    arvore *a = NULL;
    FILE *arq;

    /*arq = fopen("arquivo.txt", "rt");*/
    /*a = LerArvore(arq);*/

    /*ImprimePreOrdem(a);*/

    /*fclose(arq);*/

    Menu(a);


    a = DestruirArvore(a);

    return 0;

}
