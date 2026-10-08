#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "arquivos.h"
#include "../estruturas.h"
#include "../visualizacoes/barras/barras.h"

void calcularValoresIniciais(int* K,int N,int* l,int* u,int* i,int* k){ //8+4+8+8+8+8=44
	*l=0;	//	//c1
	*u=N-1;	//	//c2

	*i=(*l+*u)/2;	//	//c3

	*k=K[rand()%N];	//	//c4

}//O(1)	//O(1)

int busca_binaria(int* K, int* l,int* u, int* i, int k){i//8+8+8+8+4=36
	if(*u<*l) return 1;// //c1
	
	//Verificar crescente/decrescente
	if(K[*l]<=K[*u]){	//crescente	//	//c2
		if(K[*i]<k){	//	//c3
			*l=*i;	//	//c4
		}
		else if(K[*i]>k){	//	//c5
			*u=*i;	//	//c6
		}
	}
	else{	//descrescente	//	//c7
		if(K[*i]<k){//	//c8
			*u=*i;	//c9
		}
		else if(K[*i]>k){//	//c10
			*l=*i;//	//c11
		}
	}

	*i=(*l+*u)/2;//	//c12
	
	return 0;
};// O(0) // O(0)

int main(){
	srand(time(NULL));

	bool play=false;	//1
	bool step=false;	//1

	Configuracoes configuracoes_algoritmo; //1+4+1+1+64+4=72
	ConfigsRaylib configuracoes_tela; //4+4+4+4=16

	int w,h;//4+4=8

	int comparacoes=0;//4
	double prev_tempo=0;//4
	double tempo=0;//4

	//Ler aquivo contendo configuracoes
	FILE* configuracoes_fd=fopen("./configuracoes.cfg","r");//8
	if(configuracoes_fd==NULL){
		TraceLog(LOG_INFO,"Erro ao abrir configuracoes.cfg");
	}

	lerConfigsArquivo(configuracoes_fd,&configuracoes_algoritmo,&configuracoes_tela);
	fclose(configuracoes_fd);
	
	//Ler arquivo contendo valores
	
	int* valores=(int*)malloc(configuracoes_algoritmo.quantidade_valores*sizeof(int));//quantidade_valore*4
	char arquivo_valores[64];//1*64=64

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
int maior=lerValoresArquivo(valores_fd,&valores,configuracoes_algoritmo.quantidade_valores);//4
	fclose(valores_fd);
	
	//Inicializando variaveis para o algoritmo
	int indice_inferior;//4
	int indice_superior;//4
	int indice_medio;//4

	int alvo;//4
	calcularValoresIniciais(valores,configuracoes_algoritmo.quantidade_valores,&indice_inferior,&indice_superior,&indice_medio,&alvo);

	TraceLog(LOG_INFO,"Alvo: %d",alvo);

	SetTargetFPS(configuracoes_tela.fps);

	//Iniciar Raylib
	InitWindow(configuracoes_tela.largura,configuracoes_tela.altura,"Algoritmo de Busca por Arvore Binaria");
	while(!WindowShouldClose()){
		BeginDrawing();

			ClearBackground(RAYWHITE);

			//Desenhar tela
			switch(configuracoes_algoritmo.visualizacao){
				case 0://BARRAS
					desenharBarras(valores,configuracoes_algoritmo,configuracoes_tela,maior,indice_inferior,indice_superior,indice_medio, alvo);
				break;
				case 1://ARVORE
//					desenharArvore();
					break;
				default:
					WaitTime(1);
					break;
			}
			
			//Rodar algoritmo
			int key=GetKeyPressed();
			if(IsKeyPressed(KEY_SPACE) || key==KEY_SPACE){
				play=!play;

			}
			if(IsKeyPressed(KEY_R) || key==KEY_R){
				calcularValoresIniciais(valores,configuracoes_algoritmo.quantidade_valores,&indice_inferior,&indice_superior,&indice_medio,&alvo);
				DrawText("\n\n\n\n\n\n\n\nReiniciando...",configuracoes_tela.margem,configuracoes_tela.margem,FONT_SIZE,FONT_COLOR);				
				comparacoes=0;
				tempo=0;
			}
			if(IsKeyPressed(KEY_S) || key==KEY_S){
				step=true;
			}
			if((play || step) && valores[indice_medio]!=alvo){
				prev_tempo=GetTime();
				busca_binaria(valores,&indice_inferior,&indice_superior,&indice_medio,alvo);
				tempo+=GetTime()-prev_tempo;
				comparacoes++;
				step=false;
			}
			else{
				DrawText("\n\n\n\n\n\n\n\nPausado!",configuracoes_tela.margem,configuracoes_tela.margem,FONT_SIZE,FONT_COLOR);				
			}
			if(valores[indice_medio]==alvo){
				WaitTime(1);
				play=false;

				if(configuracoes_algoritmo.teste){
					FILE* estatistica_fd=fopen(configuracoes_algoritmo.arquivo_saida,"w");//8
					if(estatistica_fd==NULL) return 1;

					salvarEstatisticasArquivo(estatistica_fd,configuracoes_algoritmo,comparacoes,tempo);

					fclose(estatistica_fd);
				}
			}
			DrawText(TextFormat("Algoritmo: Busca Binaria\nElementos: %d\nComparacoes: %d\nTempo: %.4f ms\n\nEspaco para continuar/pausar\nR para reiniciar\nS para avancar um passo", configuracoes_algoritmo.quantidade_valores,comparacoes,tempo*1000),configuracoes_tela.margem,configuracoes_tela.margem,FONT_SIZE,FONT_COLOR);
		EndDrawing();
	}


		//Fechar Raylib
		CloseWindow();

		free(valores);

		return 0;
}//O(n) //O(nlog(n))
