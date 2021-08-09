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

void ImprimirGrafo(lista **g, int n){

	int i;
	printf("\nGrafo: ");
	for(i=1;i<=n;i++){

		printf("\n\t %d: ", i);
		ImprimirLista(g[i]);
	}
}


int contEntrada(lista *l, int x, int cont) {
  if (l != NULL) {
    if (l->destino == x) {
      cont++;
    }
    cont = contEntrada(l->prox, x, cont);
  }
  return cont;
}

void entradaVertice(lista **g, int x, int n) {
  int ct = 0;
  for (size_t i = 1; i <= n; i++) {
    ct = ct + contEntrada(g[i], x, 0);
  }
  printf("Grau de entrada do vertice: %d\n", ct);
}

void saidaVertice(lista *l, int cont) {
  if (l != NULL) {
    cont++;
    saidaVertice(l->prox, cont);
  }
  else {
  printf("Grau de saida do vertice: %d\n", cont);
  }
}


int contSaida(lista *l, int n, int cont) {
  if (l != NULL) {
    cont++;
    cont = cont + contSaida(l->prox, n, 0);
  }
  return cont;
}

void grafoCompleto(lista **g, int n) {
  int temp;
  for (size_t i = 1; i <= n; i++) {
    temp = contSaida(g[i], n, 0);
    if (temp < n-1) {
      printf("O grafo nao esta completo.\n");
      break;
    }
    else if (i == n) {
      printf("O grafo esta completo.\n");
    }
  }
}


//Funções para impressão de caminhos (opção 6)
int existe(int *arr, int val, int n) {
  for (size_t i = 0; i < n; i++) {
    if (arr[i] == val) {
      return 1;
    }
  }
  return 0;
}

void caminhos(lista **g, int *arr, int n, int pos) {
  if (arr[pos - 1] == n) {
    putchar('\n');
    for (size_t i = 0; i < pos; i++) {
      if (i == 0) {
        printf("%d", arr[i]);
      }
      else {
        printf("->%d", arr[i]);
      }
    }
    putchar('\n');
  }
  else {
    lista *p = g[arr[pos - 1]];
    while (p != NULL) {
      if (!existe(arr, p->destino, pos)) {
        arr[pos] = p->destino;
        caminhos(g, arr, n, pos + 1);
      }
      p = p->prox;
    }
  }
}


//Funções para caminhos curtos/baratos (opções 7 e 8)
//INCOMPLETO
/*int caminhoCurto(lista *l, int ct, int toggle, int case) {
  if (l != NULL) {
    cont++;
    cont = contEntrada(l->prox, x, cont);
  }
  return cont;
}

int caminhoBarato()

void verifCaminho(lista **g, int arr*, int n, int pos, int toggle) {
  for (size_t i = 0; i < n; i++) {
    vet[0] = i;
    for (size_t j = 0; j < pos; j++) {

    }
  }
}*/


void menu(lista **g){

	int n=0, x=0;
	int origem=0, destino=0, arestas=0, custo=0;
	printf("Insira o tamanho do vetor: ");
	scanf("%d",&n);

	g=(lista**)malloc((n+1)*sizeof(lista*));
	inicializar(g,n);

  int *vet;

	while(x != 9){

		printf("\n[1] - Inserir uma aresta.\n");
		printf("[2] - Remover uma aresta.\n");
		printf("[3] - Imprimir grafo.\n");
		printf("[4] - Imprimir os graus de entrada e saida de um vertice.\n");
		printf("[5] - Verificar se um grafo eh completo.\n");
    printf("[6] - Imprimir os caminhos entre uma origem e um destino.\n");
    printf("[7] - Imprimir o caminho mais curto.\n");
    printf("[8] - Imprimir o caminho de menor custo.\n");
		printf("[9] - Sair.\n");

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
				ImprimirGrafo(g, n);
				printf("\n");
				break;

			case 4:
        printf("Insira o valor do vertice: ");
        scanf("%d", &origem);
        limpa_tela();
        entradaVertice(g, origem, n);
        saidaVertice(g[origem], 0);
				break;

			case 5:
        limpa_tela();
        grafoCompleto(g, n);
				break;

      case 6:
        vet = (int*)malloc(n*sizeof(int));
        putchar('\n');
        printf("Insira a origem: ");
        scanf("%d", &origem);
        vet[0] = origem;
        putchar('\n');
        printf("Insira o destino: ");
        scanf("%d", &destino);
        limpa_tela();
        caminhos(g, vet, destino, 1);
      	break;

      case 7:
        vet = (int*)malloc(n*sizeof(int));
      	break;

      case 8:
      	break;

      case 9:
        exit(0);
        break;

      default:
        limpa_tela();
        printf("Opcao invalida, tente novamente.\n");
        break;

		}
	}

}

int main(){

	lista **g=NULL;
	menu(g);

	return 0;
}



