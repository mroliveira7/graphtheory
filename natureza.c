#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

struct lista
{
	int vertice;
	char *nome;
	int cor;
	struct lista *vizinhos;
	struct lista *end_vizinho;
	struct lista *prox;
};

int insere(struct lista **p, int num, char *nome, struct lista *adr){

	struct lista *aux = malloc(sizeof(struct lista));
	aux->vertice = num;
	aux->nome = malloc((strlen(nome)+1) * sizeof(char));
	strcpy(aux->nome,nome);
	aux->cor = BRANCO;
	if(num == 0)
		aux->end_vizinho = adr;
	aux->prox = (*p);
	(*p) = aux;
};

struct lista * consulta(struct lista *p, char *nome){
	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
		if(strcmp(nome,aux->nome) == 0)
			return aux;
	return 0;
};
int insereVizinho(struct lista **p, char *nome, char *vizinho,int num_criatuta,struct lista *aux, struct lista *aux2){
	
	insere(&(aux->vizinhos),num_criatuta,vizinho,aux2);
};

void printGrafo(struct lista *p){

	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
	{
		if (aux->vertice != 0)
			printf("%s [", aux->nome);
		else
			printf("%s ", aux->nome);

		if (aux->vizinhos != NULL)
			printGrafo(aux->vizinhos);
		if (aux->vertice != 0)
			printf("]\n");
	}
};

int DFSvisit(struct lista *p,int *maior,int *cont){

	struct lista *aux;
	(*cont)++;
	p->cor = CINZA;
	for(aux = p->vizinhos; aux != NULL; aux = aux->prox)
	{
		if(aux->end_vizinho->cor == BRANCO)
			DFSvisit(aux->end_vizinho, maior, cont);
	}
	p->cor = PRETO;
};

int DFS(struct lista *p,int *maior,int *cont){

	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox){
		if (aux->cor == BRANCO){
			DFSvisit(aux,maior,cont);
			if(*cont > *maior){
				*maior = *cont;
			}
			*cont = 0;
		}
	}
};

int main(){

	do{
		struct lista *root = NULL, *adr_c, *adr_p;
		char criatura[30], predador[30];
		int C,R,i,num_criatuta = 1, maior = 0,cont = 0;

		scanf("%d %d",&C,&R);
		if(C == 0 && R == 0)
			break;

		for (i = 0; i < C; i++)
		{
			scanf("%s",criatura);
			insere(&root,num_criatuta,criatura,NULL);
			num_criatuta++;
		}
		for (i = 0; i < R; i++)
		{
			scanf("%s %s",criatura, predador);
			adr_c = consulta(root,criatura);
			adr_p = consulta(root,predador);
			insereVizinho(&root,criatura,predador,0,adr_p,adr_c);
			insereVizinho(&root,predador,criatura,0,adr_c,adr_p);
		}
		//printGrafo(root);
		DFS(root,&maior,&cont);
		printf("%d\n", maior);
		maior = 0;
		cont = 0;

	}while(1);
}