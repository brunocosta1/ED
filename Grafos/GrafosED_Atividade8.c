// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
    #include <windows.h>
#endif


void limpa_tela(){

    #ifdef OS_Windows
        system("timeout 1");
        system("cls");
    #else
        system("sleep 1");
        system("clear");
    #endif

}

typedef struct lista{
	
	int destino;
	int custo;
	struct lista *prox;
	
}lista;

void inicializar(lista **g, int n){
	
	int i;
	for(i=0;i<=n;i++){
		g[i]=NULL;
	}
}

lista *InserirLista(lista *l, int d, int c){
	
	lista *no =(lista*)malloc(sizeof(lista));
	no->destino=d;
	no->custo=c;
	no->prox=l;
	return no;
}

void InserirAresta(lista**g, int origem, int destino, int custo){
	
	g[origem]=InserirLista(g[origem],destino,custo);
}

lista *RemoverLista(lista *l, int destino, int custo){
    
	lista *aux;

    if(l!=NULL){
        if(l->destino == destino && l->custo==custo){
            aux = l;
            l=l->prox;
            free(aux);
            return l;
        }
        else{
           l->prox = RemoverLista(l->prox,destino,custo);
        }
    }
    else{
        return l;
    }
}

void RemoverAresta(lista **g, int origem, int destino, int custo){
	
    g[origem]=RemoverLista(g[origem],destino,custo);
}

void ImprimirLista(lista *l){
	
	if(l!=NULL){
		
		printf("- (%d,%d) ", l->destino, l->custo);
		ImprimirLista(l->prox);
	}
}

void ImprimirGrafo(lista **g,int n){
	
	int i;
	printf("\nGrafo: ");
	for(i=1;i<=n;i++){
		
		printf("\n\t %d: ", i);
		ImprimirLista(g[i]);
	}
}

void menu(lista **g){
	
	int n=0, x=0;
	int origem=0, destino=0, arestas=0, custo=0;
	printf("Qual o tamanho do vetor: ");
	scanf("%d",&n);
	
	g=(lista**)malloc((n+1)*sizeof(lista*));
	inicializar(g,n);
	
	while(x!=6){
		
		printf("\n[1] - Inserir uma aresta.\n");
		printf("[2] - Remover uma aresta.\n");
		printf("[3] - Imprimir grafo.\n");
		printf("[4] - Imprimir os graus de entrada e saida de um vertice.\n");
		printf("[5] - Verificar se um grafo eh completo.\n");
		printf("[6] - Sair.\n");
		
		printf("\nDigite a opcao: ");
		scanf("%d", &x);
		
		switch(x){
			
			case 1:
				printf("\nOrigem: ");
				scanf("%d", &origem);
				printf("Destino: ");
				scanf("%d", &destino);
				printf("Custo: ");
				scanf("%d", &custo);
				InserirAresta(g,origem,destino,custo);
				arestas++;
				limpa_tela();
				break;
			
			case 2:
				printf("\nOrigem: ");
				scanf("%d", &origem);
				printf("Destino: ");
				scanf("%d", &destino);
				printf("Custo: ");
				scanf("%d", &custo);
                RemoverAresta(g,origem,destino,custo);
                arestas--;
                limpa_tela();
				break;
			
			case 3:
				limpa_tela();
				ImprimirGrafo(g,n);
				printf("\n");
				break;
			
			case 4:
				break;
			
			case 5:
				break;
			
		}
	}
	
}

int main(){
	
	lista **g=NULL;
	menu(g);
	
	return 0;
}




