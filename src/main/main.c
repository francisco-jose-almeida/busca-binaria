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
				configs->teste=strcmp(valor,"true")?true:false;
				break;
			case 1:
				configs->quantidade_valores=atoi(valor);
				break;
			case 2:
				configs->ordenado=strcmp(valor,"true")?true:false;
				break;
			case 3:
				configs->crescente=strcmp(valor,"true")?true:false;
				break;
			case 4:
				strcpy(configs->arquivo_saida,valor);
				break;
			case 5:
				configs->visualizacao=(strcmp(valor,"barras"))?BARRAS:ARVORE;
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

	Estado estado=CONFIGURANDO;

	Configuracoes configuracoes_algoritmo;
	ConfigsRaylib configuracoes_tela;

	char resposta[256];
	strcpy(resposta,"");

	int resposta_ptr=0;

	int opcao=1;

	int w,h;

	Color cor=SKYBLUE;

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
	int indice_inferior=0;
	int indice_superior=configuracoes_algoritmo.quantidade_valores-1;
	int indice_medio = (indice_inferior+indice_superior)/2;
	int alvo=valores[rand()%configuracoes_algoritmo.quantidade_valores];

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
					
					w=(float)(configuracoes_tela.largura-2*configuracoes_tela.margem)/configuracoes_algoritmo.quantidade_valores;
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
			
			busca_binaria(valores,&indice_inferior,&indice_superior,&indice_medio,alvo);
	
					if(valores[indice_medio]==alvo){
				WaitTime(1);
			}
		EndDrawing();
	}


		//Fechar Raylib
		CloseWindow();

		free(valores);

		return 0;
}
