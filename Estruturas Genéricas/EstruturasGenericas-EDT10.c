// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct professores{
	
	int matricula;
	char nome[50];
	float salario;
	
}Professor;

typedef struct alunos{
	
	int matricula;
	char nome[50];
	char curso[50];
	int ano;
	
}Aluno;

typedef struct pessoas{
	
	int tipo;  // 1 para prof e 2 para alunos
	void *dados;
	struct pessoas *prox; 
	
}Pessoas;


Pessoas *insereInicio(Pessoas *p, void *dados, int tipo){
	
    Pessoas *no=(Pessoas*) malloc(sizeof(Pessoas));
    no->tipo = tipo;
    no->dados = dados;
    no->prox = p;


	return no;
}

Pessoas *Remove(Pessoas *p, int mat){
	
	if(p!=NULL){
		Pessoas *a;
		a=p->prox;
		
		if(p->tipo==1){
			Professor *b = (Professor*)p->dados;
     		 if (b->matricula == mat) {
     		 	free(p);
				return a;
			  }else
			  	p->prox=Remove(p->prox, mat);
			  
		}
		else if(p->tipo==2){
			Aluno *b = (Aluno*)p->dados;
     		 if (b->matricula == mat) {
     		 	free(p);
				return a;
			  }else
			  	p->prox=Remove(p->prox, mat);
		}
	}
	else
		return NULL;
	
}

void PesquisarPessoa(Pessoas *p, int mat){
	
	if(p!=NULL){
		
		if(p->tipo==1){
			Professor *a = (Professor*)p->dados;
			if(a->matricula==mat){
				printf("\nNome: %s\nOcupacao: Professor\nMatricula: %d\nSalario: %.2f", a->nome, a->matricula, a->salario );
			}
			else{
				PesquisarPessoa(p->prox, mat);
			}
		}
		else if(p->tipo==2){
			Aluno *b = (Aluno*)p->dados;
			if(b->matricula==mat){
				printf("\nNome: %s\nOcupacao: Aluno\nMatricula: %d\nCurso: %s\nAno de ingresso: %d\n", b->nome, b->matricula, b->curso, b->ano);
			}
			else{
				PesquisarPessoa(p->prox, mat);
			}
		}
	}
	else{
		printf("Nao encontrado.");
	}

}

int ContarAlunos(Pessoas *p, char curso[50]){
	
	if(p!=NULL){
		
		if(p->tipo==2){

			Aluno *a = (Aluno*)p->dados;

			if(strcmp(curso,a->curso)==0){
				return 1 + ContarAlunos(p->prox, curso);
			}
		}
		else{
			return ContarAlunos(p->prox, curso);
		}
	}else
        return 0;
}

void ProfSalarios(Pessoas *p, float salarioalto){
	
	if(p!=NULL){
		
		if(p->tipo==1){
			Professor *a = (Professor*)p->dados;
			if(a->salario>=salarioalto){
				printf("%s %d\n", a->nome, a->matricula);
			}
		}
		else{
			ProfSalarios(p->prox, salarioalto);
		}
	}
}

void menu(Pessoas *p){
	
	int x, y, mat;
	char curso[50];
	float salarioalto;
	
	while(x!=6){
		
		printf("[1] - Inserir uma pessoa na lista.\n");
		printf("[2] - Remover uma pessoa pela matricula.\n");
		printf("[3] - Buscar uma pessoa pela matricula.\n"); //imprimir se encontrar
		printf("[4] - Contar o numero de alunos de um curso.\n");
		printf("[5] - Imprimir os professores de maior salario.\n");
		printf("[6] - Sair.\n\n");
		printf("Opcao: ");
		scanf("%d", &x);
	
		switch(x){
		
			case 1:
				printf("\n1 - PROFESSOR\n2 - ALUNO\n");
				scanf("%d", &y);
                putc('\n', stdin);
			
				if(y==1){
					Professor *prof;
					prof=(Professor*)malloc(sizeof(Professor));
					printf("Matricula: ");
					scanf("%d", &prof->matricula);
                    putc('\n', stdin); 
					printf("Nome: ");
					scanf("%s", prof->nome);
					printf("Salario:");
					scanf("%f", &prof->salario);
                    putc('\n', stdin);
					p = insereInicio(p,prof,y);
				}
				else if(y==2){
					Aluno *aluno;
					aluno=(Aluno*)malloc(sizeof(Aluno));
					printf("Matricula: ");
					scanf("%d", &aluno->matricula);
                    putc('\n', stdin);
					printf("Nome: ");
					scanf("%s", aluno->nome);					
					printf("Curso: ");
					scanf("%s", aluno->curso);
					printf("Ano de ingresso: ");
                    scanf("%d", &aluno->ano);
					p=insereInicio(p,aluno,y);
				}
				else{
					printf("Nenhuma das opcoes disponiveis.");
				}
				break;
			
			case 2:
				printf("Digite a matricula: ");
				scanf("%d", &mat);
				p=Remove(p,mat);
				break;
				
			case 3:
				printf("Digite a matricula: ");
				scanf("%d", &mat);
                putc('\n', stdin);
				PesquisarPessoa(p,mat);
				break;
			
			case 4:
				printf("Digite o curso: ");
				scanf("%s", curso);
				printf("Alunos: %d\n", ContarAlunos(p,curso));
				break;
				
			case 5:
				salarioalto=4000;
				ProfSalarios(p,salarioalto);
				break;
			
			case 6:
				break;	
		}
	
	}
	
}

int main(){

	Pessoas *p = NULL;

	menu(p);


    return 0;
	
}







