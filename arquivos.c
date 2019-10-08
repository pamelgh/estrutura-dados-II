/*CIÊNCIA DA COMPUTAÇÃO, UFFS, 3º FASE
ALUNA:  PÂMELA GHENO.
EMAIL: pgpgpame@gmail.com
ESTRUTURA DE DADOS II*/

//Cadastrar produto e escrevê-lo num arquivo de texto


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

typedef struct prod{
	char cod[50];
	char nome[80];
	char preco[80];
}tp_produto; //tipo produto;


void insere(FILE *file, tp_produto *cab){
		file = fopen("t4.txt", "ab");
		fprintf(file,"\n_________________________\n");
		printf("Preencha as informações:\n");
		printf("Código:\n");
		fprintf(file,"Código: ");
		scanf("%s", &cab->cod);
		fputs(cab->cod, file);
		fprintf(file,"\n");
		printf("\n");
		getchar();
		fprintf(file,"Nome: ");
		printf("Nome:\n");
		fgets(cab->nome, 20, stdin);
		fputs(cab->nome, file);

		printf("Preco\n");
		fprintf(file,"Preço: ");
		scanf("%s", &cab->preco);
		fputs(cab->preco, file);
		fprintf(file,"\n_________________________");
		getchar();
		printf("\n");
		fclose(file);
}

void mostra(FILE *file){
	file = fopen("t4.txt", "r");
	char c;
	while(feof(file) == 0){
		c = fgetc(file);
		putchar(c);
	}
}


int main(){
	int op;
	FILE *file;
	file = fopen("t4.txt", "wb");

	tp_produto *nodo = (tp_produto*) calloc(0,sizeof(tp_produto));

do{
		printf("\n\n\t\t-- O que deseja fazer? --\n\n");
		printf("\t\t[1] 'Cadastrar produto'\n");
		printf("\t\t[2] 'Exibir produto'\n");
		printf("\t\t[0] 'Sair'\n");
		scanf("%d", &op);
		system("clear");

		switch (op){

			case 1:
				insere(file,nodo);
					break;
			case 2:
				mostra(file);
					break;
		}

	}while (op != 0);
	fclose(file);

	return 0;
}
