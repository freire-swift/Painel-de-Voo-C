#include <stdlib.h>
#include <stdio.h>
#include <struct.c>
#include <string.h>

void inserir(ptr *listaVoo){
    ptr temp = malloc(sizeof(struct Voo));

    printf("Insira o número do voo");
    scanf("%d", &temp->numeroVoo);
    getchar();

    printf("Insira a companhia aérea");
    fgets(temp->companhia, sizeof(temp->companhia), stdin);
    getchar();

    printf("Insira o destino do voo");
    fgets(temp->destino, sizeof(temp->destino), stdin);
    getchar();

    printf("Insira o portão do voo");
    scanf("%d", &temp->portao);
    getchar();

    printf("Insira a hora do voo aperte enter, e então digite o minuto do voo");
    scanf("%d", &temp->horario->hora);
    scanf("%d", &temp->horario->minuto);

    printf("Insira o número equivalente do status do voo de acordo com a seguinte lista:");
    printf("1 - Estimado\n2 - Confirmado\n3 - Embarcando\n4 - Última chamada\n5 - Decolado\n6 - Encerrado\n7 - Atrasado\n8 - Cancelado\n");
    scanf("%d", &temp->status);

    temp->link = *listaVoo;
    *listaVoo = temp;
}