// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include "stdio.h"
#include "stdlib.h"

void ImprimirCombinacoes(char *comb, int pos, int n, char *aux){
  int a = 0;
  if (pos == n) {
    for (size_t i = 0; i <= n; i++) {
      if (comb[i] == 'a') {
        a++;
      }
    }
    if (a > n/2) {
      for (size_t i = 0; i <= n; i++) {
        printf("%c ", comb[i]);
      }
      printf("\n");
    }
  } else {
    for (size_t i = 0; i <= 2; i++) {
      comb[pos] = aux[i];
      ImprimirCombinacoes(comb, pos+1, n, aux);
    }
  }
}

int main() {
  int n;
  int pos = 0;
  char comb[3];
  char aux[3] = {'a', 'e', 'i'};

  printf("Insira o tamanho N das combinacoes: ");
  scanf("%d", &n);

  ImprimirCombinacoes(comb, pos, n, aux);

  return 0;
}
