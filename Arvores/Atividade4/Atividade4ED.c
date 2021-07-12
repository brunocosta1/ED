// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct avl{

    int info;
    int FB;
    struct avl *esq;
    struct avl *dir;

}AVL;


// CÃ³digo para verificar qual sistema operacional estÃ¡ rodando.

#ifdef __unix__
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
    #include <windows.h>
#endif

// FunÃ§Ã£o para deixar o menu mais dinÃ¢mico.

void limpa_tela(){

    #ifdef OS_Windows
        system("timeout 1");
        system("cls");
    #else
        system("sleep 1");
        system("clear");
    #endif

}

//Retorna a Altura de uma Ã¡rvore ou sub-Ã¡rvore

int Altura(AVL *a){

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


//Função para criar um elemento da Árvore

AVL *CriaElemento(int info){

    AVL *nova = (AVL*)malloc(sizeof(AVL));
    nova->info = info;
    nova->dir = NULL;
    nova->esq= NULL;

    return nova;

}


// Funcoes para ler AVL a partir de um arquivo

void AjustarFB(AVL *a){

	if(a!=NULL){
		int he=Altura(a->esq);
		int hd=Altura(a->dir);
		a->FB=hd-he;

		AjustarFB(a->esq);
		AjustarFB(a->dir);
	}
}

AVL *LerArvore(AVL *a, FILE *arq){

    char c;
    int num;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    if(num == -1){
        fscanf(arq, "%c", &c);
        return NULL;
    }else{

        AVL *a = CriaElemento(num);
        a->esq = LerArvore(a,arq);
        a->dir = LerArvore(a,arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

AVL *LerAVL(AVL *a, FILE *arq){

	a=LerArvore(a,arq);
	AjustarFB(a);
	return a;
}


//Imprime os elementos de um determinado nivel

void ImprimirNivel(AVL *a, int cont, int nivel){

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


//Imprime as folhas menores que um valor X

void ImprimirMenor(AVL *a, int x){

	if (a != NULL) {
		if (a->info < x) {
    		if(a->esq==NULL && a->dir==NULL){
    			printf("%d ", a->info);
			}
			ImprimirMenor(a->esq, x);
    	  	ImprimirMenor(a->dir, x);
    	}
    else {
		ImprimirMenor(a->esq, x);
	}
  }
}


// FunÃ§Ãµes de impressÃ£o da Ã¡rvore

void ImprimePreOrdem(AVL *a){

    if(a != NULL){
        printf("%d ", a->info);
        ImprimePreOrdem(a->esq);
        ImprimePreOrdem(a->dir);
    }

}

void ImprimeEmOrdem(AVL *a){

    if(a != NULL){
        ImprimeEmOrdem(a->esq);
        printf("%d ", a->info);
        ImprimeEmOrdem(a->dir);
    }
}

void ImprimePosOrdem(AVL *a){

    if (a != NULL){
        ImprimePosOrdem(a->esq);
        ImprimePosOrdem(a->dir);
        printf("%d ", a->info);
    }

}

void ImprimirLargura(AVL *a){

	int i;
	int nivel=0;

	if(a!=NULL){
		for(i=1;i<=Altura(a);i++){
			ImprimirNivel(a,0,nivel++);
			printf("\n");
		}
	}
}


// Funcao que verifica se existe um elemento x na AVL ABB

int Existir(AVL *a, int x){

	if(a==NULL)
		return 0;
	else if(x==a->info)
		return 1;
	else if(x<a->info)
		return Existir(a->esq,x);
	else
		return Existir(a->dir,x);

}


//Funcao para imprimir o nivel do no

int NivelNo(AVL *a, int x){

	if(x==a->info){
		return 0;
	}
	else{
		if(x<a->info){
			return NivelNo(a->esq,x) + 1;
		}
		else{
			return NivelNo(a->dir,x) + 1;
		}
	}
}


//Rotação a esquerda simples

AVL *RotacaoEsqSimples(AVL *p){

	AVL *b = p->dir;
	p->dir = b->esq;
	b->esq = p;
	return b;
}

//Rotação a direita simples

AVL *RotacaoDirSimples(AVL *p){

	AVL *b = p->esq;
	p->esq = b->dir;
	b->dir = p;
	return b;
}


//Rotação a esquerda dupla

AVL *RotacaoEsqDupla(AVL *p){

	p->dir = RotacaoDirSimples(p->dir);
	p = RotacaoEsqSimples(p);
	return p;
}

//Rotação a direita dupla

AVL *RotacaoDirDupla(AVL *p){

	p->esq = RotacaoEsqSimples(p->esq);
	p = RotacaoDirSimples(p);
	return p;
}


// Rotação a esquerda geral

AVL *RotacaoEsq(AVL *p){

	int he = Altura(p->esq);
	int hd = Altura(p->dir);

	if (fabs(hd - he) > 1){
		AVL *b = p->dir;
		he = Altura(b->esq);
		hd = Altura(b->dir);

	if (he > hd)
		p = RotacaoEsqDupla(p);
	else
		p = RotacaoEsqSimples(p);
	}

	return p;
}



//Rotação a direita geral

AVL *RotacaoDir(AVL *p){

	int he = Altura(p->esq);
	int hd = Altura(p->dir);

	if (fabs(hd - he) > 1){
		AVL *b = p->esq;
		he = Altura(b->esq);
		hd = Altura(b->dir);
		if (hd > he)
			p = RotacaoDirDupla(p);
		else
			p = RotacaoDirSimples(p);

	}
	return p;
}


//Inserir na AVL AVL

AVL *Inserir(AVL *a, int x){

	if(a == NULL){
		a = (AVL*)malloc(sizeof(AVL));
		a->info = x;
		a->esq = NULL;
		a->dir = NULL;
	}
	else{
		if (x <= a->info){
			a->esq = Inserir(a->esq,x);
			a = RotacaoDir(a);
		}
		else{
			a->dir = Inserir(a->dir,x);
			a = RotacaoEsq(a);
		}
	}

	return a;
}


//Remover na AVL AVL

AVL *Remover(AVL *a, int x){

	if(a != NULL){
		if(a->info == x){
			if(a->esq == NULL && a->dir == NULL){
				free(a);
				return NULL;
			}

		else if(a->esq == NULL || a->dir == NULL){
			AVL *aux;  if(a->esq == NULL)
			aux = a->dir;
			else
				aux = a->esq;
			free(a);
			return aux;
			}
		else{
			AVL *maiorEsq = a->esq;
			while (maiorEsq->dir != NULL)
				maiorEsq = maiorEsq->dir;
			a->info = maiorEsq->info;
			a->esq = Remover(a->esq,a->info);
			a = RotacaoEsq(a);
		}
	}
	else if (x < a->info){
		a->esq = Remover(a->esq, x);
		a = RotacaoEsq(a);
	}
		else{
		a->dir = Remover(a->dir, x);
		a = RotacaoDir(a);
		}
	}

	return a;
}


// Funcoes do menu

void MenuDeImpressao(AVL *a){

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
                limpa_tela();
                printf("\nPre-ordem: ");
                ImprimePreOrdem(a);
                printf("\n");
                break;
            case 2:
                limpa_tela();
                printf("\nEm-ordem: ");
                ImprimeEmOrdem(a);
                printf("\n");
                break;
            case 3:
                limpa_tela();
                printf("\nPos-ordem: ");
                ImprimePosOrdem(a);
                printf("\n");
                break;
            case 4:
                limpa_tela();
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
                limpa_tela();
                printf("Opcao invalida, tente novamente.\n");
                break;
        }
        break;
    }

}

void Menu(AVL *a){

    int opc = 0, info = 0, nivel = 0;
    char nome_arquivo[20];
    FILE *arq = NULL;

    while(opc != 9){

		printf("\n");
        printf("[1] - Ler uma AVL de um arquivo.\n");
        printf("[2] - Imprimir AVL.\n");
        printf("[3] - Verificar se um elemento existe na AVL.\n");
        printf("[4] - Imprimir o nivel de um no x.\n");
        printf("[5] - Imprimir as folhas menores que um valor x.\n");
        printf("[6] - Inserir um no x na AVL.\n");
        printf("[7] - Remover um no x da AVL.\n");
        printf("[8] - Sair.\n\n");
		printf("Opcao: ");
		scanf("%d", &opc);
		printf("\n");

        switch(opc){

            case 1:

                while(arq == NULL){

                    printf("Digite o nome do arquivo: ");
                    scanf("%s", nome_arquivo);
                    arq = fopen(nome_arquivo, "rt");

                    if(arq != NULL){

                        a = LerAVL(a,arq);
                        fclose(arq);
                        printf("\nArquivo lido.\n");

                    }
                    else{
                        printf("Arquivo nao foi lido, tente novamente\n");
                    }
                }
                limpa_tela();
                break;

            case 2:

                limpa_tela();
                MenuDeImpressao(a);
                break;

            case 3:

                printf("Digite o valor a ser procurado: ");
                scanf("%d", &info);
                limpa_tela();
                if(Existir(a, info))
                    printf("\nExiste!\n");
                else
                    printf("\nNao existe!\n");
                break;

            case 4:
				printf("Digite o valor do no que deseja saber o nivel: ");
      			scanf("%d", &info);

      			limpa_tela();

                if(Existir(a, info)) {
                    nivel=NivelNo(a, info);
                    printf("\nNivel: %d \n", nivel);
                }else{
                  printf("\nValor invalido!\n");
                }
                break;

            case 5:
				printf("Digite o valor de x: ");
            	scanf("%d", &info);
            	limpa_tela();
            	printf("\nFolhas menores do que %d: ", info);
				ImprimirMenor(a,info);
				printf("\n");
                break;

            case 6:
            	printf("Digite o no que deseja inserir: ");
            	scanf("%d", &info);
            	a=Inserir(a,info);
                limpa_tela();
            	break;

            case 7:
                printf("Digite o no que deseja remover: ");
            	scanf("%d", &info);
            	a=Remover(a,info);
                limpa_tela();
            	break;

            case 8:
                exit(0);
                break;

            default:
                printf("Opcao invalida, digite novamente\n");
                limpa_tela();
                break;

        }

    }
}

// Funcao que destroi a AVL

AVL *DestruirAVL(AVL *a){

    if(a != NULL){
        a->esq = DestruirAVL(a->esq);
        a->dir = DestruirAVL(a->dir);
        free(a);
    }

    return NULL;

}


int main(){

    AVL *a = NULL;
    FILE *arq;

    Menu(a);

    a = DestruirAVL(a);

    return 0;

}


