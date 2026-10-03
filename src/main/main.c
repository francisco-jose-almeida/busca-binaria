#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	BARRAS,
	ARVORE
}Visualizacao;

typedef enum{
	CONFIGURANDO,
	RODANDO
}Estado;

typedef struct{
	bool teste;
	int quantidade_valores;
	bool ordenado;
	bool crescente;
	char arquivo_saida[64];
	Visualizacao visualizacao;
}Configuracoes;

typedef struct{
	int largura;
	int altura;
	float fps;
	int margem;
}ConfigsRaylib;

int receberConfiguracoes(Configuracoes* configs_algoritmo,ConfigsRaylib* configs_tela){	

	int key=GetKeyPressed();

	if(key!=0){
	}

	return 0;
}

int lerValoresArquivo(FILE* fd, int** vetor,int quantidade){
	
	char linha[128];
	int valor;
	int contador=0;

	int *temp=realloc((*vetor),(quantidade)*sizeof(int));
	
	if(temp==NULL) return 1;

	while(fgets(linha,sizeof(linha),fd)!=NULL){
		valor=atoi(linha);
		
		temp[contador]=valor;
		
		contador++;
	}

	(*vetor)=temp;

	return 0;
}



int busca_binaria(int* K, int* l,int* u, int* i, int k){
	if(*u<*l) return 1;
	
	*i=(*l+*u)/2;

	//Verificar crescente/decrescente
	if(K[*l]<=K[*u]){	//crescente
		if(K[*i]<k){
			*l=*i;
		}
		else if(K[*i]>k){
			*u=*i;
		}
	}
	else{	//descrescente
		if(K[*i]<k){
			*u=*i;
		}
		else if(K[*i]>k){
			*l=*i;
		}
	}
	return 0;
};

int main(){
	srand(time(NULL));

	Estado estado=CONFIGURANDO;

	//Inicializando Configuracoes Tela
	ConfigsRaylib configuracoes_tela;
	configuracoes_tela.largura=800;
	configuracoes_tela.altura=600;
	configuracoes_tela.fps=60;
	configuracoes_tela.margem=30;

	//Inicializando Configuracoes Algoritmo
	Configuracoes configuracoes_algoritmo;
	configuracoes_algoritmo.teste=true;
	configuracoes_algoritmo.quantidade_valores=100;
	configuracoes_algoritmo.ordenado=true;
	configuracoes_algoritmo.crescente=true;
	strcpy(configuracoes_algoritmo.arquivo_saida,"./estatisticas_cres_100.txt");
	configuracoes_algoritmo.visualizacao=BARRAS;


	SetTargetFPS(configuracoes_tela.fps);

	//Inicializando variaveis para o algoritmo
	int* valores=(int*)malloc(configuracoes_algoritmo.quantidade_valores*sizeof(int));
	int indice_inferior=0;
	int indice_superior=configuracoes_algoritmo.quantidade_valores-1;
	int indice_medio;
	int alvo=valores[rand()%configuracoes_algoritmo.quantidade_valores];

	int mensagem_tela[3]={configuracoes_tela.largura/3,configuracoes_tela.altura/2,40};


	//Ler arquivo contendo valores
	
	char arquivo_valores[64];

	if(configuracoes_algoritmo.ordenado){
		if(configuracoes_algoritmo.crescente){
			strcpy(arquivo_valores,"./arquivos-valores/valores_crescente.bin");
		}
		else{
			strcpy(arquivo_valores,"./arquivos-valores/valores_decrescente.bin");
		}
	}
	else{
		strcpy(arquivo_valores,"./arquivos-valores/valores_aleatorio.bin");
	}
	FILE* valores_fd=fopen(arquivo_valores,"rb");
	lerValoresArquivo(valores_fd,&valores,configuracoes_algoritmo.quantidade_valores);

	//Iniciar Raylib
	InitWindow(configuracoes_tela.largura,configuracoes_tela.altura,"Algoritmo de Busca por Arvore Binaria");
	while(!WindowShouldClose()){
		BeginDrawing();
	
		switch(estado){
			case 0:	//CONFIGURANDO_ALGORITMO
				//Receber configuracoes do usuario
				receberConfiguracoes(&configuracoes_algoritmo,&configuracoes_tela);
				break;
			case 1:	//RODANDO
				//Desenhar tela
				switch(configuracoes_algoritmo.visualizacao){
					case 0://BARRAS
//						desenharBarras();
						break;
					case 1:
//						desenharArvore();
						break;
					default:
						DrawText("Visualizacao Escolhida Nao Existe!",mensagem_tela[0],mensagem_tela[1],mensagem_tela[2],RED);
						WaitTime(1);
						receberConfiguracoes(&configuracoes_algoritmo,&configuracoes_tela);
				}
				
				//Rodar algoritmo
				
				busca_binaria(valores,&indice_inferior,&indice_superior,&indice_medio,alvo);
		
				if(valores[indice_medio]==alvo){
					DrawText(TextFormat("Alvo %d Encontrado no indice: %d",alvo,indice_medio),mensagem_tela[0],mensagem_tela[1],mensagem_tela[2],GREEN);
					WaitTime(1);
				}
				break;
		}

		EndDrawing();
	}

		//Fechar Raylib
		CloseWindow();
	
		return 0;
}
