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
•  Armazenar os dados de forma persistente

usei o FILE *aquivo e o "a" para cadastrar no arquivo que ta pessoa.txt
o resto é mais sintaxe de C mesmo, e puxei a stuct tb para preencher o vetor
criei a função em void nesse caso pq n precisa retornar nada para anotar, talvez outras funções precisem*/

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

/*
2. Cadastrar novo evento
• Entrada de identificador, nome, data, endereço do local,
  limite máximo de participantes e restrição de idade.
• Verificar se o identificador já pertence a outro evento.
• Armazenar os dados de forma persistente.

Aqui da pra seguir praticamente a mesma lógica do cadastro
de pessoa, usando FILE *arquivo e o "a", mas dessa vez
no arquivo eventos.txt.

Puxar a struct Evento para preencher os campos e reaproveitar
as funções de validar data e CEP.

Precisamos criar uma função para verificar se o ID do evento
já existe, semelhante à que verifica o CPF.

Também precisamos validar se o limite de participantes é
positivo e se maiorDe18 recebe apenas 0 ou 1.

Deixei em void pq não precisa retornar nada.
*/

void cadastrarEvento(){
    
}

/*
3. Registrar participante em evento
• Informar o evento e a pessoa que será inscrita.
• Verificar se a pessoa e o evento existem.
• Verificar se a pessoa já está inscrita no evento.
• Validar as restrições de idade e de lotação.
• Registrar a inscrição de forma persistente.

Aqui vamos precisar consultar os três arquivos txt.
Primeiro verificar se o CPF existe em pessoas.txt e depois
se o ID existe em eventos.txt.

Depois verificar no inscricoes.txt se aquele CPF já está
vinculado ao mesmo ID de evento.

Vamos precisar de uma função para calcular a idade da pessoa
na data do evento e outra para contar quantas inscrições
aquele evento já possui.

Se passar por todas as verificações, usar o "a" para
registrar a inscrição no inscricoes.txt.

Usar a struct Inscricao para armazenar o CPF e o ID.
*/

void registrarParticipante();

/*
4. Buscar pessoa por CPF
• Permitir ao usuário informar um CPF.
• Localizar a pessoa cadastrada.
• Apresentar seus dados ou informar que não foi encontrada.

Aqui vamos usar FILE *arquivo com o "r", pq precisamos
apenas ler o pessoas.txt e não alterar nada.

Percorrer o arquivo linha por linha, preenchendo a struct
Pessoa e comparando o CPF informado com o CPF de cada
registro, podendo usar strcmp.

Se encontrar, mostrar os dados da pessoa.
Caso contrário, informar que não existe.

A função principal pode ser void, mas podemos criar uma
função auxiliar int para localizar e recuperar a pessoa,
assim conseguimos reaproveitar ela em outras questões.
*/

void buscarPessoaPorCPF(){
    
}

/*
5. Listar pessoas cadastradas
• Apresentar todas as pessoas cadastradas.
• Mostrar seus respectivos dados.

Essa é mais tranquila, basta abrir o pessoas.txt com o "r"
e percorrer todas as linhas do arquivo.

Usar a struct Pessoa para preencher os campos de cada
registro e mostrar os dados utilizando printf.

Não precisa comparar CPF nem fazer uma busca específica.

Caso o arquivo esteja vazio, informar que não existem
pessoas cadastradas.
*/

void listarPessoas(){
    
}

/*
6. Listar eventos cadastrados
• Apresentar todos os eventos cadastrados.
• Mostrar seus respectivos dados.
• Mostrar a quantidade atual de participantes.

Segue praticamente a mesma lógica de listar pessoas,
mas usando a struct Evento e o eventos.txt.

A diferença é que precisamos consultar o inscricoes.txt
para saber quantas pessoas estão inscritas em cada evento.

Da pra reaproveitar a função de contar participantes
que usamos na questão 3.

Essa função auxiliar pode ser int, pq precisa retornar
a quantidade de participantes.

A quantidade não precisa ser salva na struct Evento,
pq conseguimos calcular diretamente pelas inscrições.
*/

void listarEventos(){
    
}

/*
7. Listar participantes de um evento
• Permitir ao usuário informar um evento.
• Apresentar as pessoas inscritas nele.
• Informar caso não existam participantes.

Primeiro solicitar o ID do evento e verificar se existe
no eventos.txt.

Depois abrir o inscricoes.txt com o "r" e percorrer
os registros procurando inscrições com aquele ID.

Para cada CPF encontrado, consultar o pessoas.txt
para recuperar os dados da pessoa e mostrar na tela.

Da pra reaproveitar a função auxiliar de localizar
pessoa por CPF da questão 4.

Caso não encontre nenhuma inscrição com aquele ID,
informar que o evento não possui participantes.
*/

void listarParticipantesEvento(){
    
}

/*
8. Buscar eventos por cidade ou CEP
• Permitir ao usuário informar uma cidade ou CEP.
• Listar os eventos que ocorrem nesse local.

Aqui podemos perguntar primeiro se o usuário quer
buscar por cidade ou por CEP.

Abrir o eventos.txt com o "r" e percorrer os registros
preenchendo a struct Evento.

Como a struct Evento possui uma struct Endereco dentro
dela, podemos acessar os campos cidade e cep diretamente.

Usar strcmp para comparar o valor informado com o
campo correspondente.

Se a busca for por CEP, reaproveitar a função de
validarCEP.

Mostrar todos os eventos encontrados e não apenas
o primeiro, pq podem existir vários no mesmo local.
*/

void buscarEventosPorLocal(){
    
}

/*
9. Sair do programa
• Encerrar a execução do programa.
• Garantir que os dados cadastrados sejam preservados.

Como estamos gravando os dados nos arquivos txt sempre
que realizamos um cadastro, não precisamos salvar tudo
novamente quando o programa for encerrado.

Podemos controlar isso pelo próprio menu, usando
do while e switch case até o usuário selecionar 9.

Nesse caso nem precisamos necessariamente criar
uma função específica para sair.
*/

int main() {
    

    /*int validarCPF(char cpf[]);

    int validarCEP(char cep[]);

    int validarData(Data data);

    int cpfCadastrado(char cpf[]);*/

    void cadastrarPessoa();

    return 0;
}