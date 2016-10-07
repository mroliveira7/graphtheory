#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct listaCustos{
	int v;
	int u;
	double custo;
	struct listaCustos *prox;
}listaCustos;

int sortfunc(const void *a, const void *b){
	listaCustos * orderA = (listaCustos *) a;
	listaCustos * orderB = (listaCustos *) b;
	return ( orderA->custo - orderB->custo );
};

double calc_d(double a1, double a2, double b1, double b2){

	return( sqrt( pow(a2 - a1,2) + pow(b2 - b1, 2)) );
}

int main(){

	while(1){
		int i,j, n_vertices,n_arestas, custo = -1, n_saida = 0;
		double c1, c2;

		scanf("%d", &n_vertices);
		if(n_vertices == 0)
			break;

		double coord[2][n_vertices+1];
		double distancias[n_vertices+1][n_vertices+1];
		for (i = 0; i < n_vertices+1; i++)
			for (j = 0; j < n_vertices+1; j++)
				distancias[i][j] = -1;

		for (i = 1; i < n_vertices+1; i++) {
			scanf("%lf %lf", &c1, &c2);
			coord[0][i] = c1;
			coord[1][i] = c2;
		}
		listaCustos novoCustos[(n_vertices+1) * (n_vertices+1)], aux;
		int n_custos = 0;

		for(i = 1; i < n_vertices+1; i++){
			for (j = 1; j < n_vertices+1; j++) {

				if( i == j)	continue;

				distancias[i][j] = calc_d(coord[0][i], coord[0][j], coord[1][i], coord[1][j]);
				distancias[j][i];
				novoCustos[n_custos].u = i;
				novoCustos[n_custos].v = j;
				novoCustos[n_custos].custo = distancias[i][j];
				n_custos++;
			}
		}

		qsort(novoCustos, n_custos, sizeof(listaCustos), sortfunc);

		// printf("REAL TEST\n");
		// for(i = 0; i < n_custos; i++)
		// printf("ID : %d -- u: %d v: %d d: %.4lf\n" ,i, novoCustos[i].u, novoCustos[i].v, novoCustos[i].custo);
		// printf("\n");

		double maior;
		int conjuntos[n_vertices+1];
		for(i = 1; i < n_vertices+1; i++)
			conjuntos[i] = i;

		for(i = 0; i < n_custos; i++){
			aux = novoCustos[i];

			if(conjuntos[aux.u] != conjuntos[aux.v]){
				int join = conjuntos[aux.u];
				for(j = 1; j < n_vertices+1; j++)
					if(conjuntos[j] == join)
						conjuntos[j] = conjuntos[aux.v];
				maior = aux.custo;
			}
		}
		printf("%.4lf\n", maior);
	}

	return 0;
}
