#ifndef FILA_H
#define FILA_H

typedef struct fila *Fila;

Fila Inicializar();
Fila Destruir(Fila f);
void Inserir(Fila f, int x);
void Remove(Fila f);
void Imprimir(Fila f);
void Menu();


#endif
