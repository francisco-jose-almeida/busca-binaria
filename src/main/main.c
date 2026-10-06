#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "../estruturas.h"

int lerValoresArquivo(FILE* fd, int** vetor,int quantidade){
	
	char linha[128];
	int valor;
	int contador=0;

	int maior=0;

	int *temp=realloc((*vetor),(quantidade)*sizeof(int));
	
	if(temp==NULL) return -1;

	while(fgets(linha,sizeof(linha),fd)!=NULL && contador<quantidade){
		valor=atoi(linha);
		
		temp[contador]=valor;
		
		if(valor>maior) maior=valor;

		contador++;
	}

	(*vetor)=temp;

	return maior;
}
int lerConfigsArquivo(FILE* fd,Configuracoes* configs, ConfigsRaylib* configs_tela){

	char linha[128];
	
	char* parametro;
	char* separador;
	char* valor;

	int contador=0;

	while(fgets(linha,sizeof(linha),fd)!=NULL){

		if(linha[0]=='\n' || linha[0]=='\r' || linha[0]=='\0') continue;

		separador=strchr(linha,'=');

		*separador='\0';

		parametro=linha;

		valor=separador+1;
		
		switch(contador){
			case 0:
				configs->teste=!strcmp(valor,"true\n");
				break;
			case 1:
				configs->quantidade_valores=atoi(valor);
				break;
			case 2:
				configs->ordenado=!strcmp(valor,"true\n");
				break;
			case 3:
				configs->crescente=!strcmp(valor,"true\n");
				break;
			case 4:
				strcpy(configs->arquivo_saida,valor);
				break;
			case 5:
				configs->visualizacao=(!strcmp(valor,"barras\n"))?BARRAS:ARVORE;
				break;
			case 6:
				configs_tela->largura=atoi(valor);
				break;
			case 7:
				configs_tela->altura=atoi(valor);
				break;
			case 8:
				configs_tela->fps=atof(valor);
				break;
			case 9:
				configs_tela->margem=atoi(valor);
				break;
			default:
				break;
		}
		contador++;
	}

	return 0;

}
int salvarEstatisticasArquivo(FILE* fd,Configuracoes configs, int comparacoes, double tempo){

	fprintf(fd,
			"Algoritmo: Busca Binaria\n"
			"Elementos: %d\n"
			"%s\n"
			"Comparacoes: %d\n"
			"Tempo: %f ms\n",
			configs.quantidade_valores,(configs.ordenado==1)?(configs.crescente==1)?"Crescente":"Decrescente":"Aleatorio",comparacoes, tempo*1000);

	return 0;
}
void calcularValoresIniciais(int* K,int N,int* l,int* u,int* i,int* k){
	*l=0;
	*u=N-1;

	*i=(*l+*u)/2;

	*k=K[rand()%N];

}

int busca_binaria(int* K, int* l,int* u, int* i, int k){
	if(*u<*l) return 1;
	
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

	*i=(*l+*u)/2;
	
	return 0;
};

int main(){
	srand(time(NULL));

	bool play=false;
	bool step=false;

	Configuracoes configuracoes_algoritmo;
	ConfigsRaylib configuracoes_tela;

	int w,h;

	Color cor=SKYBLUE;

	int comparacoes=0;
	double prev_tempo=0;
	double tempo=0;

	//Ler aquivo contendo configuracoes
	FILE* configuracoes_fd=fopen("./configuracoes.cfg","r");
	if(configuracoes_fd==NULL){
		TraceLog(LOG_INFO,"Erro ao abrir configuracoes.cfg");
	}

	lerConfigsArquivo(configuracoes_fd,&configuracoes_algoritmo,&configuracoes_tela);
	fclose(configuracoes_fd);
	
	//Ler arquivo contendo valores
	
	int* valores=(int*)malloc(configuracoes_algoritmo.quantidade_valores*sizeof(int));
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
int maior=lerValoresArquivo(valores_fd,&valores,configuracoes_algoritmo.quantidade_valores);
	fclose(valores_fd);
	
	//Inicializando variaveis para o algoritmo
	int indice_inferior;
	int indice_superior;
	int indice_medio;

	int alvo;
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
//					desenharBarras();
					
					w=(configuracoes_tela.largura-2*configuracoes_tela.margem)/configuracoes_algoritmo.quantidade_valores;
					w=(w>0) ? w : 1;

					h=(configuracoes_tela.altura-2*configuracoes_tela.margem);


					for(int i=0;i<configuracoes_algoritmo.quantidade_valores;i++){
						if(i==indice_inferior || i==indice_superior){
							cor=ORANGE;
						}
						else if(i==indice_medio){
							cor=BLUE;
						}
						else if(valores[i]==alvo){
							cor=GREEN;
						}
						else{
							cor=SKYBLUE;
						}

						DrawRectangle(configuracoes_tela.margem+i*w,configuracoes_tela.altura-configuracoes_tela.margem-((float)valores[i]/maior)*h,w,((float)valores[i]/maior)*h,cor);
					}
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
					FILE* estatistica_fd=fopen(configuracoes_algoritmo.arquivo_saida,"w");
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
}
