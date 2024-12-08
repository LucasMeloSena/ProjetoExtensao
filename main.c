#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define NUM_MAX_CADASTROS_ALUNOS 1024
#define NUM_MAX_CADASTROS_ADMIN 100
#define NUM_MAX_CADASTROS_CUIDADORES 1024
#define NUM_MAX_CADASTROS_OBSERVACOES 3000

typedef struct
{
    int ocupado;
    char id[12];
    char nome[256];
    char senha[10];
} Admin;

typedef struct
{
    int ocupado;
    char matricula[12];
    char nome[256];
    int idade;
    char sexo;
    char turma[10];
    char informacoes[1000];
} Aluno;

typedef struct
{
    int ocupado;
    char matricula[12];
    char nome[256];
    char senha[10];
} Cuidador;

typedef struct
{
    int ocupado;
    char matricula_aluno[12];
    char matricula_cuidador[12];
    char observacao[2000];
    char data[100];
} Observacao;

Admin vetor_admin[NUM_MAX_CADASTROS_ADMIN];
Aluno vetor_alunos[NUM_MAX_CADASTROS_ALUNOS];
Cuidador vetor_cuidadores[NUM_MAX_CADASTROS_CUIDADORES];
Observacao vetor_observacoes[NUM_MAX_CADASTROS_OBSERVACOES];

int total_admin = 0;
int total_alunos = 0;
int total_cuidadores = 0;
int total_observacoes = 0;
char caminho_arquivo_total_alunos[256] = "./total_alunos.dat";
char caminho_arquivo_alunos[256] = "./alunos.dat";
char caminho_arquivo_admin[256];
char caminho_arquivo_cuidadores[256];
char caminho_arquivo_observacoes[256];
time_t agora;
// agora = time(NULL);

// Telas iniciais:
int tela_menu_opcoes_home();
int tela_menu_opcoes_cadastro_login();
int tela_menu_opcoes_login();
void tela_cadastrar_admin();
int tela_login_admin();
void tela_login_cuidador();
int tela_menu_opcoes_admin();
int tela_menu_opcoes_cuidador();

// Telas admin:
void tela_cadastrar_aluno();
void tela_pesquisar_aluno_by_matricula();
void tela_relatorio_alunos();
void tela_remover_aluno();
void tela_editar();
void salvar_aluno_arquivo();
void carregar_alunos_arquivo();
void remover_aluno_arquivo(char matricula[]);
void editar_aluno_arquivo(char matricula[]);
void init_arquivo_admin();
void salvar_admin_arquivo();
void carregar_admin_arquivo();

// Telas comuns
void limpar();
void pausar();
int tela_sair();

int main()
{
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");
    init_arquivo_admin();

    int sair = 0;
    int opcao;

    for (int i = 0; i < NUM_MAX_CADASTROS_ALUNOS; i++)
    {
        vetor_admin[i].ocupado = 0;
        vetor_alunos[i].ocupado = 0;
        vetor_cuidadores[i].ocupado = 0;
        vetor_observacoes[i].ocupado = 0;
    }

    while (1)
    {
        opcao = tela_menu_opcoes_home();
        int opcao_cadastro_login;
        int opcao_admin;

        switch (opcao)
        {
        case 1:
            opcao_cadastro_login = tela_menu_opcoes_cadastro_login();
            switch (opcao_cadastro_login)
            {
            case 1:
                tela_cadastrar_admin();
                break;
            case 2:
                opcao_admin = tela_login_admin();
                switch (opcao_admin)
                {
                case 1:
                    tela_cadastrar_aluno();
                    break;
                case 2:
                    tela_pesquisar_aluno_by_matricula();
                    break;
                case 3:
                    tela_remover_aluno();
                    break;
                case 4:
                    tela_editar();
                    break;
                case 5:
                    tela_relatorio_alunos();
                    break;
                case 6:
                    break;
                default:
                    printf("\nOpção Inválida!!! \n");
                    pausar();
                }
                break;
            }
            break;
        case 2:
            // tela_login_admin();
            break;
        case 3:
            sair = tela_sair();
            if (sair == 1)
            {
                printf("\nPrograma encerrado com sucesso!");
                exit(0);
            }
            break;
        default:
            printf("\nOpção Inválida!!! \n");
            pausar();
        }
    }

    limpar();
    printf("\nFim da execução do programa!\n");

    return 0;
}

int tela_menu_opcoes_home()
{
    int opcao;

    limpar();
    printf("Menu de Opções - Home \n");
    printf("1 - Usuário Admin\n");
    printf("2 - Usuário Cuidador\n");
    printf("3 - Sair \n\n");

    printf("Escolha um tipo de usuário para prosseguir: ");
    int erro = scanf("%d", &opcao);

    if (erro != 1)
    {
        fflush(stdin);
        opcao = -1;
    }

    return opcao;
}

int tela_menu_opcoes_cadastro_login()
{
    int opcao;

    limpar();
    printf("Menu de Opções - Admin \n");
    printf("1 - Cadastro\n");
    printf("2 - Login\n");
    printf("3 - Voltar \n\n");

    printf("Escolha uma opção: ");
    int erro = scanf("%d", &opcao);

    if (erro != 1)
    {
        fflush(stdin);
        opcao = -1;
    }

    return opcao;
}

int tela_menu_opcoes_admin()
{
    int opcao;

    limpar();
    printf("Menu de Opções \n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Pesquisar Aluno por Matrícula\n");
    printf("3 - Remover Aluno\n");
    printf("4 - Editar Aluno\n");
    printf("5 - Relatório de Alunos Cadastrados\n");
    printf("6 - Sair \n\n");

    printf("Escolha uma opção: ");
    int erro = scanf("%d", &opcao);

    if (erro != 1)
    {
        fflush(stdin);
        opcao = -1;
    }

    return opcao;
}

void tela_cadastrar_admin()
{
    char ch;
    int erro;
    int idxPesquisa = -1;

    char id[12];
    char nome[256];
    char senha[10];

    limpar();
    carregar_admin_arquivo();
    printf("-- Menu Cadastrar Admin -- \n");

    if (total_admin >= NUM_MAX_CADASTROS_ADMIN)
    {
        printf("\nErro: O cadastro já atingiu sua capacidade máxima!\n");
        pausar();
    }

    do
    {
        erro = 0;

        printf("\n*Digite a id da escola: ");
        scanf(" %11[^\n]", id);
        fflush(stdin);

        if (strlen(id) > 11)
        {
            erro = 1;
            printf("ERRO: O id pode possuir no máximo 11 carracteres!\n");
        }
        if (strlen(id) < 1)
        {
            erro = 1;
            printf("ERRO: O id deve possuir pelo menos 1 carracter!\n");
        }
    } while (erro == 1);

    do
    {
        erro = 0;

        printf("*Digite o nome da escola: ");
        scanf(" %255[^\n]", nome);
        fflush(stdin);

        if (strlen(nome) > 255)
        {
            erro = 1;
            printf("ERRO: O nome da escola pode possuir no máximo 254 carracteres!\n");
        }
        if (strlen(nome) < 3)
        {
            erro = 1;
            printf("ERRO: O nome da escola deve possuir pelo menos 3 carracteres!\n");
        }
    } while (erro == 1);

    do
    {
        erro = 0;

        printf("*Digite a senha: ");
        scanf(" %9[^\n]", senha);
        fflush(stdin);

        if (strlen(senha) > 9)
        {
            erro = 1;
            printf("ERRO: A senha pode possuir no máximo 9 carracteres!\n");
        }
        if (strlen(senha) < 4)
        {
            erro = 1;
            printf("ERRO: A senha deve possuir pelo menos 4 carracteres!\n");
        }
    } while (erro == 1);

    idxPesquisa = -1;
    for (int i = 0; i < NUM_MAX_CADASTROS_ADMIN; i++)
    {
        if (vetor_admin[i].ocupado == 1)
        {
            if (strcmp(vetor_admin[i].id, id) == 0)
            {
                idxPesquisa = i;
                break;
            }
        }
    }

    if (idxPesquisa != -1)
    {
        printf("\nErro: Não foi possível inserir os dados pois já existe uma escola com o mesmo id cadastrado!\v");
        pausar();
    }
    else
    {
        for (int i = 0; i < NUM_MAX_CADASTROS_ADMIN; i++)
        {
            if (vetor_admin[i].ocupado == 0)
            {
                vetor_admin[i].ocupado = 1;

                strcpy(vetor_admin[i].id, id);
                strcpy(vetor_admin[i].nome, nome);
                strcpy(vetor_admin[i].senha, senha);
                total_admin = total_admin + 1;
                salvar_admin_arquivo();

                printf("\nDados cadastrados com sucesso! \n");
                pausar();

                break;
            }
        }
    }
}

int tela_login_admin()
{
    char ch;
    int erro;
    int idxPesquisa = -1;
    char id[12];
    char senha[10];

    limpar();
    carregar_admin_arquivo();
    printf("-- Menu Login Admin -- \n");
    erro = 0;

    printf("\nDigite o id: ");
    scanf(" %11[^\n]", id);
    fflush(stdin);
    printf("Digite a senha: ");
    scanf(" %9[^\n]", senha);
    fflush(stdin);

    for (int i = 0; i < total_admin; i++)
    {
        if (vetor_admin[i].ocupado == 1)
        {
            if (strcmp(vetor_admin[i].id, id) == 0 && strcmp(vetor_admin[i].senha, senha) == 0)
            {
                idxPesquisa = i;
                break;
            }
        }
    }

    if (idxPesquisa != -1)
    {
        printf("\nLogin realizado com sucesso! Bem-vindo(a), %s.\n", vetor_admin[idxPesquisa].nome);
        pausar();

        return tela_menu_opcoes_admin();
    }
    else
    {
        printf("Id: %s", vetor_admin[0].id);
        printf("Senha: %s", vetor_admin[0].senha);
        printf("\nNão foi encontrado o admin com os dados informados!\n\n");
        pausar();
    }
}

void tela_cadastrar_aluno()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;

    char matricula[12];
    char nome[256];
    int idade;
    char sexo, strSexo[3];
    char turma[10];
    char informacoes[1000];
    int ocupado;

    do
    {
        limpar();
        printf("-- Menu Cadastrar -- \n");

        if (total_alunos >= NUM_MAX_CADASTROS_ALUNOS)
        {
            printf("\nErro: O cadastro já atingiu sua capacidade m�xima!\n");
            pausar();
            break;
        }

        do
        {
            erro = 0;

            printf("\n*Digite a matrícula: ");
            scanf(" %11[^\n]", matricula);
            fflush(stdin);

            if (strlen(nome) > 11)
            {
                erro = 1;
                printf("ERRO: A matrícula pode possuir no máximo 11 carracteres!\n");
            }
            if (strlen(matricula) < 3)
            {
                erro = 1;
                printf("ERRO: A matrícula deve possuir pelo menos 3 (três) carracteres!\n");
            }
        } while (erro == 1);

        do
        {
            erro = 0;

            printf("*Digite o nome: ");
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
            printf("*Digite a idade: ");
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

            printf("*Digite o sexo (M/F): ");
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

        do
        {
            erro = 0;

            printf("*Digite a turma: ");
            scanf(" %9[^\n]", turma);
            fflush(stdin);

            if (strlen(turma) > 9)
            {
                erro = 1;
                printf("ERRO: A turma pode possuir no máximo 9 carracteres!\n");
            }
            if (strlen(turma) < 1)
            {
                erro = 1;
                printf("ERRO: A turma deve possuir pelo menos 1 carractere!\n");
            }
        } while (erro == 1);

        do
        {
            erro = 0;

            printf("Digite as informações do aluno: ");
            scanf(" %999[^\n]", informacoes);
            fflush(stdin);

            if (strlen(informacoes) > 999)
            {
                erro = 1;
                printf("ERRO: As informações pode possuir no máximo 999 carracteres!\n");
            }
        } while (erro == 1);

        idxPesquisa = -1;
        for (int i = 0; i < NUM_MAX_CADASTROS_ALUNOS; i++)
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
            for (int i = 0; i < NUM_MAX_CADASTROS_ALUNOS; i++)
            {
                if (vetor_alunos[i].ocupado == 0)
                {
                    vetor_alunos[i].ocupado = 1;
                    strcpy(vetor_alunos[i].nome, nome);
                    strcpy(vetor_alunos[i].matricula, matricula);
                    vetor_alunos[i].idade = idade;
                    vetor_alunos[i].sexo = sexo;
                    strcpy(vetor_alunos[i].turma, turma);
                    strcpy(vetor_alunos[i].informacoes, informacoes);
                    total_alunos = total_alunos + 1;
                    salvar_aluno_arquivo();

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

void tela_pesquisar_aluno_by_matricula()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;
    char matricula[12];

    do
    {
        limpar();
        carregar_alunos_arquivo();
        printf("-- Menu Pesquisar Aluno por Matrícula -- \n");
        erro = 0;

        printf("\nDigite a matrícula do aluno: ");
        scanf(" %11[^\n]", matricula);
        fflush(stdin);

        int idxPesquisa = -1;
        for (int i = 0; i < total_alunos; i++)
        {
            // if (vetor_alunos[i].ocupado == 1)
            // {
            if (strcmp(vetor_alunos[i].matricula, matricula) == 0)
            {
                idxPesquisa = i;
                break;
            }
            //}
        }

        if (idxPesquisa != -1)
        {
            printf("\nAluno encontrado: \n");
            printf("Matrícula: %s\n", vetor_alunos[idxPesquisa].matricula);
            printf("Nome: %s\n", vetor_alunos[idxPesquisa].nome);
            printf("Idade: %d\n", vetor_alunos[idxPesquisa].idade);
            printf("Sexo: %c\n", vetor_alunos[idxPesquisa].sexo);
            printf("Turma: %s\n", vetor_alunos[idxPesquisa].turma);
            printf("Informações: %s\n\n", vetor_alunos[idxPesquisa].informacoes);
            pausar();
        }
        else
        {
            printf("\nNão foi encontrado um aluno com a matrícula informada!\n\n");
            pausar();
        }

        do
        {
            printf("Gostaria de pesquisar outra pessoa? (s/n): ");
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

void tela_remover_aluno()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;
    char matricula[12];

    do
    {
        limpar();
        carregar_alunos_arquivo();
        printf("-- Menu Remover Aluno --\n");

        erro = 0;
        printf("\nDigite a matrícula: ");
        scanf(" %11[^\n]", matricula);
        fflush(stdin);

        idxPesquisa = -1;
        for (int i = 0; i < NUM_MAX_CADASTROS_ALUNOS; i++)
        {
            if (vetor_alunos[i].ocupado == 1)
            {
                if (strcmp(vetor_alunos[i].matricula, matricula) == 0)
                {
                    vetor_alunos[i].ocupado = 0;
                    idxPesquisa = i;
                    remover_aluno_arquivo(vetor_alunos[i].matricula);
                    break;
                }
            }
        }

        if (idxPesquisa != -1)
        {
            printf("\nAluno removido com sucesso!\n");
        }
        else
        {
            printf("\nNão foi possível remover o aluno!\n");
        }
        pausar();

        do
        {

            printf("\nGostaria de remover outro aluno? (s/n): ");
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
    pausar();
}

void tela_relatorio_alunos()
{
    limpar();
    carregar_alunos_arquivo();
    pausar();
    printf("-- Menu Relatório Alunos -- \n\n");

    for (int i = 0; i < NUM_MAX_CADASTROS_ALUNOS; i++)
    {
        if (vetor_alunos[i].ocupado == 1)
        {
            printf("Matrícula: %s\n", vetor_alunos[i].matricula);
            printf("Nome: %s\n", vetor_alunos[i].nome);
            printf("Idade: %d\n", vetor_alunos[i].idade);
            printf("Sexo: %c\n", vetor_alunos[i].sexo);
            printf("Turma: %s\n", vetor_alunos[i].turma);
            printf("Informações: %s\n\n", vetor_alunos[i].informacoes);
        }
    }

    pausar();
}

int tela_sair()
{
    char ch;

    int sair;
    limpar();
    printf("---- Menu Sair ---- \n");

    do
    {
        printf("\nDeseja sair? (s/n): ");
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

void salvar_aluno_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_alunos, "wb");
    FILE *fp_total = fopen(caminho_arquivo_total_alunos, "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fwrite(vetor_alunos, sizeof(Aluno), 1, fp);
    fwrite(&total_alunos, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

void carregar_alunos_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_alunos, "rb");
    FILE *fp_total = fopen(caminho_arquivo_total_alunos, "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }

    fread(vetor_alunos, sizeof(Aluno), 1, fp);
    fread(&total_alunos, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

void remover_aluno_arquivo(char matricula[])
{
    FILE *fp = fopen(caminho_arquivo_alunos, "rb+");
    FILE *fp_total = fopen(caminho_arquivo_total_alunos, "rb+");

    if (fp == NULL || fp_total == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    fread(&total_alunos, sizeof(int), 1, fp_total);
    fread(vetor_alunos, sizeof(Aluno), NUM_MAX_CADASTROS_ALUNOS, fp);

    int encontrado = 0;
    for (int i = 0; i < NUM_MAX_CADASTROS_ALUNOS; i++)
    {
        if (vetor_alunos[i].matricula == matricula && vetor_alunos[i].ocupado != 0)
        {
            vetor_alunos[i].ocupado = 0;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Aluno com matrícula %d não encontrado.\n", matricula);
        fclose(fp);
        fclose(fp_total);
        return;
    }

    total_alunos--;

    fseek(fp, 0, SEEK_SET);
    fwrite(vetor_alunos, sizeof(Aluno), NUM_MAX_CADASTROS_ALUNOS, fp);
    fseek(fp_total, 0, SEEK_SET);
    fwrite(&total_alunos, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

void init_arquivo_admin()
{
    strcpy(caminho_arquivo_admin, "admin.txt");
    FILE *fp = fopen(caminho_arquivo_admin, "r");

    if (fp == NULL)
    {
        fp = fopen(caminho_arquivo_admin, "w");
        fprintf(fp, "%d\n", total_admin);
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }
}

void salvar_admin_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_admin, "w");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%d\n", total_admin);

    for (int i = 0; i < NUM_MAX_CADASTROS_ADMIN; i++)
    {
        if (vetor_admin[i].ocupado == 1)
        {
            fprintf(fp, "%s\n", vetor_admin[i].id);
            fprintf(fp, "%s\n", vetor_admin[i].nome);
            fprintf(fp, "%s\n", vetor_admin[i].senha);
        }
    }
    fclose(fp);
}

void carregar_admin_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_admin, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%d ", &total_admin);

    for (int i = 0; i < total_admin; i++)
    {
        Admin admin;
        fscanf(fp, "%11[^\n] ", admin.id);
        fscanf(fp, "%255[^\n] ", admin.nome);
        fscanf(fp, "%9[^\n] ", admin.senha);
        admin.ocupado = 1;
        vetor_admin[i] = admin;
    }
    fclose(fp);
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