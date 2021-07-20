// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int totalElementos=0;

// Codigo para verificar qual sistema operacional esta rodando.

#ifdef __unix__
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
    #include <windows.h>
#endif

// Funcao para deixar o menu mais dinamico.

void limpa_tela(){

    #ifdef OS_Windows
        system("timeout 1");
        system("cls");
    #else
        system("sleep 1");
        system("clear");
    #endif

}

//Funcoes auxiliares de indice

int indiceFilhoEsq(int x){
	
	int indice=(2*x)+1;
	
	if(x>=totalElementos || indice>=totalElementos){
		return -1;
	}
	else{
		return indice;
	}
}

int indiceFilhoDir(int x){
	
	int indice=(2*x)+2;
	
	if(x>=totalElementos || indice>=totalElementos){
		return -1;
	}
	else{
		return indice;
	}
}

int indicePai(int x){
	
	int indice=(int)floor((x-1)/2);
	
	if(x<=0 || x>= totalElementos){
		return -1;
	}
	else{
		return indice;
	}
}

//Inserir e ajustar a heap

void AjustarSubindo(int *heap, int pos){
	
	if(pos!=-1){
		int pai=indicePai(pos);
	
		if(pai!=-1){
			if(heap[pos]<heap[pai]){ //verifica se o no eh menor que o pai
				int aux=heap[pos];
				heap[pos]=heap[pai];
				heap[pai]=aux;
				AjustarSubindo(heap,pai);
			}
		}
	}
}

void Inserir(int *heap, int x){
	
	heap[totalElementos]=x;
	totalElementos++;
	
	AjustarSubindo(heap, totalElementos-1);
}


//Remover e ajustar a heap

int AjustarDescendo(int *heap, int pos){
	
	if(pos!=-1 && indiceFilhoEsq(pos)!=-1){
		
		//Descobre qual o menor filho
		int indiceMaiorFilho=indiceFilhoEsq(pos);
		
		if(indiceFilhoDir(pos)!=-1 && heap[indiceFilhoDir(pos)]<heap[indiceMaiorFilho]){
			indiceMaiorFilho=indiceFilhoDir(pos);
		}
		
		//Verifica se existe filho menor que o no atual
		if(heap[indiceMaiorFilho]<heap[pos]){
			int aux=heap[pos];
			heap[pos]=heap[indiceMaiorFilho];
			heap[indiceMaiorFilho]=aux;
			AjustarDescendo(heap,indiceMaiorFilho);
		}
	}
}

int Remover(int *heap){
	
	if(totalElementos==0){
		return -1;
	}
	else{
		int retorno=heap[0];
		heap[0]=heap[totalElementos-1];
		totalElementos--;
		AjustarDescendo(heap,0);
		return retorno;
	}
}


int main(){
	
	int N=0, x=0, y=0, i;
	int heap[N];
	int totalElementos=0;
	
	while(x!=4){
		
		printf("\n[1] - Inserir um elemento x na heap.\n");
		printf("[2] - Remover.\n");
		printf("[3] - Imprimir heap.\n");
		printf("[4] - Sair.\n");
		printf("\n");
		printf("Opcao: ");
		scanf("%d", &x);
		
		switch(x){
			
			case 1:
				
				printf("\nDigite o elemento que deseja incluir: ");
				scanf("%d", &y);
				Inserir(heap,y);
				N++;
				limpa_tela();
			break;
			
			case 2:
				
				limpa_tela();
				printf("\nElemento removido: %d \n",Remover(heap));
				N--;
			break;
				
			case 3:
				
				limpa_tela();
				printf("\n");
				for(i=0;i<=N-1;i++){
					printf("| %d ", heap[i]);
				}
				printf("| \n");
			break;	
				
		}
	}
	
}













