#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

#define NUM_MAX_CADASTROS 1024

typedef struct
{
    int ocupado;
    char nome[256];
    int idade;
    char sexo;
    char matricula[12]
} Aluno;

Aluno vetor_alunos[NUM_MAX_CADASTROS];
int total_alunos = 0;

int tela_menu_opcoes();
void tela_cadastrar();
void tela_pesquisar();
void tela_remover();
void tela_editar();
int tela_sair();
void limpar();
void pausar();

int main()
{
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");

    int sair = 0;
    int opcao;

    for (int i = 0; i < NUM_MAX_CADASTROS; i++)
    {
        vetor_alunos[i].ocupado = 0;
    }

    while (1)
    {
        opcao = tela_menu_opcoes();

        switch (opcao)
        {
        case 1:
            tela_cadastrar();
            break;
        case 2:
            tela_pesquisar();
            break;
        case 3:
            tela_remover();
            break;
        case 4:
            tela_editar();
            break;
        case 5:
            sair = tela_sair();
            if (sair == 1)
            {
                exit(0);
            }
            break;
        default:
            printf("\nOpção Inválida!!! \n");
            pausar();
        }
    }

    limpar();
    printf("\nFim da execu��o do programa!\n");

    return 0;
}

int tela_menu_opcoes()
{
    int opcao;

    limpar();
    printf("Menu de Opções \n");
    printf("1 - Cadastrar \n");
    printf("2 - Pesquisar \n");
    printf("3 - Remover \n");
    printf("4 - Editar \n");
    printf("5 - Sair \n\n");

    printf("Escolha uma opçãoo: ");
    int erro = scanf("%d", &opcao);

    if (erro != 1)
    {
        fflush(stdin);
        opcao = -1;
    }

    return opcao;
}

void tela_cadastrar()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;

    char nome[256];
    int idade;
    char sexo, strSexo[3];
    char matricula[12];

    do
    {
        limpar();
        printf("1 - Cadastrar \n");

        if (total_alunos >= NUM_MAX_CADASTROS)
        {
            printf("\nErro: O cadastro já atingiu sua capacidade m�xima!\n");
            pausar();
            break;
        }

        do
        {
            erro = 0;

            printf("\nDigite o nome: ");
            scanf(" %255[^\n]", nome);
            fflush(stdin);

            if (strlen(nome) > 254)
            {
                erro = 1;
                printf("ERRO: O nome pode possuir no máximo 254 carracteres!\n");
            }
            if (strlen(nome) < 3)
            {
                erro = 1;
                printf("ERRO: O nome deve possuir pelo menos 3 (três) carracteres!\n");
            }

        } while (erro == 1);

        do
        {
            printf("\nDigite a idade: ");
            erro = scanf("%d", &idade);

            fflush(stdin);

            if (erro != 1)
            {
                printf("ERRO: Digite um valor inteiro válido!\n");
            }
            else if (idade < 1 || idade > 20)
            {
                erro = -1;
                printf("ERRO: A idade deve estar entre 1 e 20 anos!\n");
            }

        } while (erro != 1);

        do
        {
            erro = 0;

            printf("\nDigite o sexo (M / F): ");
            scanf(" %2[^\n]", strSexo);
            fflush(stdin);

            if (strlen(strSexo) == 1)
            {
                sexo = toupper(strSexo[0]);
            }
            else
            {
                erro = 1;
            }
            if (!(sexo == 'M' || sexo == 'F') || erro == 1)
            {
                erro = 1;
                printf("ERRO: São aceitos apenas os valores 'M' ou 'F'!\n");
            }

        } while (erro == 1);

        idxPesquisa = -1;

        for (int i = 0; i < NUM_MAX_CADASTROS; i++)
        {
            if (vetor_alunos[i].ocupado == 1)
            {
                if (strcmp(vetor_alunos[i].matricula, matricula) == 0)
                {
                    idxPesquisa = i;
                    break;
                }
            }
        }

        if (idxPesquisa != -1)
        {
            printf("\nErro: Não foi possível inserir os dados pois já existe um aluno com a mesma matrícula no cadastro:\v");

            printf("\nAluno com a mesma matrícula: \n");
            printf("Nome:    %s\n", vetor_alunos[idxPesquisa].nome);
            pausar();
        }
        else
        {
            for (int i = 0; i < NUM_MAX_CADASTROS; i++)
            {
                if (vetor_alunos[i].ocupado == 0)
                {
                    vetor_alunos[i].ocupado = 1;

                    strcpy(vetor_alunos[i].nome, nome);
                    strcpy(vetor_alunos[i].matricula, matricula);
                    vetor_alunos[i].idade = idade;
                    vetor_alunos[i].sexo = sexo;
                    total_alunos = total_alunos + 1;

                    printf("\nDados cadastrados com sucesso! \n");
                    pausar();

                    break;
                }
            }
        }

        do
        {

            printf("\nGostaria de cadastrar outra pessoa? (s/n): ");
            scanf(" %c", &ch);

            fflush(stdin);

            ch = toupper(ch);

        } while (!(ch == 'S' || ch == 'N'));

        if (ch == 'S')
        {
            continuar = 1;
        }
        else
        {
            continuar = 0;
        }

    } while (continuar == 1);
}

void tela_pesquisar()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;
    char matricula[12];

    do
    {

        pausar();
        printf("2 - Pesquisar \n");

        erro = 0;

        printf("\nDigite a matrícula: ");
        scanf(" %12[^\n]", matricula);
        fflush(stdin);

        int idxPesquisa = -1;
        for (int i = 0; i < NUM_MAX_CADASTROS; i++)
        {
            if (vetor_alunos[i].ocupado == 1)
            {
                if (strcmp(vetor_alunos[i].matricula, matricula) == 0)
                {
                    idxPesquisa = i;
                    break;
                }
            }
        }

        if (idxPesquisa != -1)
        {
            printf("\Aluno encontrado: \n");
            printf("Matrícula:     %s\n", vetor_alunos[idxPesquisa].matricula);
            printf("Nome:    %s\n", vetor_alunos[idxPesquisa].nome);
            printf("Idade:   %d\n", vetor_alunos[idxPesquisa].idade);
            printf("Sexo:    %c\n", vetor_alunos[idxPesquisa].sexo);
            pausar();
        }
        else
        {
            printf("\nNão foi encontrado um aluno com a matrícula informada!\n\n");
            pausar();
        }

        do
        {

            printf("\nGostaria de pesquisar outra pessoa?  (s/n): ");
            scanf(" %c", &ch);
            fflush(stdin);

            ch = toupper(ch);

        } while (!(ch == 'S' || ch == 'N'));

        if (ch == 'S')
        {
            continuar = 1;
        }
        else
        {
            continuar = 0;
        }

    } while (continuar == 1);
}

void tela_remover()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;
    char matricula[12];

    do
    {
        limpar();
        printf("3 - Remover \n\n");

        erro = 0;
        printf("\nDigite a matrícula: ");
        scanf(" %11[^\n]", matricula);
        fflush(stdin);

        idxPesquisa = -1;
        for (int i = 0; i < NUM_MAX_CADASTROS; i++)
        {
            if (vetor_alunos[i].ocupado == 1)
            {
                if (strcmp(vetor_alunos[i].matricula, matricula) == 0)
                {
                    total_alunos = total_alunos - 1;
                    vetor_alunos[i].ocupado = 0;
                    idxPesquisa = i;

                    break;
                }
            }
        }

        if (idxPesquisa != -1)
        {
            printf("\Aluno removido com sucesso!\n");
        }
        else
        {
            printf("\nNão foi possível remover a pessoa do cadastro!\n");
        }
        pausar();

        do
        {

            printf("\nGostaria de remover outra pessoa?  (s/n): ");
            scanf(" %c", &ch);

            fflush(stdin);

            ch = toupper(ch);

        } while (!(ch == 'S' || ch == 'N'));

        if (ch == 'S')
        {
            continuar = 1;
        }
        else
        {
            continuar = 0;
        }

    } while (continuar);
}

void tela_editar()
{
}

void tela_relatorio()
{
    limpar();
    printf("4 - Relatório \n\n");

    printf("Total de Alunos Cadastrados: %d\n\n", total_alunos);

    for (int i = 0; i < NUM_MAX_CADASTROS; i++)
    {
        if (vetor_alunos[i].ocupado == 1)
        {
            printf("Matrícula:     %s\n", vetor_alunos[i].matricula);
            printf("Nome:    %s\n", vetor_alunos[i].nome);
            printf("Idade:   %d\n", vetor_alunos[i].idade);
            printf("Sexo:    %c\n", vetor_alunos[i].sexo);
        }
    }

    pausar();
}

int tela_sair()
{
    char ch;

    int sair;
    limpar();
    printf("5 - Sair \n\n");

    do
    {
        printf("\nDeseja sair?  (s/n): ");
        scanf(" %c", &ch);

        fflush(stdin);

        ch = toupper(ch);

        if (ch == 'S')
        {
            sair = 1;
        }
        else if (ch == 'N')
        {
            sair = 0;
        }

    } while (!(ch == 'S' || ch == 'N'));

    return sair;
}

void limpar()
{
    system("clear");
    // system("cls");
}

void pausar()
{
    printf("Pressione Enter para continuar...");
    getchar();
    // system("pause");
}