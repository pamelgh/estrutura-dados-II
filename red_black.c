/*
UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
Estrutura de Dados II - 3° Fase - Ciência da Computação
Professor: Doglas André Finco
RED-BLACK TREE
Alunos:
        Augusto Miguel De Araújo Lemes
        Pamela Gheno
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct avl_node{
  int info;
  struct avl_node *esq;
  struct avl_node *dir;
  struct avl_node *pai;
  int color;
}avl_node;

//___________funçao para imprimir______________
void padding ( char ch, int n ){
  for (int i = 0; i < n; i++ )
    putchar ( ch );
}
void imprimeArvore ( avl_node *root, int level ){
  if ( root == NULL ) {
    padding ( '\t', level+1 );
    puts ( "~" );
  }
  else {
    imprimeArvore ( root->dir, level + 1 );
    padding ( '\t', level+1 );
    if(root->color == 0)
      printf ( "\e[0;37m(%d)\n\e[0m",root->info);
    else
      printf ( "\e[0;31m(%d)\n\e[0m",root->info);
    imprimeArvore ( root->esq, level + 1 );
  }
}
//_______________________________________________

void* rebalancear(avl_node* raiz, int chave){
  avl_node *nodop, *tio, *avo, *filho = raiz;

  //Encontra o  "filho".
	while(filho->info != chave){
		if(filho->info > chave)
			filho = filho->esq;
		else
			filho = filho->dir;
	}
	if((filho == raiz) || (filho->pai->color == 0))
		return raiz;
	avo = filho->pai->pai;

  //encontra o tio
	if(avo->info > chave)
		tio = avo->dir;
	else
		tio = avo->esq;

    //O tio é vermelho

    if((tio != NULL) && (tio->color == 1)){
		do{
			tio->color = filho->pai->color = 0;
			avo->color = 1;
			if((avo->pai != NULL) && (avo->pai->color == 1)){
				filho = avo; // para continuar verificando
				chave = filho->info;
				avo = avo->pai->pai;
				if(avo->info > chave)
					tio = avo->dir;
				else
					tio = avo->esq;
			}else
				return raiz;
		}while((tio != NULL) && (tio->color == 1));

	}

  // Se o tio for preto.
	if((filho->pai)->info < chave && filho->pai->info < avo->info ||
		(filho->pai)->info > chave && filho->pai->info > avo->info){
		nodop = filho->pai;
		filho->pai = nodop->pai; //
		nodop->pai = filho;

		if(avo->info > chave){ // Rotação à direita
			avo->esq = filho;
			filho->esq = nodop;
			nodop->dir = NULL;
		}
		else{
			avo->dir = filho; // Rotação à esquerda
			filho->dir = nodop;
			nodop->esq = NULL;
		}
		filho = nodop;
		chave = filho->info;
	}
	filho = filho->pai; //Continua com as rotações simples e recolorações para os casos Left-Left e Right-Right.
	filho->pai = avo->pai;
	filho->color = 0;
	avo->color = 1;
	avo->pai = filho;

	if(avo->info > chave){
    avo->esq = filho->dir;
		filho->dir = avo;
	}
	else{
		avo->dir = filho->esq;
    filho->esq = avo;
	}
	if(filho->pai != NULL){
		if(filho->pai->info > chave)
			filho->pai->esq = filho;
		else
			filho->pai->dir = filho;
	}
	else return filho;
	return raiz;
}

//procura e insere no lado certo
void* inserirNodo(avl_node* raiz, avl_node* nodo, int chave){
    if(raiz == NULL){
      raiz = (avl_node*) calloc(1,sizeof(avl_node));
      raiz->info = chave;
      raiz->color = 1;
      raiz->pai = nodo;
      return raiz;
    }
    if(chave == raiz->info){
      printf("Nodo já inserido!\n");
      return raiz;
    }
   if(chave > raiz->info){
      //Insere à direita
      raiz->dir = inserirNodo(raiz->dir, raiz, chave);
    }else{
      //Insere à esquerda
      raiz->esq =   inserirNodo(raiz->esq, raiz, chave);
      }
    return raiz;
  }


//preencher novo nodo
int criaNodo(){
  int x;
  printf("Digite a chave: ");
  scanf("%d", &x);
  return x;
}


 int main(){
  avl_node* nodo = NULL; //inicia raiz da árvore vazia
  int op,x;
  do{
    printf("\t\t__________ RED-BLACK TREE ____________\n");
    printf("\n");
    imprimeArvore(nodo, 1);
    printf("\n");
    printf("\t\t {1}  Inserir\n");
    printf("\t\t {0}  Sair\n");
    printf("\t\t______________________________________\n\n");
    scanf("%d", &op);
    system("clear");
    switch(op){
      case 1:
        x = criaNodo();
        nodo = inserirNodo(nodo, NULL, x); //insere elemento
        nodo = rebalancear(nodo,x); //corrige as quebras de invariantes
	      nodo->color = 0; //sempre seta a raiz preto;
          break;
    }
  }while(op != 0);
}
