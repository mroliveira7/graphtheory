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
	int distancia;
	struct lista *esq;
	struct lista *dir;
	struct lista *vizinhos;
	struct lista *end_vizinho;
	struct lista *prox;
};

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

int insereTree(struct lista **p, int num, int eh_vizinho, struct lista *adr){

	struct lista *aux = (struct lista*) malloc(sizeof(struct lista));
	aux->vertice = num;
	aux->esq = NULL;
	aux->dir = NULL;
	aux->vizinhos = NULL;
	aux->eh_vizinho = 0;

	if(eh_vizinho == 1){
		aux->end_vizinho = adr;
		aux->eh_vizinho = 1;
		aux->vizinhos = NULL;
	}	

	if((*p) == NULL)
	{
		(*p) = aux;
	}
	else{
		if(num < (*p)->vertice)
			insere(&(*p)->dir, num,eh_vizinho,adr);
		else
			insere(&(*p)->esq, num,eh_vizinho,adr);
	}
};

struct lista * consulta(struct lista *p, int vertice){
	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
		if(aux->vertice == vertice)
			return aux;
	return 0;
};

struct lista * consultaTree(struct lista *p, int vertice){
	
	if(p == NULL)
		return 0;

	if(p->vertice == vertice)
		return p;

	if (vertice < p->vertice){
		return consultaTree(p->dir, vertice);
	}
	else{
		return consultaTree(p->esq, vertice);
	}

};


void addFila(struct lista **p, int num){
	
	struct lista *aux = malloc(sizeof(struct lista)), *aux2;
	aux->vertice = num;
	aux->prox = NULL;
	
	if((*p) == NULL){
		(*p) = aux;
		return;
	}
	for(aux2 = (*p); (aux2 != NULL) && (aux2->prox != NULL) && (aux2->prox->vertice < num); aux2 = aux2->prox);

	if(aux2 == (*p))
	{
		if((*p)->vertice < num){	
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

int rmFila(struct lista **p){
	
	int r;
	if(*p == NULL)
		return -1;
	struct lista *aux = (*p);
	r = (*p)->vertice;
	(*p) = aux->prox;
	return r;
};

int main(){

		struct lista *root = NULL, *adr_c1, *fila = NULL;
		int i, n_vertices,n_arestas, c1, c2, proximo, point_saida = 0;

		scanf("%d %d",&n_vertices, &n_arestas);

		int saida[n_vertices], horadoshow[n_vertices], porra = 0;
		int *GRAUS = calloc(n_vertices,sizeof(int));

		for(i = 0; i < n_vertices; i++)
			insereTree(&root,i,0,NULL);

		for(i = 0; i < n_arestas; i++){
			scanf("%d %d",&c1,&c2);
			adr_c1 = consultaTree(root,c1);
			insere(&(adr_c1->vizinhos),c2,1,NULL);
			GRAUS[c2] = GRAUS[c2]+1;
		}

		for(i = 0; i < n_vertices; i++){
			if(GRAUS[i] == 0){
				addFila(&fila,i);
			}
		}

		int aux;
		while(1){			
			aux = rmFila(&fila);
			porra = 0;
			if(aux == -1)
				break;

			if(GRAUS[aux] == 0){
				saida[point_saida] = aux;
				point_saida++;
			}
			GRAUS[aux] = GRAUS[aux] - 1;
			adr_c1 = consultaTree(root,aux);
			printf("%d\n",adr_c1->vertice);
			if(adr_c1->vizinhos == NULL) continue;

			for(adr_c1 = adr_c1->vizinhos; adr_c1 != NULL; adr_c1 = adr_c1->prox){
				GRAUS[adr_c1->vertice] = GRAUS[adr_c1->vertice] - 1;
				if(GRAUS[adr_c1->vertice] == 0)
				{
				horadoshow[porra] = adr_c1->vertice;
					porra++;
				}
			}
			
			for(i = 0; i < porra; i++){
					addFila(&fila,horadoshow[i]);
			}
		}

		if(point_saida == n_vertices)
		{
			for(i = 0; i < point_saida; i++)
				printf("%d\n", saida[i]);
			printf("\n");
		}
		else
			printf("*\n");
		return 0;
}