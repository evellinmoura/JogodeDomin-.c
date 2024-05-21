#include <time.h>
#include "jogo-domino.h"

void jogarDominos() {
    printf("---------------\n");
    mesa.Num_Pecas_Mesa = 0;
    inicializarPecas();
    embaralharPecas();
    distribuirPecas();
    
    quemComeca();
    if (jogadores[0].Num_Pecas_Mao < jogadores[1].Num_Pecas_Mao) {
      turno = 2;
    }
    doisJogadores();
}
