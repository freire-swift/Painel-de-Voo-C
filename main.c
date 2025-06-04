#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

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

    printf("\n\nInsira o número do voo em 4 dígitos (ex: 1234): ");
    scanf("%d", &temp->numeroVoo);
    getchar();

    printf("Insira a companhia aérea: ");
    fgets(temp->companhia, sizeof(temp->companhia), stdin);
    removerNovaLinha(temp->companhia);

    printf("Insira o destino do voo: ");
    fgets(temp->destino, sizeof(temp->destino), stdin);
    removerNovaLinha(temp->destino);

    printf("Insira o portão do voo em 2 dígitos (ex: 12): ");
    scanf("%d", &temp->portao);

    printf("Digite a HORA do voo (ex: 21), aperte Enter e, em seguida, digite o MINUTO do voo (ex: 30): \n");
    scanf("%d", &temp->horario.hora);
    scanf("%d", &temp->horario.minuto);

    printf("\nSeguindo o menu abaixo, insira o número referente ao status do voo: \n");
    printf("1 - Estimado\n2 - Confirmado\n3 - Embarcando\n4 - Última chamada\n5 - Decolado\n6 - Encerrado\n7 - Atrasado\n8 - Cancelado\n");
    scanf("%d", (int *)&temp->status);
    getchar();

    ptr atual = *listaVoo, anterior = NULL;
    while (atual != NULL)
    {
        if (temp->horario.hora < atual->horario.hora || (temp->horario.hora == atual->horario.hora && temp->horario.minuto < atual->horario.minuto))
        {
            break;
        }

        anterior = atual;
        atual = atual->link;
    }

    if (anterior == NULL)
    {
        temp->link = *listaVoo;
        *listaVoo = temp;
    }
    else
    {
        temp->link = atual;
        anterior->link = temp;
    }

    printf("\nO voo %d foi adicionado.\n\n", temp->numeroVoo);
}

int alterar(ptr *listaVoo)
{
    if (*listaVoo == NULL)
    {
        printf("A lista está vazia, não é possível alterar um voo.\n");
        return -1;
    }

    int vooSelecionado;
    printf("Digite o número do voo a ser alterado:\n");
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
        printf("1 - Alterar número do voo\n");
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
            printf("\n\nInsira o número do voo em 4 dígitos (ex: 1234): ");
            scanf("%d", &atual->numeroVoo);
            getchar();
            break;
        case 2:
            printf("Insira a companhia aérea: ");
            fgets(atual->companhia, sizeof(atual->companhia), stdin);
            removerNovaLinha(atual->companhia);
            break;
        case 3:
            printf("Insira o destino do voo: ");
            fgets(atual->destino, sizeof(atual->destino), stdin);
            removerNovaLinha(atual->destino);
            break;
        case 4:
            printf("Insira o portão do voo em 2 dígitos (ex: 12): ");
            scanf("%d", &atual->portao);
            getchar();
            break;
        case 5:
            printf("Digite a HORA do voo (ex: 21), aperte Enter e, em seguida, digite o MINUTO do voo (ex: 30): \n");
            int novaHora, novoMinuto;
            scanf("%d", &novaHora);
            scanf("%d", &novoMinuto);
            getchar();

            if (*listaVoo == atual)
            {
                *listaVoo = atual->link;
            }
            else
            {
                ptr anterior = *listaVoo;
                while (anterior->link != atual)
                {
                    anterior = anterior->link;
                }
                anterior->link = atual->link;
            }
            atual->horario.hora = novaHora;
            atual->horario.minuto = novoMinuto;

            ptr anterior = NULL, cursor = *listaVoo;
            while (cursor != NULL)
            {
                if (atual->horario.hora < cursor->horario.hora || (atual->horario.hora == cursor->horario.hora && atual->horario.minuto < cursor->horario.minuto))
                {
                    break;
                }
                anterior = cursor;
                cursor = cursor->link;
            }

            if (anterior == NULL)
            {
                atual->link = *listaVoo;
                *listaVoo = atual;
            }
            else
            {
                atual->link = cursor;
                anterior->link = atual;
            }
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    printf("O voo %d foi alterado.\n", vooSelecionado);
    return vooSelecionado;
}

int alterarStatus(ptr *listaVoo)
{
    if (*listaVoo == NULL)
    {
        printf("A lista está vazia, não é possível alterar o status de um voo.\n");
        return -1;
    }

    int vooSelecionado;
    printf("Digite o número do voo a ter o status alterado:\n");
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

    printf("Seguindo o menu abaixo, insira o número referente ao status do voo: \n");
    printf("1 - Estimado\n2 - Confirmado\n3 - Embarcando\n4 - Última chamada\n5 - Decolado\n6 - Encerrado\n7 - Atrasado\n8 - Cancelado\n");
    scanf("%d", (int *)&atual->status);
    getchar();

    printf("O status do voo %d foi alterado.\n", vooSelecionado);
    return vooSelecionado;
}

int excluir(ptr *listaVoo)
{
    if (*listaVoo == NULL)
    {
        printf("A lista está vazia, não é possível excluir um voo.\n");
        return -1;
    }

    int vooSelecionado;
    printf("Digite o número do voo a ser excluído:\n");
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
    printf("O voo %d foi removido.\n", vooSelecionado);
    return vooSelecionado;
}

void exibir(ptr listaVoo)
{
    printf("\n\n--------------------------------------------------------------------------------------\n");
    printf("=========================== PAINEL DE VOO AEROPORTO VMPERG ===========================\n");
    printf("--------------------------------------------------------------------------------------\n");
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
    setlocale(LC_ALL, "pt_BR.UTF-8");
    ptr listaVoo = NULL;
    int opcao;

    do
    {
        printf("\nPainel de Voo - Menu\n");
        printf("1 - Inserir voo\n");
        printf("2 - Alterar voo\n");
        printf("3 - Alterar status do voo\n");
        printf("4 - Excluir voo\n");
        printf("5 - Exibir painel\n");
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
            alterarStatus(&listaVoo);
            break;
        case 4:
            excluir(&listaVoo);
            break;
        case 5:
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