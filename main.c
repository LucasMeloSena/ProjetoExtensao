#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

#define NUM_MAX_CAD 1024


typedef struct Pessoa {
    int ocupado;
	char nome[256];
	char cpf[13];
	int idade;
	char sexo;
	float salario;

} Pessoa;


Pessoa vetor_pessoas[NUM_MAX_CAD];
int total_pessoas = 0;

int tela_menu_opcoes();

void tela_cadastrar();

void tela_pesquisar();
void tela_remover();

void tela_relatorio();

int tela_sair();


int main()
{
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");

    int sair = 0;
    int opcao;

    for(int i=0; i < NUM_MAX_CAD; i++)
    {
        vetor_pessoas[i].ocupado = 0;
    }


    do
    {
        opcao = tela_menu_opcoes();

        switch(opcao)
        {
            case 1:
                tela_cadastrar();
            break;
            case 2:
                tela_pesquisar();
            break
            case 3:
                tela_remover();
            break;
            case 4:
                tela_relatorio();

            break;
            case 5:
                sair = tela_sair();

            break;
            default:
                printf("\nOp��o Inv�lida !!! \n");
                system("pause");
        }

    }while(sair == 0);

    system("cls");
    printf("\nFim da execu��o do programa!\n");

    return 0;
}

int tela_menu_opcoes()
{
    int opcao;

    system("cls");
    printf("Menu de Op��es \n");
    printf("1 - Cadastrar \n");
    printf("2 - Pesquisar \n");
    printf("3 - Remover \n");
    printf("4 - Relat�rio \n");
    printf("5 - Sair \n\n");

    printf("Escolha uma op��o: ");
    int erro = scanf("%d", &opcao);

    if(erro != 1) {
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
    char cpf[13];
	int idade;
	char sexo, strSexo[3];
    float salario;

    do {
        system("cls");
        printf("1 - Cadastrar \n");

        if(total_pessoas >= NUM_MAX_CAD)
        {
            printf("\nErro: O cadastro j� atingiu sua capacidade m�xima!\n");
            system("pause");
            break;
        }

        do
        {
            erro = 0;

            printf("\nDigite o nome: ");
            scanf(" %255[^\n]", nome);

            fflush(stdin);


            if(strlen(nome) > 254)
            {
                erro = 1;
                printf("ERRO: O nome pode possuir no m�ximo 254 carracteres!\n");
            }
            if(strlen(nome) < 3) {
                erro = 1;
                printf("ERRO: O nome deve possuir pelo menos 3 (tr�s) carracteres!\n");
            }

        } while(erro == 1);

        do
        {
            erro = 0;

            printf("\nDigite o CPF: ");

            scanf(" %12[^\n]", cpf);

            fflush(stdin);

            if(strlen(cpf) != 11)
            {
                erro = 1;
                printf("ERRO: O CPF deve possuir 11 (onze) d�gitos!\n");
            }

        }while(erro == 1);


        do
        {
            printf("\nDigite a idade: ");
            erro = scanf("%d", &idade);

            fflush(stdin);

            if(erro != 1)
            {
                printf("ERRO: Digite um valor inteiro v�lido!\n");
            }
            else if(idade < 1 || idade > 120)
            {
                erro = -1;
                printf("ERRO: A idade deve estar entre 1 e 120 anos!\n");
            }

        }while(erro != 1);


        do
        {
            erro = 0;

            printf("\nDigite o sexo (M / F): ");

            scanf(" %2[^\n]", strSexo);

            fflush(stdin);

            if(strlen(strSexo) == 1)
            {
                sexo = toupper(strSexo[0]);
            }
            else
            {
                erro = 1;
            }

            if( !(sexo == 'M' || sexo == 'F') || erro == 1 )
            {
                erro = 1;
                printf("ERRO: S�o aceitos apenas os valores 'M' ou 'F'!\n");
            }

        }while(erro == 1);


        do
        {
            printf("\nDigite o sal�rio: R$ ");
            erro = scanf("%f", &salario);

            fflush(stdin);

            if(salario < 1320.0 || erro != 1)
            {
                erro = -1;
                printf("ERRO: o sal�rio n�o pode ser menor que R$ 1320,00 !\n");
            }

        }while(erro != 1);

        idxPesquisa = -1;

        for(int i=0; i < NUM_MAX_CAD; i++)
        {
            if(vetor_pessoas[i].ocupado == 1) {

                if( strcmp(vetor_pessoas[i].cpf, cpf) == 0)
                {
                    idxPesquisa = i;
                    break;
                }
            }
        }


        if(idxPesquisa != -1)
        {
            printf("\nErro: N�o foi poss�vel inserir os dados pois j� existe uma pessoa com o mesmo cpf no cadastro:\v");

            printf("\nPessoa com o mesmo CPF: \n");
            printf("CPF:     %s\n", vetor_pessoas[idxPesquisa].cpf);
            printf("Nome:    %s\n", vetor_pessoas[idxPesquisa].nome);
            printf("Idade:   %d\n", vetor_pessoas[idxPesquisa].idade);
            printf("Sexo:    %c\n", vetor_pessoas[idxPesquisa].sexo);
            printf("Salario: R$ %.2f\n\n",vetor_pessoas[idxPesquisa].salario);
            system("pause");
        }
        else
        {
            for(int i=0; i < NUM_MAX_CAD; i++)
            {
                if(vetor_pessoas[i].ocupado == 0)
                {
                    vetor_pessoas[i].ocupado = 1;

                    strcpy(vetor_pessoas[i].nome, nome);
                    strcpy(vetor_pessoas[i].cpf, cpf);
                    vetor_pessoas[i].idade = idade;
                    vetor_pessoas[i].sexo = sexo;
                    vetor_pessoas[i].salario = salario;
                    total_pessoas = total_pessoas + 1;

                    printf("\nDados cadastrados com sucesso! \n");
                    system("pause");

                    break;
                }
            }
        }

        do{

            printf("\nGostaria de cadastrar outra pessoa? (s/n): ");
            scanf(" %c", &ch);

            fflush(stdin);

            ch = toupper(ch);

        }while(!(ch == 'S' || ch == 'N'));

        if(ch == 'S')
        {
            continuar = 1;
        }
        else{
            continuar = 0;
        }

    } while(continuar == 1);
}

void tela_pesquisar()
{
    int continuar;

    char ch;

    int erro;

    int idxPesquisa = -1;

    char cpf[13];

    do{

        system("cls");
        printf("2 - Pesquisar \n");

        do
        {
            erro = 0;

            printf("\nDigite o CPF: ");
            scanf(" %12[^\n]", cpf);

            fflush(stdin);

            if(strlen(cpf) != 11)
            {
                erro = 1;
                printf("ERRO: O CPF deve possuir 11 (onze) d�gitos!\n");
            }

        }while(erro == 1)

        idxPesquisa = -1;

        for(int i=0; i<NUM_MAX_CAD; i++){

            if(vetor_pessoas[i].ocupado == 1)
            {
                if(strcmp(vetor_pessoas[i].cpf, cpf) == 0){

                    idxPesquisa = i;

                    break;
                }
            }
        }

        if(idxPesquisa != -1)
        {
            printf("\nPessoa Encontrada: \n");
            printf("CPF:     %s\n", vetor_pessoas[idxPesquisa].cpf);
            printf("Nome:    %s\n", vetor_pessoas[idxPesquisa].nome);
            printf("Idade:   %d\n", vetor_pessoas[idxPesquisa].idade);
            printf("Sexo:    %c\n", vetor_pessoas[idxPesquisa].sexo);
            printf("Salario: R$ %.2f\n\n",vetor_pessoas[idxPesquisa].salario);
            system("pause");
        }
        else
        {
            printf("\nN�o foi encontrada uma pessoa com o cpf informado!\n\n");
            system("pause");
        }

        do{

            printf("\nGostaria de pesquisar outra pessoa?  (s/n): ");
            scanf(" %c", &ch);

            fflush(stdin);

            ch = toupper(ch);

        }while(!(ch == 'S' || ch == 'N'));

        if(ch == 'S')
        {
            continuar = 1;
        }
        else{
            continuar = 0;
        }

    } while(continuar == 1);
}

void tela_remover()
{
    int continuar;

    char ch;

    int erro;

    int idxPesquisa = -1;

    char cpf[13];

    do
    {
        system("cls");
        printf("3 - Remover \n\n");

        do
        {
            erro = 0;

            printf("\nDigite o CPF: ");

            scanf(" %12[^\n]", cpf);

            fflush(stdin);

            if(strlen(cpf) != 11)
            {
                erro = 1;
                printf("ERRO: O CPF deve possuir 11 (onze) d�gitos!\n");
            }

        }while(erro == 1);


        idxPesquisa = -1;

        for(int i = 0; i < NUM_MAX_CAD; i++) {

            if(vetor_pessoas[i].ocupado == 1)
            {
                if(strcmp(vetor_pessoas[i].cpf, cpf) == 0){

                    total_pessoas = total_pessoas - 1;

                    vetor_pessoas[i].ocupado = 0;
                    idxPesquisa = i;

                    break;
                }
            }
        }

        if(idxPesquisa != -1)
        {
            printf("\nPessoa removida com sucesso!\n");
        }
        else
        {
            printf("\nN�o foi poss�vel remover a pessoa do cadastro!\n");
        }

        system("pause");

        do{

            printf("\nGostaria de remover outra pessoa?  (s/n): ");
            scanf(" %c", &ch);

            fflush(stdin);

            ch = toupper(ch);

        }while(!(ch == 'S' || ch == 'N'));

        if(ch == 'S')
        {
            continuar = 1;
        }
        else{
            continuar = 0;
        }

    }while(continuar);
}

void tela_relatorio()
{
    system("cls");
    printf("4 - Relat�rio \n\n");

    printf("Total de Pessoas Cadastradas: %d\n\n", total_pessoas);

    for(int i=0; i<NUM_MAX_CAD; i++){

        if(vetor_pessoas[i].ocupado == 1)
        {
            printf("CPF:     %s\n", vetor_pessoas[i].cpf);
            printf("Nome:    %s\n", vetor_pessoas[i].nome);
            printf("Idade:   %d\n", vetor_pessoas[i].idade);
            printf("Sexo:    %c\n", vetor_pessoas[i].sexo);
            printf("Salario: R$ %.2f\n\n",vetor_pessoas[i].salario);
        }
    }

    system("pause");
}

int tela_sair()
{
    char ch;

    int sair;
    system("cls");
    printf("5 - Sair \n\n");

    do{
        printf("\nDeseja mesmo sair?  (s/n): ");
        scanf(" %c", &ch);

        fflush(stdin);

        ch = toupper(ch);

        if(ch == 'S')
        {
            sair = 1;
        }
        else if(ch == 'N')
        {
            sair = 0;
        }

    }while(!(ch == 'S' || ch == 'N'));

    return sair;
}
