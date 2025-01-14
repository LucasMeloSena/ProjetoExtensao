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
    char hora[100];
} Observacao;

Admin vetor_admin[NUM_MAX_CADASTROS_ADMIN];
Aluno vetor_alunos[NUM_MAX_CADASTROS_ALUNOS];
Cuidador vetor_cuidadores[NUM_MAX_CADASTROS_CUIDADORES];
Observacao vetor_observacoes[NUM_MAX_CADASTROS_OBSERVACOES];
Cuidador cuidador_logado;

int total_admin = 0;
int total_alunos = 0;
int total_cuidadores = 0;
int total_observacoes = 0;
char caminho_arquivo_total_alunos[256] = "./total_alunos.dat";
char caminho_arquivo_alunos[256] = "./alunos.dat";
char caminho_arquivo_admin[256] = "./admins.dat";
char caminho_arquivo_total_admins[256] = "./total_admins.dat";
char caminho_arquivo_cuidadores[256] = "./cuidadores.dat";
char caminho_arquivo_total_cuidadores[256] = "./total_cuidadores.dat";
char caminho_arquivo_observacoes[256] = "./observacoes.dat";
char caminho_arquivo_total_observacoes[256] = "./total_observacoes.dat";

// Telas iniciais:
int tela_menu_opcoes_home();
int tela_menu_opcoes_cadastro_login_admin();
int tela_menu_opcoes_login_cuidador();
int tela_login_admin();
int tela_login_cuidador();
int tela_menu_opcoes_admin();
int tela_menu_opcoes_cuidador();

// Cadastros:
void tela_cadastrar_admin();
void salvar_admin_arquivo();
void tela_cadastrar_aluno();
void salvar_aluno_arquivo();
void tela_cadastrar_cuidador();
void salvar_cuidador_arquivo();
void tela_adicionar_observacao();
void salvar_observacao_arquivo();

// Listagems únicas:
void tela_pesquisar_aluno_by_matricula();
void tela_pesquisar_cuidador_by_matricula();

// Listagens gerais:
void tela_relatorio_alunos();
void carregar_alunos_arquivo();
void carregar_admin_arquivo();
void tela_relatorio_cuidadores();
void carregar_cuidadores_arquivo();
void tela_relatorio_observacoes();
void carregar_observacoes_arquivo();

// Edições:
void tela_editar_aluno();
void editar_aluno_arquivo(Aluno aluno);
void tela_editar_cuidador();
void editar_cuidador_arquivo(Cuidador cuidador);
void substituir_cuidador_arquivo();
void substituir_aluno_arquivo();

// Exclusões:
void tela_remover_aluno();
void remover_aluno_arquivo(char matricula[]);
void tela_remover_cuidador();
void remover_cuidador_arquivo(char matricula[]);

// Telas comuns
void limpar();
void pausar();
int tela_sair();

int main()
{
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");

    int sair = 0;
    int opcao;

    for (int i = 0; i < 1024; i++)
    {
        vetor_alunos[i].ocupado = 0;
        vetor_cuidadores[i].ocupado = 0;
    }

    for (int i = 0; i < 3000; i++)
    {
        vetor_observacoes[i].ocupado = 0;
    }

    for (int i = 0; i < 100; i++)
    {
        vetor_admin[i].ocupado = 0;
    }

    while (1)
    {
        opcao = tela_menu_opcoes_home();
        int opcao_cadastro_login_admin;
        int opcao_login_cuidador;
        int opcao_admin;
        int opcao_cuidador;

        switch (opcao)
        {
        case 1:
            opcao_cadastro_login_admin = tela_menu_opcoes_cadastro_login_admin();
            switch (opcao_cadastro_login_admin)
            {
            case 1:
                tela_cadastrar_admin();
                break;
            case 2:
                opcao_admin = tela_login_admin();
                switch (opcao_admin)
                {
                case 0:
                    break;
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
                    tela_editar_aluno();
                    break;
                case 5:
                    tela_relatorio_alunos();
                    break;
                case 6:
                    tela_cadastrar_cuidador();
                    break;
                case 7:
                    tela_pesquisar_cuidador_by_matricula();
                    break;
                case 8:
                    tela_remover_cuidador();
                    break;
                case 9:
                    tela_editar_cuidador();
                    break;
                case 10:
                    tela_relatorio_cuidadores();
                    break;
                case 11:
                    tela_relatorio_observacoes();
                    break;
                case 12:
                    break;
                default:
                    printf("\nOpção Inválida!!! \n");
                    pausar();
                }
                break;
            }
            break;
        case 2:
            opcao_login_cuidador = tela_menu_opcoes_login_cuidador();
            switch (opcao_login_cuidador)
            {
            case 1:
                opcao_cuidador = tela_login_cuidador();
                switch (opcao_cuidador)
                {
                case 0:
                    break;
                case 1:
                    tela_pesquisar_aluno_by_matricula();
                    break;
                case 2:
                    tela_adicionar_observacao();
                    break;
                case 3:
                    break;
                default:
                    printf("\nOpção Inválida!!! \n");
                    pausar();
                }
                break;
            }
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

int tela_menu_opcoes_cadastro_login_admin()
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

int tela_menu_opcoes_login_cuidador()
{
    int opcao;

    limpar();
    printf("Menu de Opções - Cuidador \n");
    printf("1 - Login\n");
    printf("2 - Voltar \n\n");

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
    printf("6 - Cadastrar Cuidador\n");
    printf("7 - Pesquisar Cuidador por Matrícula\n");
    printf("8 - Remover Cuidador\n");
    printf("9 - Editar Cuidador\n");
    printf("10 - Relatório de Cuidadores Cadastrados\n");
    printf("11 - Relatório de Observações\n");
    printf("12 - Sair \n\n");

    printf("Escolha uma opção: ");
    int erro = scanf("%d", &opcao);

    if (erro != 1)
    {
        fflush(stdin);
        opcao = -1;
    }

    return opcao;
}

int tela_menu_opcoes_cuidador()
{
    int opcao;

    limpar();
    printf("Menu de Opções \n");
    printf("1 - Pesquisar Aluno por Matrícula\n");
    printf("2 - Adicionar Observação Diária de Discente\n");
    printf("3 - Sair \n\n");

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

void tela_cadastrar_cuidador()
{
    char ch;
    int erro;
    int idxPesquisa = -1;

    char id[12];
    char nome[256];
    char senha[10];

    limpar();
    carregar_cuidadores_arquivo();
    printf("-- Menu Cadastrar Cuidador -- \n");

    if (total_cuidadores >= NUM_MAX_CADASTROS_CUIDADORES)
    {
        printf("\nErro: O cadastro já atingiu sua capacidade máxima!\n");
        pausar();
    }

    do
    {
        erro = 0;

        printf("\n*Digite o id do cuidador: ");
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

        printf("*Digite o nome do cuidador: ");
        scanf(" %255[^\n]", nome);
        fflush(stdin);

        if (strlen(nome) > 255)
        {
            erro = 1;
            printf("ERRO: O nome do cuidador pode possuir no máximo 254 carracteres!\n");
        }
        if (strlen(nome) < 3)
        {
            erro = 1;
            printf("ERRO: O nome do cuidador deve possuir pelo menos 3 carracteres!\n");
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
    for (int i = 0; i < NUM_MAX_CADASTROS_CUIDADORES; i++)
    {
        if (vetor_cuidadores[i].ocupado == 1)
        {
            if (strcmp(vetor_cuidadores[i].matricula, id) == 0)
            {
                idxPesquisa = i;
                break;
            }
        }
    }

    if (idxPesquisa != -1)
    {
        printf("\nErro: Não foi possível inserir os dados pois já existe um cuidador com o mesmo id cadastrado!\v");
        pausar();
    }
    else
    {
        if (total_cuidadores == 0)
        {
            vetor_cuidadores[0].ocupado = 1;
            strcpy(vetor_cuidadores[0].matricula, id);
            strcpy(vetor_cuidadores[0].nome, nome);
            strcpy(vetor_cuidadores[0].senha, senha);
            total_cuidadores++;
            salvar_cuidador_arquivo();

            printf("\nDados cadastrados com sucesso! \n");
            pausar();
        }
        else
        {
            int encontrou_desocupado = 0;
            for (int i = 0; i < total_cuidadores; i++)
            {
                if (vetor_cuidadores[i].ocupado == 0)
                {
                    vetor_cuidadores[i].ocupado = 1;
                    strcpy(vetor_cuidadores[i].matricula, id);
                    strcpy(vetor_cuidadores[i].nome, nome);
                    strcpy(vetor_cuidadores[i].senha, senha);
                    substituir_cuidador_arquivo();

                    printf("\nDados cadastrados com sucesso! \n");
                    pausar();

                    encontrou_desocupado = 1;
                    break;
                }
            }
            if (encontrou_desocupado == 0)
            {
                vetor_cuidadores[total_cuidadores].ocupado = 1;
                strcpy(vetor_cuidadores[total_cuidadores].matricula, id);
                strcpy(vetor_cuidadores[total_cuidadores].nome, nome);
                strcpy(vetor_cuidadores[total_cuidadores].senha, senha);
                total_cuidadores++;
                salvar_cuidador_arquivo();

                printf("\nDados cadastrados com sucesso! \n");
                pausar();
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
        printf("\nNão foi encontrado o admin com os dados informados!\n\n");
        pausar();
        return 0;
    }
}

int tela_login_cuidador()
{
    char ch;
    int erro;
    int idxPesquisa = -1;
    char id[12];
    char senha[10];

    limpar();
    carregar_cuidadores_arquivo();
    printf("-- Menu Login Cuidador -- \n");
    erro = 0;

    printf("\nDigite a matricula: ");
    scanf(" %11[^\n]", id);
    fflush(stdin);
    printf("Digite a senha: ");
    scanf(" %9[^\n]", senha);
    fflush(stdin);

    for (int i = 0; i < total_cuidadores; i++)
    {
        if (vetor_cuidadores[i].ocupado == 1)
        {
            if (strcmp(vetor_cuidadores[i].matricula, id) == 0 && strcmp(vetor_cuidadores[i].senha, senha) == 0)
            {
                idxPesquisa = i;
                break;
            }
        }
    }

    if (idxPesquisa != -1)
    {
        printf("\nLogin realizado com sucesso! Bem-vindo(a), %s.\n", vetor_cuidadores[idxPesquisa].nome);
        strcpy(cuidador_logado.matricula, vetor_cuidadores[idxPesquisa].matricula);
        strcpy(cuidador_logado.nome, vetor_cuidadores[idxPesquisa].nome);
        strcpy(cuidador_logado.senha, vetor_cuidadores[idxPesquisa].senha);
        cuidador_logado.ocupado = vetor_cuidadores[idxPesquisa].ocupado;

        pausar();

        return tela_menu_opcoes_cuidador();
    }
    else
    {
        printf("\nNão foi encontrado o cuidador com os dados informados!\n\n");
        pausar();
        return 0;
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
        carregar_alunos_arquivo();
        printf("-- Menu Cadastrar Aluno -- \n");

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

            if (strlen(matricula) > 11)
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
            if (total_alunos == 0)
            {
                vetor_alunos[0].ocupado = 1;
                strcpy(vetor_alunos[0].nome, nome);
                strcpy(vetor_alunos[0].matricula, matricula);
                vetor_alunos[0].idade = idade;
                vetor_alunos[0].sexo = sexo;
                strcpy(vetor_alunos[0].turma, turma);
                strcpy(vetor_alunos[0].informacoes, informacoes);
                total_alunos++;
                salvar_aluno_arquivo();

                printf("\nDados cadastrados com sucesso! \n");
                pausar();
            }
            else
            {
                int encontrou_desocupado = 0;
                for (int i = 0; i < total_cuidadores; i++)
                {
                    if (vetor_cuidadores[i].ocupado == 0)
                    {
                        vetor_alunos[i].ocupado = 1;
                        strcpy(vetor_alunos[i].nome, nome);
                        strcpy(vetor_alunos[i].matricula, matricula);
                        vetor_alunos[i].idade = idade;
                        vetor_alunos[i].sexo = sexo;
                        strcpy(vetor_alunos[i].turma, turma);
                        strcpy(vetor_alunos[i].informacoes, informacoes);
                        substituir_aluno_arquivo();

                        printf("\nDados cadastrados com sucesso! \n");
                        pausar();

                        encontrou_desocupado = 1;
                        break;
                    }
                }
                if (encontrou_desocupado == 0)
                {
                    vetor_alunos[total_alunos].ocupado = 1;
                    strcpy(vetor_alunos[total_alunos].nome, nome);
                    strcpy(vetor_alunos[total_alunos].matricula, matricula);
                    vetor_alunos[total_alunos].idade = idade;
                    vetor_alunos[total_alunos].sexo = sexo;
                    strcpy(vetor_alunos[total_alunos].turma, turma);
                    strcpy(vetor_alunos[total_alunos].informacoes, informacoes);
                    total_alunos++;
                    salvar_aluno_arquivo();

                    printf("\nDados cadastrados com sucesso! \n");
                    pausar();
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

void tela_editar_aluno()
{
    int idxPesquisa = -1;
    char matricula[12];

    limpar();
    carregar_alunos_arquivo();
    printf("-- Menu Atualizar Aluno -- \n");

    printf("\nDigite a matrícula do aluno: ");
    scanf(" %11[^\n]", matricula);
    fflush(stdin);

    for (int i = 0; i < total_alunos; i++)
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
        printf("\nAluno encontrado: \n");
        printf("Matrícula: %s\n", vetor_alunos[idxPesquisa].matricula);
        printf("Nome: %s\n", vetor_alunos[idxPesquisa].nome);
        printf("Idade: %d\n", vetor_alunos[idxPesquisa].idade);
        printf("Sexo: %c\n", vetor_alunos[idxPesquisa].sexo);
        printf("Turma: %s\n", vetor_alunos[idxPesquisa].turma);
        printf("Informações: %s\n\n", vetor_alunos[idxPesquisa].informacoes);

        int erro;
        char nome[256];
        int idade;
        char sexo, strSexo[3];
        char turma[10];
        char informacoes[1000];

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

        Aluno aluno;
        aluno.ocupado = 1;
        strcpy(aluno.nome, nome);
        strcpy(aluno.matricula, matricula);
        aluno.idade = idade;
        aluno.sexo = sexo;
        strcpy(aluno.turma, turma);
        strcpy(aluno.informacoes, informacoes);
        editar_aluno_arquivo(aluno);

        printf("\nAluno atualizado com sucesso! \n");
        pausar();
    }
    else
    {
        printf("\nNão foi encontrado um aluno com a matrícula informada!\n\n");
        pausar();
    }
}

void tela_relatorio_alunos()
{
    limpar();
    carregar_alunos_arquivo();
    getchar();
    printf("-- Menu Relatório Alunos -- \n\n");

    int total_ocupados = 0;
    for (int i = 0; i < total_alunos; i++)
    {
        if (vetor_alunos[i].ocupado == 1)
        {
            total_ocupados++;
        }
    }

    printf("Número de alunos cadastrados: %d\n\n", total_ocupados);
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

void tela_pesquisar_cuidador_by_matricula()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;
    char matricula[12];

    do
    {
        limpar();
        carregar_cuidadores_arquivo();
        printf("-- Menu Pesquisar Cuidador por Matrícula -- \n");
        erro = 0;

        printf("\nDigite a matrícula do cuidador: ");
        scanf(" %11[^\n]", matricula);
        fflush(stdin);

        int idxPesquisa = -1;
        for (int i = 0; i < total_cuidadores; i++)
        {
            if (vetor_cuidadores[i].ocupado == 1)
            {
                if (strcmp(vetor_cuidadores[i].matricula, matricula) == 0)
                {
                    idxPesquisa = i;
                    break;
                }
            }
        }

        if (idxPesquisa != -1)
        {
            printf("\nCuidador encontrado: \n");
            printf("Matrícula: %s\n", vetor_cuidadores[idxPesquisa].matricula);
            printf("Nome: %s\n", vetor_cuidadores[idxPesquisa].nome);
            printf("Senha: %s\n\n", vetor_cuidadores[idxPesquisa].senha);
            pausar();
        }
        else
        {
            printf("\nNão foi encontrado um cuidador com a matrícula informada!\n\n");
            pausar();
        }

        do
        {
            printf("Gostaria de pesquisar outro cuidador? (s/n): ");
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

void tela_remover_cuidador()
{
    int continuar;
    char ch;
    int erro;
    int idxPesquisa = -1;
    char matricula[12];

    do
    {
        limpar();
        carregar_cuidadores_arquivo();
        printf("-- Menu Remover Cuidador --\n");

        erro = 0;
        printf("\nDigite a matrícula: ");
        scanf(" %11[^\n]", matricula);
        fflush(stdin);

        idxPesquisa = -1;
        for (int i = 0; i < NUM_MAX_CADASTROS_CUIDADORES; i++)
        {
            if (vetor_cuidadores[i].ocupado == 1)
            {
                if (strcmp(vetor_cuidadores[i].matricula, matricula) == 0)
                {
                    vetor_cuidadores[i].ocupado = 0;
                    idxPesquisa = i;
                    remover_cuidador_arquivo(vetor_cuidadores[i].matricula);
                    break;
                }
            }
        }

        if (idxPesquisa != -1)
        {
            printf("\nCuidador removido com sucesso!\n");
        }
        else
        {
            printf("\nNão foi possível remover o cuidador!\n");
        }
        pausar();

        do
        {

            printf("\nGostaria de remover outro cuidador? (s/n): ");
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

void tela_editar_cuidador()
{
    int idxPesquisa = -1;
    char matricula[12];
    char senha[10];

    limpar();
    carregar_cuidadores_arquivo();
    printf("-- Menu Atualizar Cuidador -- \n");

    printf("\nDigite a matrícula do cuidador: ");
    scanf(" %11[^\n]", matricula);
    fflush(stdin);

    for (int i = 0; i < total_cuidadores; i++)
    {
        if (vetor_cuidadores[i].ocupado == 1)
        {
            if (strcmp(vetor_cuidadores[i].matricula, matricula) == 0)
            {
                idxPesquisa = i;
                break;
            }
        }
    }

    if (idxPesquisa != -1)
    {
        printf("\nCuidador encontrado: \n");
        printf("Matrícula: %s\n", vetor_cuidadores[idxPesquisa].matricula);
        printf("Nome: %s\n", vetor_cuidadores[idxPesquisa].nome);
        printf("Senha: %s\n\n", vetor_cuidadores[idxPesquisa].senha);

        int erro;
        char nome[256];
        int idade;
        char sexo, strSexo[3];
        char turma[10];
        char informacoes[1000];

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

        Cuidador cuidador;
        cuidador.ocupado = 1;
        strcpy(cuidador.nome, nome);
        strcpy(cuidador.matricula, matricula);
        strcpy(cuidador.senha, senha);
        editar_cuidador_arquivo(cuidador);

        printf("\nCuidador atualizado com sucesso! \n");
        pausar();
    }
    else
    {
        printf("\nNão foi encontrado um cuidador com a matrícula informada!\n\n");
        pausar();
    }
}

void tela_relatorio_cuidadores()
{
    limpar();
    carregar_cuidadores_arquivo();
    getchar();
    printf("-- Menu Relatório Cuidadores -- \n\n");

    int total_ocupados = 0;
    for (int i = 0; i < total_cuidadores; i++)
    {
        if (vetor_cuidadores[i].ocupado == 1)
        {
            total_ocupados++;
        }
    }

    printf("Número de cuidadores cadastrados: %d\n\n", total_ocupados);
    for (int i = 0; i < NUM_MAX_CADASTROS_CUIDADORES; i++)
    {
        if (vetor_cuidadores[i].ocupado == 1)
        {
            printf("Matrícula: %s\n", vetor_cuidadores[i].matricula);
            printf("Nome: %s\n", vetor_cuidadores[i].nome);
            printf("Senha: %s\n\n", vetor_cuidadores[i].senha);
        }
    }

    pausar();
}

void tela_relatorio_observacoes()
{
    limpar();
    carregar_cuidadores_arquivo();
    carregar_alunos_arquivo();
    carregar_observacoes_arquivo();
    getchar();
    printf("-- Menu Relatório Observações -- \n\n");

    int total_ocupados = 0;
    for (int i = 0; i < total_observacoes; i++)
    {
        if (vetor_observacoes[i].ocupado == 1)
        {
            total_ocupados++;
        }
    }

    printf("Número de observações cadastradas: %d\n\n", total_observacoes);

    for (int i = 0; i < total_observacoes; i++)
    {
        if (vetor_observacoes[i].ocupado == 1)
        {
            char aluno[256];
            char cuidador[256];

            for (int j = 0; j < total_alunos; j++)
            {
                if (vetor_alunos[j].ocupado == 1)
                {
                    if (strcmp(vetor_alunos[j].matricula, vetor_observacoes[i].matricula_aluno) == 0)
                    {
                        strcpy(aluno, vetor_alunos[j].nome);
                        break;
                    }
                }
            }

            for (int j = 0; j < total_cuidadores; j++)
            {
                if (vetor_cuidadores[j].ocupado == 1)
                {
                    if (strcmp(vetor_cuidadores[j].matricula, vetor_observacoes[i].matricula_cuidador) == 0)
                    {
                        strcpy(cuidador, vetor_cuidadores[j].nome);
                        break;
                    }
                }
            }

            printf("Matrícula Aluno: %s\n", vetor_observacoes[i].matricula_aluno);
            printf("Aluno: %s\n", aluno);
            printf("Matrícula Cuidador: %s\n", vetor_observacoes[i].matricula_cuidador);
            printf("Cuidador: %s\n", cuidador);
            printf("Data: %s\n", vetor_observacoes[i].data);
            printf("Hora: %s\n", vetor_observacoes[i].hora);
            printf("Observação: %s\n\n", vetor_observacoes[i].observacao);
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

void tela_adicionar_observacao()
{
    carregar_observacoes_arquivo();

    time_t agora = time(NULL);
    struct tm tm = *localtime(&agora);
    char data[100];
    char hora[100];
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(hora, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

    char ch;
    int erro;

    char matricula_aluno[12];
    char observacao[2000];

    limpar();
    carregar_alunos_arquivo();
    printf("-- Menu Cadastrar Observação -- \n");

    if (total_observacoes >= NUM_MAX_CADASTROS_OBSERVACOES)
    {
        printf("\nErro: O cadastro já atingiu sua capacidade máxima!\n");
        pausar();
    }

    do
    {
        erro = 0;

        printf("\n*Digite a matrícula do aluno: ");
        scanf(" %11[^\n]", matricula_aluno);
        fflush(stdin);

        if (strlen(matricula_aluno) > 11)
        {
            erro = 1;
            printf("ERRO: A matrícula pode possuir no máximo 11 carracteres!\n");
        }
        if (strlen(matricula_aluno) < 3)
        {
            erro = 1;
            printf("ERRO: A matrícula deve possuir pelo menos 3 (três) carracteres!\n");
        }
    } while (erro == 1);

    int idxPesquisa = -1;
    for (int i = 0; i < total_alunos; i++)
    {
        if (vetor_alunos[i].ocupado == 1)
        {
            if (strcmp(vetor_alunos[i].matricula, matricula_aluno) == 0)
            {
                idxPesquisa = i;
                break;
            }
        }
    }

    if (idxPesquisa != -1)
    {
        do
        {
            erro = 0;

            printf("*Digite a observação: ");
            scanf(" %1999[^\n]", observacao);
            fflush(stdin);

            if (strlen(observacao) > 1999)
            {
                erro = 1;
                printf("ERRO: A observações pode possuir no máximo 1999 carracteres!\n");
            }
            if (strlen(observacao) < 10)
            {
                erro = 1;
                printf("ERRO: A observação deve possuir pelo menos 10 carracteres!\n");
            }
        } while (erro == 1);

        vetor_observacoes[total_observacoes].ocupado = 1;
        strcpy(vetor_observacoes[total_observacoes].observacao, observacao);
        strcpy(vetor_observacoes[total_observacoes].data, data);
        strcpy(vetor_observacoes[total_observacoes].hora, hora);
        strcpy(vetor_observacoes[total_observacoes].matricula_cuidador, cuidador_logado.matricula);
        strcpy(vetor_observacoes[total_observacoes].matricula_aluno, matricula_aluno);
        total_observacoes++;
        salvar_observacao_arquivo();

        printf("\nDados cadastrados com sucesso! \n");
        pausar();
    }
    else
    {
        printf("\nNão foi encontrado um aluno com a matrícula informada!\n\n");
        pausar();
    }
}

// CRUD Alunos
void salvar_aluno_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_alunos, "ab");
    FILE *fp_total = fopen(caminho_arquivo_total_alunos, "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fwrite(&total_alunos, sizeof(int), 1, fp_total);
    fwrite(&vetor_alunos[total_alunos - 1], sizeof(Aluno), 1, fp);

    fclose(fp);
    fclose(fp_total);
}

void substituir_aluno_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_alunos, "rb+");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fwrite(vetor_alunos, sizeof(Aluno), total_alunos, fp);
    fclose(fp);
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

    fread(&total_alunos, sizeof(int), 1, fp_total);
    fread(vetor_alunos, sizeof(Aluno), total_alunos, fp);
    fclose(fp_total);
    fclose(fp);
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
    fread(vetor_alunos, sizeof(Aluno), total_alunos, fp);

    int encontrado = 0;
    for (int i = 0; i < total_alunos; i++)
    {
        if (strcmp(vetor_alunos[i].matricula, matricula) == 0 && vetor_alunos[i].ocupado != 0)
        {
            vetor_alunos[i].ocupado = 0;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Aluno com matrícula %s não encontrado.\n", matricula);
        fclose(fp);
        fclose(fp_total);
        return;
    }

    fseek(fp, 0, SEEK_SET);
    fwrite(vetor_alunos, sizeof(Aluno), total_alunos, fp);
    fseek(fp_total, 0, SEEK_SET);
    fwrite(&total_alunos, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

void editar_aluno_arquivo(Aluno aluno)
{
    FILE *fp = fopen(caminho_arquivo_alunos, "rb+");
    FILE *fp_total = fopen(caminho_arquivo_total_alunos, "rb+");

    if (fp == NULL || fp_total == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    int encontrado = 0;
    for (int i = 0; i < NUM_MAX_CADASTROS_ALUNOS; i++)
    {
        if (strcmp(vetor_alunos[i].matricula, aluno.matricula) == 0 && vetor_alunos[i].ocupado != 0)
        {
            vetor_alunos[i] = aluno;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Aluno com matrícula %s não encontrado.\n", aluno.matricula);
        fclose(fp);
        fclose(fp_total);
        return;
    }

    fseek(fp, 0, SEEK_SET);
    fwrite(vetor_alunos, sizeof(Aluno), NUM_MAX_CADASTROS_ALUNOS, fp);
    fseek(fp_total, 0, SEEK_SET);
    fwrite(&total_alunos, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

// CRUD Admin
void salvar_admin_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_admin, "ab");
    FILE *fp_total = fopen(caminho_arquivo_total_admins, "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fwrite(&vetor_admin[total_admin - 1], sizeof(Admin), 1, fp);
    fwrite(&total_admin, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

void carregar_admin_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_admin, "rb");
    FILE *fp_total = fopen(caminho_arquivo_total_admins, "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }

    fread(&total_admin, sizeof(int), 1, fp_total);
    fread(vetor_admin, sizeof(Admin), total_admin, fp);
    fclose(fp);
    fclose(fp_total);
}

// Funções gerais:
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

// CRUD Cuidador
void salvar_cuidador_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_cuidadores, "ab");
    FILE *fp_total = fopen(caminho_arquivo_total_cuidadores, "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fwrite(&total_cuidadores, sizeof(int), 1, fp_total);
    fwrite(&vetor_cuidadores[total_cuidadores - 1], sizeof(Cuidador), 1, fp);
    fclose(fp);
    fclose(fp_total);
}

void substituir_cuidador_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_cuidadores, "rb+");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fwrite(vetor_cuidadores, sizeof(Cuidador), total_cuidadores, fp);
    fclose(fp);
}

void remover_cuidador_arquivo(char matricula[])
{
    FILE *fp = fopen(caminho_arquivo_cuidadores, "rb+");
    FILE *fp_total = fopen(caminho_arquivo_total_cuidadores, "rb+");

    if (fp == NULL || fp_total == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    fread(&total_cuidadores, sizeof(int), 1, fp_total);
    fread(vetor_cuidadores, sizeof(Aluno), total_cuidadores, fp);

    int encontrado = 0;
    for (int i = 0; i < total_cuidadores; i++)
    {
        if (strcmp(vetor_cuidadores[i].matricula, matricula) == 0 && vetor_cuidadores[i].ocupado != 0)
        {
            vetor_cuidadores[i].ocupado = 0;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Cuidador com matrícula %s não encontrado.\n", matricula);
        fclose(fp);
        fclose(fp_total);
        return;
    }

    fseek(fp, 0, SEEK_SET);
    fwrite(vetor_cuidadores, sizeof(Cuidador), total_cuidadores, fp);
    fseek(fp_total, 0, SEEK_SET);
    fwrite(&total_cuidadores, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

void editar_cuidador_arquivo(Cuidador cuidador)
{
    FILE *fp = fopen(caminho_arquivo_cuidadores, "rb+");
    FILE *fp_total = fopen(caminho_arquivo_total_cuidadores, "rb+");

    if (fp == NULL || fp_total == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    int encontrado = 0;
    for (int i = 0; i < NUM_MAX_CADASTROS_CUIDADORES; i++)
    {
        if (strcmp(vetor_cuidadores[i].matricula, cuidador.matricula) == 0 && vetor_cuidadores[i].ocupado != 0)
        {
            vetor_cuidadores[i] = cuidador;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Cuidador com matrícula %s não encontrado.\n", cuidador.matricula);
        fclose(fp);
        fclose(fp_total);
        return;
    }

    fseek(fp, 0, SEEK_SET);
    fwrite(vetor_cuidadores, sizeof(Cuidador), NUM_MAX_CADASTROS_CUIDADORES, fp);
    fseek(fp_total, 0, SEEK_SET);
    fwrite(&total_cuidadores, sizeof(int), 1, fp_total);

    fclose(fp);
    fclose(fp_total);
}

void carregar_cuidadores_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_cuidadores, "rb");
    FILE *fp_total = fopen(caminho_arquivo_total_cuidadores, "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }

    fread(&total_cuidadores, sizeof(int), 1, fp_total);
    fread(vetor_cuidadores, sizeof(Cuidador), total_cuidadores, fp);
    fclose(fp);
    fclose(fp_total);
}

void salvar_observacao_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_observacoes, "ab");
    FILE *fp_total = fopen(caminho_arquivo_total_observacoes, "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fwrite(&total_observacoes, sizeof(int), 1, fp_total);
    fwrite(&vetor_observacoes[total_observacoes - 1], sizeof(Observacao), 1, fp);
    fclose(fp);
    fclose(fp_total);
}

void carregar_observacoes_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_observacoes, "rb");
    FILE *fp_total = fopen(caminho_arquivo_total_observacoes, "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }

    fread(&total_observacoes, sizeof(int), 1, fp_total);
    fread(vetor_observacoes, sizeof(Observacao), total_observacoes, fp);
    fclose(fp);
    fclose(fp_total);
}
