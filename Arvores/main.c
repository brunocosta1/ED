// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

typedef struct arvore{

    int info;
    struct arvore *esq;
    struct arvore *dir;

}arvore;

// C�digo para verificar qual sistema operacional est� rodando.

#ifdef __unix__
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
    #include <windows.h>
#endif

// Fun��o para deixar o menu mais din�mico.

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
// Fun��o para ler �rvore a partir de um arquivo

arvore *LerArvore(arvore *a, FILE *arq){

    char c;
    int num;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    if(num == -1){
        fscanf(arq, "%c", &c);
        return NULL;
    }else{

        arvore *a = CriaElemento(num);
        a->esq = LerArvore(a,arq);
        a->dir = LerArvore(a,arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

// Fun��o para contar o n�mero de elementos na �rvore

int Contador(arvore *a){

    if(a != NULL)
        return 1 + Contador(a->dir) + Contador(a->esq);
    else
        return 0;
}

// Fun��o para verificar se um elemento existe na �rvore

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

//Fun��o para contar a altura da �rvore

int Altura(arvore *a){

	if(a==NULL){
		return 0;
	}
	else{
		int he, hd;
		he=Altura(a->esq);
		hd=Altura(a->dir);

		if(he>hd){
			return he + 1;
		}
		else{
			return hd + 1;
		}
	}
}

int ArvoreBalanceada(arvore *a){

    if(a != NULL){

        int alturaDireita, alturaEsquerda;

        alturaEsquerda = Altura(a->esq);
        alturaDireita = Altura(a->dir);

        if(abs(alturaDireita - alturaEsquerda) > 1)
            return 0;
        else{

            int temp1 = ArvoreBalanceada(a->dir), temp2 = ArvoreBalanceada(a->esq);

            if(temp1 && temp2)
                return 1;
            else
                return 0;

        }


    }

}

//Imprimir os elementos de um determinado nivel da arvore


void ImprimirNivel(arvore *a, int cont, int nivel){
	
	if(a!=NULL){
		if(cont==nivel){
			printf("%d ", a->info);
		}
		else{
			ImprimirNivel(a->esq,cont+1,nivel);
			ImprimirNivel(a->dir,cont+1,nivel);
		}
	}
}


// Fun��es de impress�o da �rvore

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

void ImprimirLargura(arvore *a){

	int i;
	int nivel=0;

	if(a!=NULL){
		for(i=1;i<=Altura(a);i++){
			ImprimirNivel(a,0,nivel++);
			printf("\n");
		}
	}
}

//Fun��o que verifica se a �rvore � cheia

int ArvoreCheia(arvore *a){

	int altura=Altura(a);
	int nos=Contador(a);
	int valor=pow(2,altura);
	valor=valor-1;

	if(a==NULL){
		return 0;
	}
	else{
		if(valor==nos){
			return 1;
		}
	}
}

// Fun��es do menu

void MenuDeImpressao(arvore *a){

    int opc = 0;
    
    while(opc != 6){

        printf("\nDigite a forma de impress�o: \n\n");
        printf("[1] - Pr�-ordem\n");
        printf("[2] - Em-ordem\n");
        printf("[3] - P�s-ordem\n");
        printf("[4] - Largura\n");
        printf("[5] - Voltar\n");
        printf("[6] - Sair\n\n");
        printf("Op��o: ");
        scanf("%d", &opc);

        switch(opc){

            case 1:
                printf("\nPr�-ordem: ");
                ImprimePreOrdem(a);
                printf("\n");
                break;
            case 2:
                printf("\nEm-ordem: ");
                ImprimeEmOrdem(a);
                printf("\n");
                break;
            case 3:
                printf("\nP�s-ordem: ");
                ImprimePosOrdem(a);
                printf("\n");
                break;
            case 4:
            	printf("\nLargura: \n");
            	ImprimirLargura(a);
            	printf("\n");
                break;
            case 5:
            	break;
            case 6:
                exit(0);
                break;
            default:
                printf("Op��o inv�lida, tente novamente.\n");
                Pausa();
                break;
        }
        break;
    }

}

void Menu(arvore *a){

    int opc = 0, info = 0, cheia = 0;
    char nome_arquivo[20];
    FILE *arq;

    while(opc != 10){

		printf("\n");
        printf("[1] - Ler uma �rvore de um arquivo.\n");
        printf("[2] - Imprimir �rvore.\n");
        printf("[3] - Verificar se um elemento existe na �rvore.\n");
        printf("[4] - Contar o n�mero de elementos na �rvore.\n");
        printf("[5] - Imprimir os n�s folhas da �rvore.\n");
        printf("[6] - Verificar se uma �rvore est� balanceada.\n");
        printf("[7] - Verificar se uma �rvore � cheia.\n");
        printf("[8] - Imprimir o n�vel de um n�.\n");
        printf("[9] - Sair.\n\n");
		printf("Op��o: ");
		scanf("%d", &opc);
		printf("\n");        

        switch(opc){

            case 1:

                printf("Digite o nome do arquivo: ");
                scanf("%s", nome_arquivo);
                arq = fopen(nome_arquivo, "rt");
                a = LerArvore(a,arq);
                fclose(arq);
                printf("Arquivo lido.\n");
                Pausa();
                break;

            case 2:

                MenuDeImpressao(a);
                break;

            case 3:

                printf("Digite o valor a ser procurado: ");
                scanf("%d", &info);
                if(Existe(a, info))
                    printf("\nExiste!\n");
                else
                    printf("\nN�o existe!\n");
                //Pausa();
                break;

            case 4:

                printf("N�mero de elementos na �rvore: %d\n", Contador(a));
                //Pausa();
                break;

            case 5:
                printf("N�s folhas: ");
                ImprimirNoFolha(a);
                printf("\n");
                //Pausa();
                break;
                
            case 6:
                if(ArvoreBalanceada(a))
                    printf("�rvore balanceada!\n");
                else
                    printf("�rvore n�o balanceada!\n");
            	break;
            	
            case 7:
            	cheia=ArvoreCheia(a);
            	if(cheia==1){
            		printf("A �rvore � cheia.\n");
				}else{
					printf("A �rvore n�o � cheia.\n");
				}
				//Pausa();
            	break;
            	
            case 8:
            	break;

            case 9:
                exit(0);
                break;

            default:
                printf("Op��o inv�lida, digite novamente\n");
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

	setlocale(LC_ALL, "Portuguese");
    arvore *a = NULL;
    FILE *arq;

    Menu(a);

    a = DestruirArvore(a);

    return 0;

}
