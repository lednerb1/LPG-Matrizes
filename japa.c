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

Elemento * definirElementos(FILE * arquivo, Matriz ** tamanho){
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

void criaMatriz(Matriz * matriz, Elemento * elementos){

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

int menu(){
	int aux;
	system("clear");
	printf("O que deseja?\n\n");
	printf("\t1: Carregar uma matriz\n");
	printf("\t2: Visualizar uma matriz\n");
	printf("\t3: Modificar uma matriz\n");
	printf("\t4: Salvar uma matriz\n");
	printf("\t5: Somar matrizes\n");
	printf("\t6: Subtrair matrizes\n");
	printf("\t7: Multiplicar matrizes\n");
	printf("\t0: Sair\n\n");
	printf("In: ");
	scanf("%d", &aux);
	system("clear");
	return aux;
}

void carregar(FILE *arquivo[2], char nome[2][50]){

	char aux;
	printf("Digite o nome do arquivo para ser carregado\nIn: ");
	if(!nome[0][0]){
		scanf("%s", nome[0]);
		printf("Deseja carregar o segundo arquivo?\nS/N: ");
		getchar();
		scanf("%c", &aux);
		if(aux == 'S' || aux == 's'){
			printf("Digite o nome do segundo arquivo\nIn: ");
			scanf("%s", nome[1]);
		}else{
			return;
		}
	return;
	}if(!nome[1][0]){
		scanf("%s", nome[1]);
	}else{
		printf("\n\nErro: Todos arquivos lidos, ENTER para continuar\n");
		getchar();
		getchar();
	}
}

int main(int argc, char const *argv[])
{

	// if(argc < 3){
	// 	printf("inicie os arquvos\n");
	// 	exit(1);
	// }
	char nome[2][50] = {"\0", "\0"};
	FILE * arquivo[2] = {NULL, NULL};
	Matriz * _m = malloc(sizeof(Matriz));
	Elemento * posicoes = NULL;

	int op;
	do{
		op = menu();
		
		switch(op){
			case 0:
			break;
			case 1:
			carregar(arquivo, nome);
			printf("%s\n%s\n", nome[0], nome[1]);

		}

	}while(op);

	//arquivo = fopen(argv[1], "r");
	//posicoes = definirElementos(arquivo, &_m);

	//criaMatriz(_m, posicoes);

	return 0;
}