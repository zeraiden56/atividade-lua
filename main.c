/*Implementar um programa em C que gerencie o cadastro de pessoas, eventos e inscrições de participantes.
Os dados deverão ser armazenados de forma persistente em arquivos de texto (.txt), permitindo que as informações cadastradas permaneçam
disponíveis mesmo após o encerramento do programa. O trabalho fará uso de structs aninhadas, manipualação de arquivos, texto,
busca e validação de dados.*/

#include <stdio.h>
#include <stdlib.h>
    
int main() {
    
    FILE *arquivo;

    char nome[50];
    float nota;

    arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL){
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    /*while ((c = fgetc(arquivo)) != EOF) {
        printf("%c", c);
    }*/
    
    /*while (fgets(linha, 200, arquivo) != NULL){
        printf("%s", linha);
    }*/

    while (fscanf(arquivo, "%49s %f", nome, &nota) == 2){
        printf("Aluno: %s | Nota: %.1f\n", nome, nota);
    }

    fclose(arquivo);

    return 0;
}