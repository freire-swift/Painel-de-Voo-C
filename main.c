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
    char companhia[21];
    char destino[31];  
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

// Função auxiliar para limpar o buffer do teclado
void limparEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int contemAcentuacao(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)str[i];
        if (c >= 128)
        {
            return 1;
        }
    }
    return 0;
}

// Função auxiliar para ler string limitada e obrigar o usuário a digitar até o tamanho permitido
void lerStringLimitada(char *dest, int max)
{
    int valido = 0;
    while (!valido)
    {
        if (fgets(dest, max, stdin) != NULL)
        {
            removerNovaLinha(dest);
            // Se o texto foi cortado, limpar o buffer e pedir novamente
            if (strlen(dest) == max - 1 && dest[max - 2] != '\n')
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                printf("Atenção: o texto excedeu o limite de %d caracteres. Digite novamente:\n", max - 1);
            }
            else if (contemAcentuacao(dest))
            {
                printf("Atenção: não utilize acentuação. Digite novamente apenas com letras sem acento.\n");
            }
            else
            {
                valido = 1;
            }
        }
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

    int ok = 0;
    do
    {
        printf("\n\nInsira o número do voo em 4 dígitos (ex: 1234): ");
        ok = scanf("%d", &temp->numeroVoo);
        limparEntrada();
        if (ok != 1 || temp->numeroVoo < 1 || temp->numeroVoo > 9999)
            printf("Valor inválido! Digite um número entre 1 e 9999.\n");
    } while (ok != 1 || temp->numeroVoo < 1 || temp->numeroVoo > 9999);

    printf("Insira a companhia aérea (máx. 20 caracteres): ");
    lerStringLimitada(temp->companhia, sizeof(temp->companhia));

    printf("Insira o destino do voo (máx. 30 caracteres): ");
    lerStringLimitada(temp->destino, sizeof(temp->destino));

    do
    {
        printf("Insira o portão do voo em 2 dígitos (ex: 12): ");
        ok = scanf("%d", &temp->portao);
        limparEntrada();
        if (ok != 1 || temp->portao < 1 || temp->portao > 99)
            printf("Valor inválido! Digite um número entre 1 e 99.\n");
    } while (ok != 1 || temp->portao < 1 || temp->portao > 99);

    do
    {
        printf("Digite a HORA do voo (ex: 21): ");
        ok = scanf("%d", &temp->horario.hora);
        limparEntrada();
        if (ok != 1 || temp->horario.hora < 0 || temp->horario.hora > 23)
            printf("Valor inválido! Digite uma hora entre 0 e 23.\n");
    } while (ok != 1 || temp->horario.hora < 0 || temp->horario.hora > 23);

    do
    {
        printf("Digite o MINUTO do voo (ex: 30): ");
        ok = scanf("%d", &temp->horario.minuto);
        limparEntrada();
        if (ok != 1 || temp->horario.minuto < 0 || temp->horario.minuto > 59)
            printf("Valor inválido! Digite um minuto entre 0 e 59.\n");
    } while (ok != 1 || temp->horario.minuto < 0 || temp->horario.minuto > 59);

    do
    {
        printf("\nSeguindo o menu abaixo, insira o número referente ao status do voo: \n");
        printf("1 - Estimado\n2 - Confirmado\n3 - Embarcando\n4 - Última chamada\n5 - Decolado\n6 - Encerrado\n7 - Atrasado\n8 - Cancelado\n");
        ok = scanf("%d", (int *)&temp->status);
        limparEntrada();
        if (ok != 1 || temp->status < 1 || temp->status > 8)
            printf("Valor inválido! Digite um número entre 1 e 8.\n");
    } while (ok != 1 || temp->status < 1 || temp->status > 8);

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

    int vooSelecionado, ok = 0;
    do
    {
        printf("Digite o número do voo a ser alterado:\n");
        ok = scanf("%d", &vooSelecionado);
        limparEntrada();
        if (ok != 1 || vooSelecionado < 1 || vooSelecionado > 9999)
            printf("Valor inválido! Digite um número entre 1 e 9999.\n");
    } while (ok != 1 || vooSelecionado < 1 || vooSelecionado > 9999);

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
        ok = scanf("%d", &opcao);
        limparEntrada();
        if (ok != 1)
            opcao = -1;

        switch (opcao)
        {
        case 1:
            do
            {
                printf("\n\nInsira o número do voo em 4 dígitos (ex: 1234): ");
                ok = scanf("%d", &atual->numeroVoo);
                limparEntrada();
                if (ok != 1 || atual->numeroVoo < 1 || atual->numeroVoo > 9999)
                    printf("Valor inválido! Digite um número entre 1 e 9999.\n");
            } while (ok != 1 || atual->numeroVoo < 1 || atual->numeroVoo > 9999);
            break;
        case 2:
            printf("Insira a companhia aérea (máx. 20 caracteres): ");
            lerStringLimitada(atual->companhia, sizeof(atual->companhia));
            break;
        case 3:
            printf("Insira o destino do voo (máx. 30 caracteres): ");
            lerStringLimitada(atual->destino, sizeof(atual->destino));
            break;
        case 4:
            do
            {
                printf("Insira o portão do voo em 2 dígitos (ex: 12): ");
                ok = scanf("%d", &atual->portao);
                limparEntrada();
                if (ok != 1 || atual->portao < 1 || atual->portao > 99)
                    printf("Valor inválido! Digite um número entre 1 e 99.\n");
            } while (ok != 1 || atual->portao < 1 || atual->portao > 99);
            break;
        case 5:
        {
            int novaHora, novoMinuto;
            do
            {
                printf("Digite a HORA do voo (ex: 21): ");
                ok = scanf("%d", &novaHora);
                limparEntrada();
                if (ok != 1 || novaHora < 0 || novaHora > 23)
                    printf("Valor inválido! Digite uma hora entre 0 e 23.\n");
            } while (ok != 1 || novaHora < 0 || novaHora > 23);
            do
            {
                printf("Digite o MINUTO do voo (ex: 30): ");
                ok = scanf("%d", &novoMinuto);
                limparEntrada();
                if (ok != 1 || novoMinuto < 0 || novoMinuto > 59)
                    printf("Valor inválido! Digite um minuto entre 0 e 59.\n");
            } while (ok != 1 || novoMinuto < 0 || novoMinuto > 59);

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
        }
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

    int vooSelecionado, ok = 0;
    do
    {
        printf("Digite o número do voo a ter o status alterado:\n");
        ok = scanf("%d", &vooSelecionado);
        limparEntrada();
        if (ok != 1 || vooSelecionado < 1 || vooSelecionado > 9999)
            printf("Valor inválido! Digite um número entre 1 e 9999.\n");
    } while (ok != 1 || vooSelecionado < 1 || vooSelecionado > 9999);

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

    do
    {
        printf("Seguindo o menu abaixo, insira o número referente ao status do voo: \n");
        printf("1 - Estimado\n2 - Confirmado\n3 - Embarcando\n4 - Última chamada\n5 - Decolado\n6 - Encerrado\n7 - Atrasado\n8 - Cancelado\n");
        ok = scanf("%d", (int *)&atual->status);
        limparEntrada();
        if (ok != 1 || atual->status < 1 || atual->status > 8)
            printf("Valor inválido! Digite um número entre 1 e 8.\n");
    } while (ok != 1 || atual->status < 1 || atual->status > 8);

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

    int vooSelecionado, ok = 0;
    do
    {
        printf("Digite o número do voo a ser excluído:\n");
        ok = scanf("%d", &vooSelecionado);
        limparEntrada();
        if (ok != 1 || vooSelecionado < 1 || vooSelecionado > 9999)
            printf("Valor inválido! Digite um número entre 1 e 9999.\n");
    } while (ok != 1 || vooSelecionado < 1 || vooSelecionado > 9999);

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
    printf("\n\n");
    printf("================================================================================================\n");
    printf("================================= PAINEL DE VOO AEROPORTO VMPERG ===============================\n");
    printf("================================================================================================\n");
    printf("|  VOO  |      COMPANHIA       |            DESTINO             | PT |  HORA  |     STATUS     |\n");
    printf("------------------------------------------------------------------------------------------------\n");

    ptr temp = listaVoo;
    while (temp != NULL)
    {
        int comp_len = strlen(temp->companhia);
        int dest_len = strlen(temp->destino);
        int comp_pad_left = (22 - comp_len) / 2;
        int comp_pad_right = 22 - comp_len - comp_pad_left;
        int dest_pad_left = (32 - dest_len) / 2;
        int dest_pad_right = 32 - dest_len - dest_pad_left;

        // Centraliza o status
        const char *status = statusParaString(temp->status);
        int status_len = strlen(status);
        int status_pad_left = (16 - status_len) / 2;
        int status_pad_right = 16 - status_len - status_pad_left;

        printf("| %4d  |%*s%-*s%*s|%*s%-*s%*s| %2d | %02d:%02d  |%*s%-*s%*s|\n",
               temp->numeroVoo,
               comp_pad_left, "", comp_len, temp->companhia, comp_pad_right, "",
               dest_pad_left, "", dest_len, temp->destino, dest_pad_right, "",
               temp->portao,
               temp->horario.hora,
               temp->horario.minuto,
               status_pad_left, "", status_len, status, status_pad_right, "");
        temp = temp->link;
    }

    printf("================================================================================================\n");
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    ptr listaVoo = NULL;
    int opcao, ok = 0;

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
        ok = scanf("%d", &opcao);
        limparEntrada();
        if (ok != 1)
            opcao = -1;

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