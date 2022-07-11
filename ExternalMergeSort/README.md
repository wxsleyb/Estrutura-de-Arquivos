# README do separa.c e intercala.c

1. Baixar o arquivo EstruturaArq-main desse meu repositório e colocar em Downloads
2. Extrair EstruturaArq-main.zip em Downloads
3. Agora é preciso abrir o terminal do linux e fazer:
4. digite: cd Downloads
5. depois da etapa 4 digite: cd EstruturaArq-main
6. depois da etapa 5 digite: cd ExternalMergeSort
7. depois da etapa 6, chame a função que divide os blocos digitando: gcc -o separa separa.c
8. depois da etapa 7 digite: ./separa
9. depois da etapa 8 digite a QUANTIDADE de BLOCOS que VOCÊ quer DIVIDIR o arquivo.
10. Pronto, arquivo foi dividido pela quantidade de blocos que você decidiu
11. Agora para intercalar os arquivos separados digite: gcc -o intercala intercala.c 
12. depois da etapa 11 digite: ./intercala
13. depois da etapa 12 digite a QUANTIDADE de BLOCOS que o arquivo FOI SEPARADO (a mesma qtd da etapa 9)
14. Pronto, será retornado a intercalação sendo feita e por fim o renomeio do arquivo para CEP_RJ_INTEIRO_ORDENADO.dat
