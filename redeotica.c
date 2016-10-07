#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INF 999999

typedef struct listaCustos{
	int v;
	int u;
	int custo;
	struct listaCustos *prox;
}listaCustos;

int sortfunc(const void *a, const void *b){
	listaCustos * orderA = (listaCustos *) a;
	listaCustos * orderB = (listaCustos *) b;
	return ( orderA->custo - orderB->custo );
};

int main(){

	int n_teste = 1;

	while(1){

		int i,j, n_vertices,n_arestas, c1, c2, custo = -1, n_saida = 0;

		scanf("%d %d", &n_vertices, &n_arestas);
		if(n_vertices == 0 && n_arestas == 0)
			break;

		int conjuntos[n_vertices+1];
		for(i = 1; i < n_vertices+1; i++)
			conjuntos[i] = i;

		listaCustos novoCustos[n_arestas], l_saida[n_arestas], aux;

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
				l_saida[n_saida] = aux;
				n_saida++;
			}
		}

		printf("Teste %d\n", n_teste);
		for (i = 0; i < n_saida; i++) {
			if(l_saida[i].u > l_saida[i].v)
				printf("%d %d\n", l_saida[i].v, l_saida[i].u);
			else
				printf("%d %d\n", l_saida[i].u, l_saida[i].v);
		}
		printf("\n");
		n_teste++;
	}
	
	return 0;
}
