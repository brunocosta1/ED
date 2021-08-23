#include "stdio.h"

typedef struct professores
{
    int matricula;
    char nome[50];
    float salario;
} Professores;

typedef struct alunos
{
    int matricula;
    char nome[50];
    char curso [20];
    int ingresso;
} Alunos;

typedef struct pessoa
{
    int tipo; //1 = Professor, 2 = Aluno
    void *dados; //Armazena professor ou aluno
} Pessoa;

void Inicializar(Pessoa *vet, int tam) {
  for (size_t i = 0; i < tam; i++) {
    vet[i].tipo = 0;
    vet[i].dados = NULL;
  }
}



void Inserir(Pessoa *vet, void *info, int tipo, int tam)
{
  for (size_t i = 0; i < tam; i++)
  {
    if (vet[i].info == 0 && vet[i].dados == NULL)
    {
      vet[i].tipo = tipo;
      vet[i].dados = info;
    }
  }
}

void Remover(Pessoa *vet, int mat, int tam)
{
  for (size_t i = 0; i < tam; i++)
  {
    if (vet[i].tipo == 1)
    {
      Professores *p = (Professores *)vet[i].dados;
      if (p->matricula == mat) {
        vet[i].tipo = 0;
        vet[i].dados = NULL;
        return;
      }
    }
    if (vet[i].tipo == 2)
    {
      Alunos *a = (Alunos *)vet[i].dados;
      if (a->matricula == mat) {
        vet[i].tipo = 0;
        vet[i].dados = NULL;
        return;
      }
    }
  }
  printf("Matricula nao encontrada.\n");
}

void PesquisarPessoa(Pessoa *vet, int mat, int tam)
{
    for (size_t i = 0; i < tam; i++)
    {
      if (vet[i].tipo == 1)
      {
        Professores *p = (Professores *)vet[i].dados;
        if (p->matricula == mat) {
          printf("\nNome: %s\nOcupacao: Professor\nMatricula: %d\nSalario: %.2f", p->nome, p->matricula, p->salario);
          return;
        }
      }
      if (vet[i].tipo == 2)
      {
        Alunos *a = (Alunos *)vet[i].dados;
        if (a->matricula == mat) {
          printf("\nNome: %s\nOcupacao: Aluno\nMatricula: %d\nCurso: %s\nAno de ingresso: %d\n", a->nome, a->matricula, a->curso, a->ingresso);
          return;
        }
      }
    }
    printf("Matricula nao encontrada.\n");
}


int main()
{
    int tam;
    scanf("%d", &tam);
    Pessoa vet[tam];

}
