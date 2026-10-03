#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdbool.h>

//DEFININDO CONSTANTES
#define FONT_SIZE	20
#define FONT_COLOR	GRAY

//DEFININDO ESTRUTURAS

typedef enum{
	CONFIGURANDO,
	RODANDO
}Estado;

typedef enum{
	BARRAS,
	ARVORE
}Visualizacao;

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

#endif
