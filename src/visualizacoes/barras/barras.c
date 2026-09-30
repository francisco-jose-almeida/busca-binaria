#include "barras.h"
#include "raylib.h"

/*Funcao para desenhar um passo da busca binaria como um grafico de barras*/
void desenharBarras(int *vetor, int quantidade, int indice_menor, int indice_maior, int indice_medio, int alvo, int passo){
	
	int x,y,w,h;

	y=GetScreenHeight()-GetScreenHeight()*.1;

	w=((GetScreenWidth()-2*GetScreenWidth()/10)/quantidade);

	Color color=SKYBLUE;

	BeginDrawing();

	ClearBackground(RAYWHITE);

	for(int i=0;i<quantidade;i++){

		x=(GetScreenWidth()/10)+i*w;

		h=vetor[i]/1000;

		if(i==indice_menor || i == indice_maior){
			color=ORANGE;
		}
		else if(i==indice_medio){
			color=BLUE;
		}
		else if(vetor[i]==alvo){
			color=GREEN;
		}
		else{
			color=SKYBLUE;
		}

		DrawRectangle(x,y,w,h,color);
	}
	
	EndDrawing();
}
