#include <stdio.h>
#include "../estruturas.h"

int lerValoresArquivo(FILE* fd, int** vetor, int quantidade);

int lerConfigsArquivo(FILE* fd,Configuracoes* configs, ConfigsRaylib* configs_tela);

int salvarEstatisticasArquivo(FILE* fd, Configuracoes configs,int comparacoes, double tempo);
