#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){
	srand(time(NULL));

	if(argc<2) {
		printf("Parametros insuficientes\n");
		return 1;
	}

	char* arquivo=argv[1];
	int quantidade= (argv[2]==NULL ? 10 : atoi(argv[2]));
	int maximo= (argv[3]==NULL ? 100 : atoi(argv[3]));

	FILE* arquivo_fd=fopen(arquivo,"w");

	if(arquivo_fd == NULL) {
		printf("Erro ao abrir arquivo\n");
		return 1;
	}

	int valor=rand()%(maximo/quantidade);
	int soma;

	fprintf(arquivo_fd,"%d\n",valor);

	for(int i=0;i<quantidade;i++){
		soma=rand()%(maximo/quantidade);
		valor+=soma;

		fprintf(arquivo_fd,"%d\n",valor);
	}

	fclose(arquivo_fd);

	return 0;
}
