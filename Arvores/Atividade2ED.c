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

//Função para contar a altura da árvore

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

    if(a==NULL)
    	return 1;
    else{

        int alturaDireita, alturaEsquerda;

        alturaEsquerda = Altura(a->esq) + 1;
        alturaDireita = Altura(a->dir) + 1;

        if(abs(alturaDireita - alturaEsquerda) > 1)
            return 0;
        else{
        
			int temp1 = ArvoreBalanceada(a->dir), temp2 = ArvoreBalanceada(a->esq);

            if(temp1 == 1 && temp2 == 1)
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

//Imprimir nivel de um no
void NivelNo(arvore *a, int num, int nivel) {

  if(a == NULL) {
      printf("Arvore vazia!\n");
  }
  else {
    if(a->info == num) {
        printf("\nNivel do no %d: %d\n", num, nivel);
    }
    if(a->esq != NULL) {
        NivelNo(a->esq, num, nivel + 1);
    }
    if(a->dir != NULL) {
        NivelNo(a->dir, num, nivel + 1);
    }
  }
}

//Função que verifica se a árvore é cheia

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

// Funções do menu

void MenuDeImpressao(arvore *a){

    int opc = 0;

    while(opc != 6){

        printf("\nDigite a forma de impressao: \n\n");
        printf("[1] - Pre-ordem\n");
        printf("[2] - Em-ordem\n");
        printf("[3] - Pos-ordem\n");
        printf("[4] - Largura\n");
        printf("[5] - Voltar\n");
        printf("[6] - Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &opc);

        switch(opc){

            case 1:
                Pausa();
                printf("\nPre-ordem: ");
                ImprimePreOrdem(a);
                printf("\n");
                break;
            case 2:
                Pausa();
                printf("\nEm-ordem: ");
                ImprimeEmOrdem(a);
                printf("\n");
                break;
            case 3:
                Pausa();
                printf("\nPos-ordem: ");
                ImprimePosOrdem(a);
                printf("\n");
                break;
            case 4:
                Pausa();
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
                Pausa();
                printf("Opcao invalida, tente novamente.\n");
                break;
        }
        break;
    }

}

void Menu(arvore *a){

    int opc = 0, info = 0, cheia = 0, nivel = 0;
    char nome_arquivo[20];
    FILE *arq = NULL;

    while(opc != 10){

		printf("\n");
        printf("[1] - Ler uma arvore de um arquivo.\n");
        printf("[2] - Imprimir arvore.\n");
        printf("[3] - Verificar se um elemento existe na arvore.\n");
        printf("[4] - Contar o numero de elementos na arvore.\n");
        printf("[5] - Imprimir os nos folhas da arvore.\n");
        printf("[6] - Verificar se uma arvore esta balanceada.\n");
        printf("[7] - Verificar se uma arvore e cheia.\n");
        printf("[8] - Imprimir o nivel de um no.\n");
        printf("[9] - Sair.\n\n");
		printf("Opcao: ");
		scanf("%d", &opc);
		printf("\n");

        switch(opc){

            case 1:

                Pausa();
                while(arq == NULL){

                    printf("Digite o nome do arquivo: ");
                    scanf("%s", nome_arquivo);
                    arq = fopen(nome_arquivo, "rt");

                    if(arq != NULL){

                        a = LerArvore(a,arq);
                        fclose(arq);
                        printf("Arquivo lido.\n");

                    }
                    else{
                        printf("Arquivo não foi lido, tente novamente\n");
                    }
                }
                break;

            case 2:

                Pausa();
                MenuDeImpressao(a);
                break;

            case 3:

                printf("Digite o valor a ser procurado: ");
                scanf("%d", &info);
                if(Existe(a, info))
                    printf("\nExiste!\n");
                else
                    printf("\nNão existe!\n");
                //Pausa();
                break;

            case 4:

                Pausa();
                printf("Numero de elementos na arvore: %d\n", Contador(a));
                break;

            case 5:
                Pausa();
                printf("Nos folhas: ");
                ImprimirNoFolha(a);
                printf("\n");
                break;

            case 6:
                Pausa();
                if(ArvoreBalanceada(a))
                    printf("Arvore balanceada!\n");
                else
                    printf("Arvore nao balanceada!\n");
            	break;

            case 7:
            	cheia=ArvoreCheia(a);
				Pausa();
            	if(cheia==1){
            		printf("A arvore e cheia.\n");
				}else{
					printf("A arvore nao e cheia.\n");
				}
            	break;

            case 8:
      			printf("Insira o valor do No qual deseja saber o nivel:\n");
      			scanf("%d", &info);

      			Pausa();

                if(Existe(a, info)) {
                    NivelNo(a, info, 0);
                }else{
                  printf("\nValor invalido!\n");
                }

            	break;

            case 9:
                exit(0);
                break;

            default:
                printf("Opçao invalida, digite novamente\n");
                Pausa();
                break;

        }

    }
}


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
