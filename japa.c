#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int valor;
	int i;
	int j;
} Elemento;

typedef struct {
	int i;
	int j;
	int **m;
	int amount;
} Matriz;

void add(Elemento ** temp, int valor, int i, int j, int count){
	(*temp)[count].valor = valor;
	(*temp)[count].i = i;
	(*temp)[count].j = j;
	//printf("count = %d\nElemento:\nValor=%d\ni=%d\nj=%d\n", count, (*temp)[count].valor, (*temp)[count].i, (*temp)[count].j);
}

int find(FILE * arquivo){
	int count = 0;
	int i, j, tami, tamj;
	int aux;
	fscanf(arquivo, "%d %d\n", &tami, &tamj);
	for(i=0; i<tami; i++){
		for(j=0; j<tamj; j++){
			fscanf(arquivo, "%d ", &aux);
			if(aux){
				count++;
			}
		}
	}
	return count;
}

Elemento * carregar(FILE * arquivo, Matriz ** tamanho){
	int i, j;
	int aux;
	int count=0;
	Elemento * temp = NULL;
	(*tamanho)->amount = find(arquivo);
	//printf("amount = %d\n",(*tamanho)->amount);
	temp = malloc(sizeof(Elemento) * (*tamanho)->amount);
	rewind(arquivo);
	fscanf(arquivo, "%d %d\n", &((*tamanho)->i), &((*tamanho)->j));
	//printf("tami %d tamj %d\n", (*tamanho)->i, (*tamanho)->j);

	for(i=0; i<(*tamanho)->i; i++){
		for(j=0; j<(*tamanho)->j; j++){
			fscanf(arquivo, "%d ", &aux);
			if(aux){
				add(&temp, aux, i, j, count);
				count++;
			}
		}
	}
	return temp;
}

void printaMatriz(Matriz * matriz, Elemento * elementos){

	int i;
	int j;
	matriz->m = malloc(sizeof(int*)*matriz->i);
	for(i=0; i<matriz->i; i++){
		matriz->m[i] = malloc(sizeof(int)*matriz->j);
	}

	for(i=0; i<matriz->i; i++){
		for(j=0; j<matriz->j; j++){
			matriz->m[i][j] = 0;
		}
	}

	for(i=0; i<matriz->amount; i++){
		int x = elementos[i].i;
		int y = elementos[i].j;
		int v = elementos[i].valor;
		matriz->m[x][y] = v;
	}
	for(i=0; i<matriz->i; i++){
		for(j=0; j<matriz->j; j++){
			printf("%3d ", matriz->m[i][j]);
		}
		printf("\n");
	}

	for(i=0; i<matriz->i; i++){
		free(matriz->m[i]);
	}
	free(matriz->m);

}

int main(int argc, char const *argv[])
{
	FILE * arquivo = NULL;
	Matriz * _m = malloc(sizeof(Matriz));
	Elemento * posicoes = NULL;
	if(argc < 2){
		printf("inicie os arquvos\n");
		exit(1);
	}

	arquivo = fopen(argv[1], "r");
	posicoes = carregar(arquivo, &_m);

	printaMatriz(_m, posicoes);

	return 0;
}