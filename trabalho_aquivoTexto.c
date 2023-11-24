#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
	//variaveis
	FILE *arq1, *arq2, *arq3;
	char str_arq1[100], str_arq2[100];
	int cont = 0;

	arq1 = fopen("Arquivo.txt", "r");//abre os arquivos para leitura
	arq2 = fopen("Arquivo2.txt", "r");
	arq3 = fopen("Arquivo3.txt", "w");//abre arquivo para escrita

	/*pega cada nome do arq1 e compara com todos os nomes do arq2, se os nomes forem iguais
	armazena em arq3 adiciona um no contador e vaia para o proximo nome do arq 1*/
	while(fgets(str_arq1, 100, arq1) != NULL){
		while(fgets(str_arq2, 100, arq2) != NULL){
			if(strcmp(str_arq1, str_arq2) == 0){
				fprintf(arq3, "%s", str_arq1);
				cont++;
				break;
			}
		}
		rewind(arq2);
	}

	//fecha arquivos
	fclose(arq1);
	fclose(arq2);
	fclose(arq3);

	//exibe mensagem com o numero de nomes copiados para arq3
	printf("Foram encontrados %d nomes duplicados e entao copiados para o Arquivo3!\n", cont);
	
	system("pause");
	
	return 0;
}
