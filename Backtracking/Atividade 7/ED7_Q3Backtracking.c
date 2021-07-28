// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdlib.h>
#include <stdio.h>

void imprime(int *qtd, int *moedas)
{
	int i;
	
	for(i=0;i<=4;i++){
		
		if(qtd[i]!=0){ //imprime só quando existe moedas de algum valor
			printf("- %d moedas de %d ", qtd[i], moedas[i]);
		}
	}
	printf("-");
}

void CombMoedas(int *qtd, int *moedas, int pos, int valor)
{
        int i, y, soma;

        if(pos==4)
        {
            soma = qtd[4]*50+qtd[3]*25+qtd[2]*10+qtd[1]*5+qtd[0]*1; //multiplica a quantidade de moedas com seus valores
            if(soma==valor)
            {
              imprime(qtd,moedas);
              printf("\n");
            }
        }
        else
        {
          y=valor/moedas[pos]; //o resultado da divisao do valor pela moeda é a quantidade de moedas para aquele valor

          for(i=0;i<=y;i++)
          {
            qtd[pos]=i; //atribui as quantidades no vetor auxiliar
            CombMoedas(qtd,moedas, pos+1, valor);
          }
        }
}

int main(){
	
	int vet[]={0,0,0,0,0}; //vetor auxiliar pra guardar a quantidade de moedas
	int vetMoedas[]={1,5,10,25,50};
	int pos=0, valor;
	
		printf("Digite o valor em centavos: ");
        scanf("%d", &valor);
        printf("\nCombinacoes: \n\n");
        CombMoedas(vet,vetMoedas,pos,valor);
            
	return 0;           
}
