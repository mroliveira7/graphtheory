#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INF 999999

struct lista{
	int vertice;
	int cor;
	int eh_vizinho;
	int distancia;
	struct lista *vizinhos;
	struct lista *end_vizinho;
	struct lista *prox;
};

int CIDADES[50];
int NCIDADES = 0;

int insere(struct lista **p, int num, int eh_vizinho, struct lista *adr){

	struct lista *aux = malloc(sizeof(struct lista));
	aux->vertice = num;
	aux->cor = BRANCO;
	aux->distancia = INF;
	aux->eh_vizinho;
	if(eh_vizinho == 1){
		aux->end_vizinho = adr;
		aux->eh_vizinho = 1;
		aux->vizinhos = NULL;
	}
	aux->prox = (*p);
	(*p) = aux;
};

struct lista * consulta(struct lista *p, int vertice){
	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
		if(aux->vertice == vertice)
			return aux;
	return 0;
};

int insereVizinho(struct lista **p, int vizinho,struct lista *aux, struct lista *aux2){
	
	insere(&(aux->vizinhos),vizinho,1,aux2);
};

void printGrafo(struct lista *p){

	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
	{
		if (aux->eh_vizinho != 1)
			printf("%d [", aux->vertice);
		else
			printf("%d ", aux->vertice);

		if (aux->vizinhos != NULL)
			printGrafo(aux->vizinhos);
		if (aux->eh_vizinho != 1)
			printf("]\n");
	}
};

int BFS(struct lista *p, int start){

	struct lista *start_adr = consulta(p,start), *aux_adr, *aux2;
	int i, fim_fila = 0, maior_d = 0;
	struct lista * fila[100];

	for (aux2 = p; aux2 != NULL; aux2 = aux2->prox){
		aux2->cor = BRANCO;
		aux2->distancia = 999999;
	}

	start_adr->cor = CINZA;
	start_adr->distancia = 0;
	fila[0] = start_adr;
	fim_fila++;

	while(fim_fila != 0)
	{
		aux_adr = fila[0];
		for(i = 0; i < fim_fila-1; i++) fila[i] = fila[i+1];
		fim_fila--;
		for(aux2 = aux_adr->vizinhos; aux2 != NULL; aux2 = aux2->prox)
		{
			if(aux2->end_vizinho->cor == BRANCO){
				aux2->end_vizinho->cor = CINZA;
				aux2->end_vizinho->distancia = aux_adr->distancia + 1;
				if(aux2->end_vizinho->distancia >= maior_d)
					maior_d = aux2->end_vizinho->distancia;
				fila[fim_fila] = aux2->end_vizinho;
				fim_fila++;
			}
		}
		aux_adr->cor = PRETO;
	}
	return maior_d;
};

int main(){

	int num_teste = 1;
	do{

		struct lista *root = NULL, *adr_c1, *adr_c2; 
		int i, n_vertices, c1, c2, start;

		scanf("%d",&n_vertices);
		if(n_vertices == 0)
			break;

		for(i = 0; i < n_vertices; i++)
			insere(&root,i+1,0,NULL);

		for(i = 0; i < n_vertices-1; i++){
			scanf("%d %d",&c1,&c2);
			adr_c1 = consulta(root,c1);
			adr_c2 = consulta(root,c2);
			insereVizinho(&root,c1,adr_c2,adr_c1);
			insereVizinho(&root,c2,adr_c1,adr_c2);
		}
		//printGrafo(root);
		int menor_d = 999999, central, temp = 999999;
		for (i = 0; i < n_vertices; i++)
		{
			temp = BFS(root,i+1);
			if (temp < menor_d)
			{
				menor_d = temp;
				central = i+1;
			}
		}

		printf("Teste %d\n", num_teste);
		printf("%d\n", central);

		printf("\n\n");
		num_teste++;

	}while(1);

	return 0;
}