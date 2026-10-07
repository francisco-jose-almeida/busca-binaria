#include "raylib.h"
#include "barras.h"
#include "../../estruturas.h"

void desenharBarras(int *valores,Configuracoes configs_algoritmo,ConfigsRaylib configs_tela,int maior,int l,int u,int i,int alvo){
	int w=(configs_tela.largura-2*configs_tela.margem)/configs_algoritmo.quantidade_valores;
	w=(w>0) ? w : 1;

	int h=(configs_tela.altura-2*configs_tela.margem);

	Color cor=SKYBLUE;

	for(int j=0;j<configs_algoritmo.quantidade_valores;j++){
		if(j==l || j==u){
			cor=ORANGE;                                                                       }
		else if(j==i){
			cor=BLUE;
		}
		else if(valores[j]==alvo){
			cor=GREEN;
		}
		else{
			cor=SKYBLUE;
		}

		int altura=((float)valores[j]/maior)*h;

		int x=configs_tela.margem+j*w;
		int y=configs_tela.altura-configs_tela.margem-altura;
		
		DrawRectangle(x,y,w,altura,cor);
	}
}
