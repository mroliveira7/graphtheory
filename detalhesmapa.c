#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INF 999999

struct lista{
	int vertice;
	int cor;
	int eh_vizinho;
	int custo;
	struct lista *vizinhos;
	struct lista *end_vizinho;
	struct lista *prox;
};

typedef struct listaCustos{
	int v;
	int u;
	int custo;
	struct listaCustos *prox;
}listaCustos;

int insere(struct lista **p, int num, int eh_vizinho, struct lista *adr){

	struct lista *aux = malloc(sizeof(struct lista));
	struct lista *aux2;
	aux->vertice = num;
	aux->cor = BRANCO;
	if(eh_vizinho == 1){
		aux->end_vizinho = adr;
		aux->eh_vizinho = 1;
		aux->vizinhos = NULL;
	}
	if((*p) == NULL){
		(*p) = aux;
		aux->prox = NULL;
	}
	else{
		aux->prox = (*p);
		(*p) = aux;
	}
};

struct lista * consulta(struct lista *p, int vertice){
	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
		if(aux->vertice == vertice)
			return aux;
	return 0;
};

void addFila(struct listaCustos **p, int u, int v, int custo){

	struct listaCustos *aux = malloc(sizeof(struct listaCustos)), *aux2;
	aux->u = u;
	aux->v = v;
	aux->custo = custo;
	aux->prox = NULL;

	if((*p) == NULL){
		(*p) = aux;
		return;
	}
	for(aux2 = (*p); (aux2 != NULL) && (aux2->prox != NULL) && (aux2->prox->custo < custo); aux2 = aux2->prox);

	if(aux2 == (*p))
	{
		if((*p)->custo < custo){
			aux->prox = (*p)->prox;
			(*p)->prox = aux;
		}
		else{
			aux->prox = (*p);
			(*p) = aux;
		}
	}
	else{
		aux->prox = aux2->prox;
		aux2->prox = aux;
	}
};

struct listaCustos * rmFila(struct listaCustos **p){

	struct listaCustos *r;
	if(*p == NULL)
		return NULL;
	struct listaCustos *aux = (*p);
	r = (*p);
	(*p) = aux->prox;
	return r;
};

int sortfunc(const void *a, const void *b){
	listaCustos * orderA = (listaCustos *) a;
	listaCustos * orderB = (listaCustos *) b;
	return ( orderA->custo - orderB->custo );
};

int main(){

		struct lista *root = NULL, *adr_c1;
		struct listaCustos *l_custos = NULL, *l_saida = NULL, aux;
		int i,j, n_vertices,n_arestas, c1, c2, custo = -1;

		scanf("%d %d", &n_vertices, &n_arestas);

		int conjuntos[n_vertices+1];
		for(i = 1; i < n_vertices+1; i++)
			conjuntos[i] = i;

		listaCustos novoCustos[n_arestas];

		for(i = 0; i < n_arestas; i++){
			scanf("%d %d %d", &c1, &c2, &custo);
			novoCustos[i].u = c1;
			novoCustos[i].v = c2;
			novoCustos[i].custo = custo;
		}

		qsort(novoCustos, n_arestas, sizeof(listaCustos), sortfunc);
		int soma_custos = 0;

		for(i = 0; i < n_arestas; i++){
			aux = novoCustos[i];

			if (conjuntos[aux.u] != conjuntos[aux.v]){

				int join = conjuntos[aux.u];
				for(j = 1; j < n_vertices+1; j++)
					if(conjuntos[j] == join)
						conjuntos[j] = conjuntos[aux.v];
				soma_custos += aux.custo;
			}
		}

		printf("%d\n", soma_custos);
		return 0;
}
