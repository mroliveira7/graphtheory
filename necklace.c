#include <stdio.h>
#include <stdlib.h>

int BEANS[51];

void printaCircuito(int **ma, int v){

	int i;
	for (i = 1; i < 51; i++){
		if(ma[v][i] > 0){

			printf("%d %d\n", v,i);
			ma[v][i]--;
			ma[i][v]--;
			printaCircuito(ma,i);
		}
	}
};

int main (){
	
	int qtd_testes, n_teste = 1;
	scanf("%d", &qtd_testes);

	while(n_teste <= qtd_testes){

		int **MA = (int **)malloc(51 * sizeof(int*)), n_beans, b1, b2, i,j, eh_euleriano = 1;
		scanf("%d", &n_beans);

		for(i = 1; i < 51; i++) MA[i] = (int *)malloc(51 * sizeof(int));
		
		for(i = 1; i < 51; i++)
			for(j = 1; j < 51; j++){
				MA[i][j] = 0;
				BEANS[j] = 0;
			}
		for(i = 0; i < n_beans; i++)
		{
			scanf("%d %d", &b1, &b2);
			MA[b1][b2]++;
			MA[b2][b1]++;
			BEANS[b1]++;
			BEANS[b2]++;
		}

		for(i = 1; i < 51; i++)
			if((BEANS[i] % 2) != 0)
				eh_euleriano = 0;

		if (eh_euleriano == 1)
		{
			printf("Case #%d\n", n_teste);
			for (i = 1; i < 51; i++){
				if(MA[1][i] > 0){
					printaCircuito(MA,i);
				}
			}
		}
		else{
			printf("Case #%d\n", n_teste);
			printf("some beads may be lost\n");
		}
		printf("\n");
		
		n_teste++;
		eh_euleriano = 1;
	}

	return 0;
}