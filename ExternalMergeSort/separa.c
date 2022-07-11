#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int compare(const void *e1, const void *e2) // função que auxilia a ordenação pelo CEP, poderia ser por logradouro, cidade, etc
{
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8); // só teria que mudar o cep aqui pelo que preferir
}

int main(int argc, char **argv)
{
    FILE *initial_file;                                         // declarando o arquivo inicial e o arquivo
    Endereco *e1;                                                        // criando um ponteiro de Endereco
    long sizefile, sizeregister, quantityregister, quantityfileperblock; // variaveis sobre tamanhos, quantidade registros e a quantidade de arquivos por bloco
    char name_file_cep[15];                                              // char para armazenar o nome personalizado do arquivo
    int N;                                                               // numero de blocos a ser dividido

    initial_file = fopen("CEP_RJ.dat", "rb");                         // abre o arquivo
    fseek(initial_file, 0, SEEK_END);                              // faz com quem vá para o final do arquivo
    sizefile = ftell(initial_file);                                // calcula o tamanho do arquivo em bytes
    sizeregister = sizeof(Endereco);                               // calcula o tamanho do registro
    quantityregister = sizefile / sizeregister;                    // calcula a quantidade de registros
    printf("Digite em QUANTOS blocos SERÁ DIVIDIDO o ARQUIVO:  "); // escolhe a quantidade de blocos
    scanf("%d", &N);

    quantityfileperblock = quantityregister / N;                  // calcula a quantidade de registros por blocos
    e1 = (Endereco *)malloc(quantityfileperblock * sizeregister); // aloca uma memoria para o arquivo
    rewind(initial_file);                                         // volta ao inicio do arquivo (estava no final devido ao SEEK_END)

    for (int i = 1; i <= N; i++) // loop até a quantidade de blocos a ser dividido
    {
        if (N % 2 == 1)
        {
            printf("\nVoce digitou um valor impar, tente novamente usando um valor par\n"); // não pode botar quantidade de blocos impar
            break;
        }

        sprintf(name_file_cep, "CEP_RJ%d.dat", i);        // renomeia o nome do arquivo da forma que você quer (CEP_RJ1.dat, CEP_RJ2.dat,...)
        FILE *final_file = fopen(name_file_cep, "wb"); // abre o arquivo final pra armazenar esses arquivos divididos

        fread(e1, sizeregister, quantityfileperblock, initial_file); // lê o arquivo inicial cep.dat
        qsort(e1, quantityfileperblock, sizeregister, compare);      // ordena o arquivo pelo CEP dos endereços (ver a funçao compara)
        fwrite(e1, sizeregister, quantityfileperblock, final_file);  // escreve no arquivo final essa parte dividida do arquivo
        printf("Bloco %d ordenado e separado\n", i);
        //remove(name_file_cep);

        fclose(final_file); // fecha o arquivo final
    }

    free(e1);             // libera a memoria alocada e1
    fclose(initial_file); // fecha o arquivo inicial
}
