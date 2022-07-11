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

int compare(const void *e1, const void *e2) // função que auxilia a fazer a intercalação
{
	return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8); // nesse caso auxiliando pelo cep
}

void merge(char *file, char *next_file, char *output) // função intercala
{
	FILE *a, *b, *saida; // abrindo os arquivos a(arquivo), b(arquivo que vem depois do a) e a saida que será o arquivo intercalado de "a" e "b"
	Endereco ea, eb;

	a = fopen(file, "r");
	b = fopen(next_file, "r");
	saida = fopen(output, "wb");

	fread(&ea, sizeof(Endereco), 1, a); // lendo o arquivo a
	fread(&eb, sizeof(Endereco), 1, b); // lendo o arquivo que vem depois do a

	while (!feof(a) && !feof(b))
	{
		if (compare(&ea, &eb) < 0)
		{
			fwrite(&ea, sizeof(Endereco), 1, saida);
			fread(&ea, sizeof(Endereco), 1, a);
		}
		else
		{
			fwrite(&eb, sizeof(Endereco), 1, saida);
			fread(&eb, sizeof(Endereco), 1, b);
		}
	}

	while (!feof(a))
	{
		fwrite(&ea, sizeof(Endereco), 1, saida);
		fread(&ea, sizeof(Endereco), 1, a);
	}
	while (!feof(b))
	{
		fwrite(&eb, sizeof(Endereco), 1, saida);
		fread(&eb, sizeof(Endereco), 1, b);
	}

	fclose(a);
	fclose(b);
	fclose(saida);
}

int main(int argc, char **argv)
{
	char output[15], file[15], next_file[15]; // char para o nome personalizado
	int next_name = 0;
	int quantity_blocks;	   // quantidade de blocos
	char file_name_merged[15]; // char para o nome personalizado depois que estiver intercalado
	int initial_blocks;		   // variavel pra registrar os blocos iniciais

	printf("\nDigite em QUANTOS BLOCOS o ARQUIVO foi SEPARADO: "); // digitar a quantidade de blocos que tinha sido separado o arquivo
	scanf("%d", &quantity_blocks);
	initial_blocks = quantity_blocks;			 // igualando os blocos iniciais com a quantidade de blocos passada
	int quantity_blocks_pairs = quantity_blocks; // quantidade de pares de bloco igualado a quantidade de blocos (pq só pode valor par)
	int next_int = 1;							 // inteiro que da o nome ao arquivo cep

	while (quantity_blocks_pairs >= 2) // para o while funcionar apenas com numeros pares
	{

		next_name = 1; // inteiro que vai dar nome ao arquivo de saida
		while (next_int <= quantity_blocks)
		{

			sprintf(file, "CEP_RJ%d.dat", next_int);
			sprintf(next_file, "CEP_RJ%d.dat", next_int + 1);
			sprintf(output, "CEP_RJ%d.dat", next_name + quantity_blocks);
			printf("Arquivo %s intercalado com o proximo arquivo %s e se transformando em %s\n", file, next_file, output);
			merge(file, next_file, output); // faz o intercala do arquivo com o arquivo que vem depois dele e escreve na saida um novo arquivo
			remove(file);					// deleta o arquivo que ja foi intercalado
			remove(next_file);				// deleta o arquivo que ja foi intercalado
			next_name++;
			next_int += 2; // passando de 2 em 2 pq estão sendo pegos 2 arquivos a cada while
		}
		quantity_blocks_pairs = quantity_blocks_pairs / 2; // a quantidade de blocos pares vai sendo dividida pela metade a cada passo do while
		quantity_blocks += quantity_blocks_pairs;
	}
	printf("\nTodos os %d blocos da parte inicial foram intercalados e transformados em um só arquivo chamado CEP_RJ%d.dat\n", initial_blocks, next_int);
	printf("\nArquivo CEP_RJ%d.dat renomeado para CEP_RJ_INTEIRO_ORDENADO.dat\n", next_int);
	sprintf(file_name_merged, "CEP_RJ%d.dat", next_int);
	rename(file_name_merged, "CEP_RJ_INTEIRO_ORDENADO.dat"); // renomeia o arquivo intercalado para o CEP_RJ_INTEIRO_ORDENADO.dat
}
