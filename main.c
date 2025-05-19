#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum StatusVoo
{
    estimado = 1,
    confirmado = 2,
    embarcando = 3,
    ultimaChamada = 4,
    decolado = 5,
    encerrado = 6,
    atrasado = 7,
    cancelado = 8
};

typedef struct
{
    int hora;
    int minuto;
} Horario;

typedef struct Voo
{
    int numeroVoo;
    char companhia[100];
    char destino[100];
    int portao;
    enum StatusVoo status;
    Horario horario;
    struct Voo *link;
} *ptr;

void removerNovaLinha(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

const char *statusParaString(enum StatusVoo status)
{
    switch (status)
    {
    case estimado:
        return "Estimado";
    case confirmado:
        return "Confirmado";
    case embarcando:
        return "Embarcando";
    case ultimaChamada:
        return "Ultima chamada";
    case decolado:
        return "Decolado";
    case encerrado:
        return "Encerrado";
    case atrasado:
        return "Atrasado";
    case cancelado:
        return "Cancelado";
    default:
        return "Desconhecido";
    }
}

void inserir(ptr *listaVoo)
{
    ptr temp = malloc(sizeof(struct Voo));
    if (!temp)
    {
        printf("Erro de alocação de memória.\n");
        return;
    }

    printf("\n\nInsira o número do voo em esquema de 4 casas 0000\n");
    scanf("%d", &temp->numeroVoo);
    getchar();

    printf("Insira a companhia aérea\n");
    fgets(temp->companhia, sizeof(temp->companhia), stdin);
    removerNovaLinha(temp->companhia);

    printf("Insira o destino do voo\n");
    fgets(temp->destino, sizeof(temp->destino), stdin);
    removerNovaLinha(temp->destino);

    printf("Insira o portão do voo em 2 casas 00\n");
    scanf("%d", &temp->portao);

    printf("Insira a hora do voo aperte enter, e então digite o minuto do voo\n");
    scanf("%d", &temp->horario.hora);
    scanf("%d", &temp->horario.minuto);

    printf("Insira o número equivalente do status do voo de acordo com a seguinte lista:\n");
    printf("1 - Estimado\n2 - Confirmado\n3 - Embarcando\n4 - Última chamada\n5 - Decolado\n6 - Encerrado\n7 - Atrasado\n8 - Cancelado\n");
    scanf("%d", (int *)&temp->status);
    getchar();

    if(temp->link != NULL){
        temp->link = *listaVoo;
        *listaVoo = temp;
    } else{
        temp->link = NULL;
        *listaVoo = temp;
    }
    

    printf("O voo %d foi adicionado\n\n", temp->numeroVoo);
}

int excluir(ptr *listaVoo)
{
    if (*listaVoo == NULL)
    {
        printf("A lista está vazia, não é possivel excluir um voo");
        return -1;
    }

    int vooSelecionado;
    printf("Digite o número do voo a ser excluído\n");
    scanf("%d", &vooSelecionado);

    ptr atual = *listaVoo;
    ptr anterior = NULL;

    while (atual != NULL && atual->numeroVoo != vooSelecionado)
    {
        anterior = atual;
        atual = atual->link;
    }

    if (atual == NULL)
    {
        printf("Voo não encontrado.\n");
        return -1;
    }

    if (anterior == NULL)
    {
        *listaVoo = atual->link;
    }
    else
    {
        anterior->link = atual->link;
    }

    free(atual);
    printf("O voo %d foi removido\n", vooSelecionado);
    return vooSelecionado;
}

int alterar(ptr *listaVoo)
{
    if (*listaVoo == NULL)
    {
        printf("A lista está vazia, não é possivel alterar um voo");
        return -1;
    }

    int vooSelecionado;
    printf("Digite o número do voo a ser alterado\n");
    scanf("%d", &vooSelecionado);

    ptr atual = *listaVoo;

    while (atual != NULL && atual->numeroVoo != vooSelecionado)
    {
        atual = atual->link;
    }

    if (atual == NULL)
    {
        printf("Voo não encontrado.\n");
        return -1;
    }

    int opcao;

    do
    {
        printf("\nAlteração - Menu\n");
        printf("1 - Alterar n° do voo\n");
        printf("2 - Alterar companhia do voo\n");
        printf("3 - Alterar destino do voo\n");
        printf("4 - Alterar portão do voo\n");
        printf("5 - Alterar horário do voo\n");
        printf("0 - Terminar alterações\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            printf("\n\nInsira o número do voo em esquema de 4 casas 0000\n");
            scanf("%d", &atual->numeroVoo);
            getchar();
            break;
        case 2:
            printf("Insira a companhia aérea\n");
            fgets(atual->companhia, sizeof(atual->companhia), stdin);
            removerNovaLinha(atual->companhia);
            break;
        case 3:
            printf("Insira o destino do voo\n");
            fgets(atual->destino, sizeof(atual->destino), stdin);
            removerNovaLinha(atual->destino);
            break;
        case 4:
            printf("Insira o portão do voo em 2 casas 00\n");
            scanf("%d", &atual->portao);
            getchar();
            break;
        case 5:
            printf("Insira a hora do voo aperte enter, e então digite o minuto do voo\n");
            scanf("%d", &atual->horario.hora);
            scanf("%d", &atual->horario.minuto);
            getchar();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    printf("O voo %d foi alterado\n", vooSelecionado);
    return vooSelecionado;
}

void exibir(ptr listaVoo)
{
    printf("\n\n=========================== PAINEL DE VOO AEROPORTO VMPERG ===========================\n");
    printf("|  VOO  |     COMPANHIA     |         DESTINO         | PT |  HORA  |     STATUS     |\n");
    printf("--------------------------------------------------------------------------------------\n");

    ptr temp = listaVoo;
    while (temp != NULL)
    {
        printf("| %04d  | %-17s | %-23s | %02d | %02d:%02d  | %-14s |\n",
               temp->numeroVoo,
               temp->companhia,
               temp->destino,
               temp->portao,
               temp->horario.hora,
               temp->horario.minuto,
               statusParaString(temp->status));
        temp = temp->link;
    }

    printf("======================================================================================\n");
}

int main()
{
    ptr listaVoo = NULL;
    int opcao;

    do
    {
        printf("\nPainel de Voo - Menu\n");
        printf("1 - Inserir voo\n");
        printf("2 - Alterar voo\n");
        printf("3 - Excluir voo\n");
        printf("4 - Exibir painel\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            inserir(&listaVoo);
            break;
        case 2:
            alterar(&listaVoo);
            break;
        case 3:
            excluir(&listaVoo);
            break;
        case 4:
            exibir(listaVoo);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    while (listaVoo != NULL)
    {
        ptr temp = listaVoo;
        listaVoo = listaVoo->link;
        free(temp);
    }

    return 0;
}