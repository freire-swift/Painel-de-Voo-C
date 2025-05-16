#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum StatusVoo {
    estimado = 1,
    confirmado = 2,
    embarcando = 3,
    ultimaChamada = 4,
    decolado = 5,
    encerrado = 6,
    atrasado = 7,
    cancelado = 8
}

typedef struct{
    int hora;
    int minuto;
} Horario;

typedef struct Voo{
    int numeroVoo;
    char companhia[100];
    char destino[100];
    int portao;
    enum StatusVoo status;
    Horario horario;
    struct Voo *link;
} *ptr;