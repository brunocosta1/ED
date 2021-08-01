// Alunos: Bruno Costa dos Passos, Kamile Novaes, Raphael Kazuhiro Yoshiki

#include <stdio.h>
#include <stdlib.h>

void ImprimirCombinacoes(int *comb, int pos, int n, int *aux){

  int soma = 0;
  if (pos == n) {
    for (int i = 0; i < n; i++) {
      soma += comb[i];
    }
    if (soma % 2 == 0) {
      for (int i = 0; i < n; i++) {
        printf("%d ", comb[i]);
      }
      printf("\n");
    }
  } else {
    for (int i = 0; i < 4; i++) {
      comb[pos] = aux[i];
      ImprimirCombinacoes(comb, pos+1, n, aux);
    }
  }
}

int main() {
  int n;
  int pos = 0;
  int comb[4];
  int aux[4] = {15, 31, 55, 44};

  printf("Insira o tamanho N das combinacoes: ");
  scanf("%d", &n);

  ImprimirCombinacoes(comb, pos, n, aux);

  return 0;
}
