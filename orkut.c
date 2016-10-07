#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INF 999999

int TEMPO = 0;
int graus[30];

struct lista{
	char *vertice;
	int id;
	int eh_vizinho;
	int d;
	int f;
	int cor;
	struct lista *vizinhos;
	struct lista *end_vizinho;
	struct lista *prox;
};

struct fila {
	struct lista *p;
	struct fila *prox;
};

int insere(struct lista **p, char *nome, int eh_vizinho, struct lista *adr, int jeba){

	struct lista *aux = malloc(sizeof(struct lista)), *aux2;
	aux->vertice = malloc((strlen(nome)+1) * sizeof(char));
	aux->vizinhos = NULL;
	aux->cor = BRANCO;
	aux->d = 0;
	aux->f = 0;
	strcpy(aux->vertice, nome);
	aux->eh_vizinho = 0;
	if(jeba != -1)
		aux->id = jeba;

	if(eh_vizinho == 1){
		aux->end_vizinho = adr;
		aux->eh_vizinho = 1;
	}

	aux->prox = *p;
	*p = aux;
};

struct lista * consulta(struct lista *p, char *vertice){
	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
		if(strcmp(aux->vertice,vertice) == 0)
			return aux;
	return NULL;
};

struct lista * consultaInt(struct lista *p, int id){
	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
		if(aux->id == id)
			return aux;
	return 0;
};

int DFSvisit(struct lista *p, char *nome){

	struct lista *aux;
	TEMPO++;
	p->d = TEMPO;
	p->cor = CINZA;
	for(aux = p->vizinhos; aux != NULL; aux = aux->prox)
	{
		if(strcmp(aux->end_vizinho->vertice,nome) == 0){
			graus[p->id] = graus[p->id] - 1;
		}
		if(aux->end_vizinho->cor == BRANCO)
			DFSvisit(aux->end_vizinho,nome);
	}
	TEMPO++;
	p->cor = PRETO;
	p->f = TEMPO;
};

int DFS(struct lista *p, char *nome){

	struct lista *aux;
	TEMPO = 0;
	for(aux = p; aux != NULL; aux = aux->prox){
		aux->cor = BRANCO;
		aux->d = 0;
		aux->f = 0;
	}

	for(aux = p; aux != NULL; aux = aux->prox){
		if (aux->cor == BRANCO){
			DFSvisit(aux, nome);
		}
	}
};

void printGrafo(struct lista *p){

	struct lista *aux;
	for(aux = p; aux != NULL; aux = aux->prox)
	{
		if (aux->eh_vizinho != 1)
			printf("%s [", aux->vertice);
		else
			printf("%s ", aux->vertice);

		if (aux->vizinhos != NULL)
			printGrafo(aux->vizinhos);
		if (aux->eh_vizinho != 1)
			printf("]\n");
	}
};

void printInverso(struct lista *p){
	if(p->prox != NULL)
		printInverso(p->prox);
	printf("%s ", p->vertice);
};

void addFila(struct fila **p, struct lista *vem){
	
	struct fila *aux = malloc(sizeof(struct fila)), *aux2;
	aux->p = vem;
	aux->prox = NULL;
	
	if((*p) == NULL){
		(*p) = aux;
		return;
	}
	for(aux2 = *p; aux2->prox != NULL; aux2 = aux2->prox);
	aux2->prox = aux;
};

struct lista * rmFila(struct fila **p){
	
	if(*p == NULL)
		return NULL;
	else{
		struct lista *aux;
		aux = (*p)->p;
		*p = (*p)->prox;

		return aux;
	}
};

int main(){

	int teste = 1;

	while(1){

		struct lista *root = NULL, *adr1, *adr2, *aux;
		struct fila *fila = NULL, *saida = NULL;
		char nome[16], nome2[16];
		int i, j, n = 0, n_vertices = 0;

		scanf("%d", &n_vertices);

		for(i = 0; i < n_vertices; i++)
			graus[i] = 0;

		if(n_vertices == 0)
			break;

		for(i = 0; i < n_vertices; i++){
			scanf("%s", nome);
			insere(&root,nome,0,NULL, i);
		}
		for(i = 0; i < n_vertices; i++){

			scanf("%s",nome);
			scanf("%d", &n);
			adr1 = consulta(root,nome);
			for(j = 0; j < n; j++){
				scanf("%s", nome2);
				adr2 = consulta(root,nome2);
				insere(&(adr1->vizinhos),nome2,1,adr2,-1);

			}
			graus[adr1->id] = n;
		}

		int cont_out = 0;
		int nao;

		while(1){	

			nao = 1;
			for(i = 0; i < n_vertices; i++)
				if(graus[i] == 0){
					adr1 = consultaInt(root,i);
					addFila(&fila,adr1);
					graus[i] = graus[i] - 1;
					nao = 0;
				}

			if(!(aux = rmFila(&fila)) && nao == 1)
				break;

			addFila(&saida,aux);
			cont_out++;
			DFS(root, aux->vertice);
		}

		printf("Teste %d\n", teste);
		if(cont_out == n_vertices){
			while(aux = rmFila(&saida))
				printf("%s ", aux->vertice);
			printf("\n\n");
		}
		else
			printf("impossivel\n\n");
		
		teste++;
		TEMPO = 0;
	}
}