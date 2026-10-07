#include "raylib.h"
#include "barras.h"

void desenharBarras(int *valores,int quantidade,int maior, int largura, int altura, int margem,int l,int u,int i,int alvo){
	int w=(largura-2*margem)/quantidade;
	w=(w>0) ? w : 1;

	int h=(altura-2*margem);

	Color cor=SKYBLUE;

	for(int j=0;j<quantidade;j++){
		if(j==l || j==u){
			cor=ORANGE;                                                                                                                                               
		}
	else if(j==i){
		cor=BLUE;
	}
	else if(valores[j]==alvo){
		cor=GREEN;
	}
	else{
		cor=SKYBLUE;
	}

	DrawRectangle(margem+j*w,altura-margem-((float)valores[j]/maior)*h,w,((float)valores[j]/maior)*h,cor);
	}
}
