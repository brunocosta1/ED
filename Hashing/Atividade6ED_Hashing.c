// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 53 //Turma de 50 alunos, mas colocando o valor do tamanho em 53 para ficar com número primo

// Código para verificar qual sistema operacional está rodando.

#ifdef __unix__
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
    #include <windows.h>
#endif

// Função para deixar o menu mais dinâmico.

void limpa_tela(){

    #ifdef OS_Windows
        system("timeout 1");
        system("cls");
    #else
        system("sleep 1");
        system("clear");
    #endif

}
typedef struct registro{

    int mat;
    char nome[100];
    char curso[50];
    int disponibilidade;

}registro;

int hash(int key);
void inicializa(char *nome_arq);
void inserir(char *nome_arq, registro aluno);
void imprimir(char *nome_arq, int mat);
int acha_pos(char *nome_arq, int mat);
void menu(char *nome_arq);

int main(){

    /*char nome_arq[10];*/
    /*printf("Digite o nome do arquivo que deseja inicializar: ");*/
    /*scanf("%s", nome_arq);*/
    /*scanf("");*/

    inicializa("registro");
    limpa_tela();

    menu("registro");

    return 0;

}

void menu(char *nome_arq){

    int opc = 0;
    int mat_temp;
    registro aluno_temp;


    while(opc != 4){

        printf("[0] - Inserir novo aluno\n");
        printf("[1] - Imprimir informações de um aluno\n");
        printf("[2] - Imprimir a tabela de dispersão\n");
        printf("[3] - Sair\n\n");

        printf("Opção: ");
        scanf("%d", &opc);
        scanf("");
        printf("\n");

        switch(opc){
            
            case 0:
                printf("Digite o nome do aluno: ");
                scanf("%s", aluno_temp.nome);
                printf("\n");

                printf("Digite o nome do curso do aluno: ");
                scanf("%s", aluno_temp.curso);
                printf("\n");

                printf("Digite o a matrícula do aluno: ");
                scanf("%d", &aluno_temp.mat);
                scanf("");
                printf("\n");

                inserir(nome_arq, aluno_temp);
                limpa_tela();

                break;

            case 1:
                printf("Digite a matrícula: ");
                scanf("");
                scanf("%d", &mat_temp);

                imprimir(nome_arq, mat_temp);

                break;

            case 2:
                break;

            case 3:
                break;

            default:
                break;
        }



    }

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
void imprimir(char *nome_arq, int mat){

    int pos = acha_pos(nome_arq, mat);

    FILE *arq = fopen(nome_arq, "rb");

    registro a;

    fseek(arq, pos*sizeof(registro), SEEK_SET);

    if(fread(&a, sizeof(registro), 1, arq) == 1){

        printf("Nome: %s\n", a.nome);
        printf("Curso: %s\n", a.curso);
        printf("Matrícula: %d\n", a.mat);

    }


    fclose(arq);

}

void inserir(char *nome_arq, registro aluno){

    int pos = acha_pos(nome_arq, aluno.mat);

    FILE *arq = fopen(nome_arq, "r+b");

    registro a;

    aluno.disponibilidade = 0;

    fseek(arq, pos*sizeof(registro), SEEK_SET);
    fwrite(&aluno, sizeof(registro), 1, arq);

    fclose(arq);

}

int acha_pos(char *nome_arq, int mat){

    int pos = hash(mat);

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



