#include <stdio.h>
#include <stdlib.h>

int VGLOBAL[100];

void DFSvisit(int **ma, int num_vertice, int v, int *visitados){
	int i;
	for (i = 0; i < num_vertice; i++)
		if(ma[v][i] == 1 && VGLOBAL[i] == 0)
		{
			printf("%d\n", v);
			VGLOBAL[i] == 1;
			DFSvisit(ma,num_vertice,i,visitados);
		}
};

int DFS(int **ma, int num_vertice){
	
	int i, visitados[num_vertice],j;
	for (i = 0; i < num_vertice; i++)
		visitados[i] = 0;

	VGLOBAL[0] = 1;

	for (i = 0; i < num_vertice; i++)
	{
		if (ma[0][i] == 1 && VGLOBAL[i] == 0)
		{
			VGLOBAL[i] = 1;
			DFSvisit(ma,num_vertice,i,visitados);
		}
	}
	for(i = 0; i < num_vertice; i++)
		if(VGLOBAL[i] == 0)
			return 0;
	return 1;
};


int main(){

	int nteste = 1;
	int nVertices, nArestas, i, j,v1, v2;

	do{
		scanf("%d %d", &nVertices, &nArestas);
		if (nVertices == 0 && nArestas == 0)
			break;

		int **MA = (int **)malloc(nVertices * sizeof(int*));
		for(i = 0; i < nVertices; i++) MA[i] = (int *)malloc(nVertices * sizeof(int));
		for(i = 0; i < nVertices; i++)
			for(j = 0; j < nVertices; j++)
				MA[i][j] = 0;
		for(i = 0; i < nArestas; i++)
			VGLOBAL[i] = 0;

		for (i = 0; i < nArestas; i++)
		{
			scanf("%d %d", &v1, &v2);
			MA[v1-1][v2-1] = 1;
			MA[v2-1][v1-1] = 1;
		}
		if (DFS(MA,nVertices)){
			printf("Teste %d\n", nteste);
			printf("normal\n");
		}
		else
		{
			printf("Teste %d\n", nteste);
			printf("falha\n");
		}
		printf("\n");
		nteste++;
	}
	while(1);
	return 0;
}
