/*Implementar um programa em C que gerencie o cadastro de pessoas, eventos e inscrições de participantes.
Os dados deverão ser armazenados de forma persistente em arquivos de texto (.txt), permitindo que as informações cadastradas permaneçam
disponíveis mesmo após o encerramento do programa. O trabalho fará uso de structs aninhadas, manipualação de arquivos, texto,
busca e validação de dados.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 1. Endereço 
Campos: rua, número, cidade, CEP (formatado como string no formato "xxxxx-xxx").*/
typedef struct {
    char rua[50];
    int numero;
    char cidade[50];
    char cep[10];
} Endereco;

/* 2. Data 
Campos: dia, mês, ano*/
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

/*3. Pessoa 
Campos: nome, cpf, dataNascimento (Data), endereço (Endereço).*/
typedef struct {
    char nome[100];
    char cpf[12];
    Data dataNascimento;
    Endereco endereco;
} Pessoa;

/*4. Evento 
Campos: idEvento, nomeEvento, localEvento (Endereço), dataEvento (Data),  
númeroMaximoParticipantes (int), maiorDe18 (int): 1 se o evento é para maiores de 18 anos, 0 
se liberado para todas as idade*/
typedef struct {
    int idEvento;
    char nomeEvento[50];
    Endereco localEvento;
    Data dataEvento;
    int numeroMaximoParticipantes;
    int maiorDe18;
} Evento;

/*5. Inscrição 
Campos: idEvento e cpfPessoa. A inscrição deverá relacionar uma pessoa previamente 
cadastrada a um evento existente.*/
typedef struct {
    int idEvento;
    char cpfPessoa[12];
} Inscricao;


/*1.  Cadastrar nova pessoa 
•  Entrada de nome, CPF, data de nascimento e endereço completo. 
•  Validar CPF, data e CEP. 
•  Verificar se o CPF já está cadastrado antes de realizar o novo cadastro. 
•  Armazenar os dados de forma persistente*/

void cadastrarPessoa() {

    Pessoa pessoa;
    FILE *arquivo;

    printf("\n=== CADASTRO DE PESSOA ===\n");

    printf("Nome: ");
    scanf(" %99[^\n]", pessoa.nome);

    printf("CPF (somente números): ");
    scanf(" %11s", pessoa.cpf);

    if (!validarCPF(pessoa.cpf)) {
        printf("CPF inválido!\n");
        return;
    }

    int resultado = cpfCadastrado(pessoa.cpf);

    if (resultado == -1) {
        printf("Erro ao consultar os cadastros.\n");
        return;
    }

    if (resultado == 1) {
        printf("CPF já cadastrado!\n");
        return;
    }

    printf("Data de nascimento (dd/mm/aaaa): ");

    if (scanf("%d/%d/%d", &pessoa.dataNascimento.dia, &pessoa.dataNascimento.mes, &pessoa.dataNascimento.ano) != 3) {
        printf("Formato de data inválido!\n");
        return;
    }

    if (!validarData(pessoa.dataNascimento)) {
        printf("Data inválida!\n");
        return;
    }

    printf("Rua: ");
    scanf(" %49[^\n]", pessoa.endereco.rua);

    printf("Número: ");

    if (scanf("%d", &pessoa.endereco.numero) != 1) {
        printf("Número inválido!\n");
        return;
    }

    printf("Cidade: ");
    scanf(" %49[^\n]", pessoa.endereco.cidade);

    printf("CEP (xxxxx-xxx): ");
    scanf(" %9s", pessoa.endereco.cep);

    if (!validarCEP(pessoa.endereco.cep)) {
        printf("CEP inválido!\n");
        return;
    }

    arquivo = fopen("pessoas.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int gravado = fprintf(arquivo, "%s;%s;%02d/%02d/%04d;%s;%d;%s;%s\n",
        pessoa.nome,
        pessoa.cpf,
        pessoa.dataNascimento.dia,
        pessoa.dataNascimento.mes,
        pessoa.dataNascimento.ano,
        pessoa.endereco.rua,
        pessoa.endereco.numero,
        pessoa.endereco.cidade,
        pessoa.endereco.cep
    );

    int fechamento = fclose(arquivo);

    if (gravado < 0 || fechamento == EOF) {
        printf("Erro ao gravar os dados!\n");
        return;
    }

    printf("Pessoa cadastrada com sucesso!\n");
}

int main() {
    

    /*int validarCPF(char cpf[]);

    int validarCEP(char cep[]);

    int validarData(Data data);

    int cpfCadastrado(char cpf[]);*/

    void cadastrarPessoa();

    return 0;
}