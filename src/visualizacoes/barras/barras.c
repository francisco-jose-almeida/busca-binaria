#include "raylib.h"
#include "barras.h"
#include "../../estruturas.h"

void desenharBarras(int *valores,Configuracoes configs_algoritmo,ConfigsRaylib configs_tela,int maior,int l,int u,int i,int alvo){
	float w=(float)(configs_tela.largura-2*configs_tela.margem)/configs_algoritmo.quantidade_valores;
	
	int h=(configs_tela.altura-2*configs_tela.margem);

	
	int altura=0;

	int elementos_barra=1;

	int x=configs_tela.margem;
	int y;

	Color cor=SKYBLUE;

	for(int j=0;j<configs_algoritmo.quantidade_valores;j++){
		if(j==l || j==u){
			cor=ORANGE;                                                                       
		}
		if(j==i){
			cor=BLUE;
		}
		if(valores[j]==alvo){
			cor=GREEN;
		}
		altura+=((float)valores[j]/maior)*h;

		if(w>=1){
			altura/=elementos_barra;
			
			x+=w;
			y=configs_tela.altura-configs_tela.margem-altura;
		
			DrawRectangle(x,y,w,altura,cor);

			altura=0;
			w=(float)(configs_tela.largura-2*configs_tela.margem)/configs_algoritmo.quantidade_valores;
			elementos_barra=1;

			cor=SKYBLUE;
		}
		else{
			w+=(float)(configs_tela.largura-2*configs_tela.margem)/configs_algoritmo.quantidade_valores;
			elementos_barra++;
		}
	}
}
