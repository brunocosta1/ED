// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki 


#include <stdio.h>
#include <stdlib.h>

// Código para verificar qual sistema operacional está rodando

#ifdef __unix__
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
    #include <windows.h>
#endif



typedef struct lista {
	int info;
	struct lista *prox;
}Lista;

Lista *CriaLista(){

    return NULL;

}

Lista *CriaElemento(int valor){

    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = NULL;

    return novo;
}

Lista *InserirFinal(Lista *l, int x){
	
	if(l==NULL){
		Lista *no= CriaElemento(x);
		return no;
	}
	else{
		l->prox=InserirFinal(l->prox,x);
		return l;
	}
}

int SomaLista(Lista *l){
	
	if(l==NULL){
		return 0;
	}
	else{
		return l->info + SomaLista(l->prox);
	}
}

Lista *RemoveElemento(Lista *l, int x){

	if(l!=NULL){
		Lista *p;
		p=l->prox;
		
		if(l->info==x){
			free(l);
			return p;
		}
		else{
			l->prox=RemoveElemento(l->prox,x);
		}
	}
	else{
		return NULL;
	}
}

int Contador(Lista *l, int x){
	
	if(l==NULL){
		return 0;
	}
	else{

		if(l->info==x)
			return 1 + Contador(l->prox,x);
		else
			return Contador(l->prox,x);

	}
}

void ImprimirLista(Lista *l){
	
	if(l!=NULL){
		printf("[%d] ",l->info);
		ImprimirLista(l->prox);
	}
}

void Pausa(){

    #ifdef OS_Windows
        system("timeout 1");
        system("cls");
    #else
        system("sleep 1");
        system("clear");
    #endif

}

void Menu(Lista *l){

    int x = 0, y = 0;

	while(x!=6){
		
		printf("\n");
		printf("[1] - Inserir um elemento no final da lista.\n");
		printf("[2] - Somar todos os elementos da lista.\n");
		printf("[3] - Contar o numero de ocorrencias de um elemento.\n");
		printf("[4] - Remover um elemento.\n");
		printf("[5] - Imprimir lista.\n");
		printf("[6] - Sair.\n");
		printf("\n");
		printf("Opcao: ");
		scanf("%d", &x);
		
		switch(x){
			
			case 1:
				printf("\nDigite o elemento que deseja incluir: ");
				scanf("%d", &y);
				l = InserirFinal(l,y);
                printf("Inserindo...\n");
                Pausa();
				break;
				
			case 2:
                Pausa();
				printf("\nSoma dos elementos: %d\n", SomaLista(l));
				break;
				
			case 3:
				printf("\nQual elemento deseja contar? ");
				scanf("%d", &y);
				if(l==NULL){
					printf("\nLista vazia...\n");
                    Pausa();
				}
				else{
                    Pausa();
					printf("\nNumero de ocorrencias: %d\n", Contador(l,y));
				}
				break;
				
			case 4:
				if(l==NULL){
					printf("\nLista vazia...\n");
                    Pausa();
				}
				else{
					printf("\nQual elemento deseja remover? ");
					scanf("%d", &y);
					l=RemoveElemento(l,y);
                    printf("Removendo...\n");
                    Pausa();
				}
				break;
				
			case 5:
				printf("\n");
				if(l==NULL){
					printf("Lista vazia...\n");
                    Pausa();
				}
				else{
                    Pausa();
					ImprimirLista(l);
					printf("\n");
				}
				break;
            case 6:
                printf("Saindo...\n");
                Pausa();
                break;
            default:
                printf("Opção inválida, digite novamente.\n");
                Pausa();
                break;
		}
	}
}

int main(){
	
	Lista *l = CriaLista();

    Menu(l);
	
    return 0;
}

