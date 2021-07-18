// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 53 //Turma de 50 alunos, mas colocando o valor do tamanho em 53 para ficar com número primo

typedef struct registro{

    int mat;
    char nome[100];
    char curso[50];
    int disponibilidade;

}registro;

int hash(int key);
void inicializa(char *nome_arq);
void inserir(char *nome_arq, registro aluno);
int acha_pos(char *nome_arq, int mat);
void menu();

int main(){

    return 0;

}

int hash(int key){

    return key % TAM;

}

void inicializa(char *nome_arq){

    FILE *arq = fopen(nome_arq, "wb");
    registro a;

    a.disponibilidade = 1;

    for(int i = 0; i < TAM; i++)
        fwrite(&a, sizeof(registro), 1, arq);

    fclose(arq);

}

void inserir(char *nome_arq, registro aluno){

    int pos = acha_pos(nome_arq, aluno.mat);

    FILE *arq = fopen(nome_arq, "r+b");

    registro a;

    strcpy(a.nome, aluno.nome);
    strcpy(a.curso, aluno.curso);
    a.mat = aluno.mat;
    a.disponibilidade = 0;

    fseek(arq, pos*sizeof(registro), SEEK_SET);
    fwrite(&a, sizeof(registro), 1, arq);

    fclose(arq);

}

int acha_pos(char *nome_arq, int mat){

    int resto = mat % 1000;
    int pos = hash(resto);

    registro a;

    FILE *arq = fopen(nome_arq, "rb");

    fseek(arq, pos*sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);

    while(a.disponibilidade == 0){

        pos = (pos+1) % TAM;
        fseek(arq, pos*sizeof(registro), SEEK_SET);
        fread(&a, sizeof(registro), 1, arq);

    }

    fclose(arq);
    return pos;

}

void menu(){

    int opc = 0;

    while(opc != 4){

        printf("[0] - Inserir novo aluno\n");
        printf("[1] - Imprimir informações de um aluno\n");
        printf("[2] - Imprimir a tabela de dispersão\n");
        printf("[3] - Sair\n\n");

        printf("Opção: ");
        scanf("%d", &opc);
        printf("\n");

        switch(opc){
            

        }



    }

}

