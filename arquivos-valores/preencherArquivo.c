#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	srand(time(NULL));

     if(argc<2) {
         printf("Parametros insuficientes\n");
         return 1;
     }

     char* arquivo=argv[1];
     int tipo= (argc<3) ? 'c' : argv[2][0]; //c, d, a - crescente, decrescente, aleatorio
     int quantidade= (argc<4 ? 10 : atoi(argv[3]));

     FILE* arquivo_fd=fopen(arquivo,"w");

     if(arquivo_fd == NULL) {
         printf("Erro ao abrir arquivo\n");
         return 1;
     }

	 if(tipo=='c'){
     	int valor=rand()%(10000/quantidade);
     	int soma;

    	 fprintf(arquivo_fd,"%d\n",valor);

     	for(int i=0;i<quantidade;i++){
         	soma=rand()%(10000/quantidade);
        	 valor+=soma;

       	  fprintf(arquivo_fd,"%d\n",valor);
     	}
	 }
	 else if(tipo=='d'){
			int valor=10000-rand()%(10000/quantidade);
     	int soma;

    	 fprintf(arquivo_fd,"%d\n",valor);

     	for(int i=0;i<quantidade;i++){
         	soma=rand()%(10000/quantidade);
        	 valor-=soma;

       	  fprintf(arquivo_fd,"%d\n",valor);
     	}

	 }
	 else if(tipo=='a'){
		int valor;
		for(int i=0;i<quantidade;i++){
        	valor=rand()%10000;

       		fprintf(arquivo_fd,"%d\n",valor);
     	}

	 }

     fclose(arquivo_fd);

	return 0;
}
