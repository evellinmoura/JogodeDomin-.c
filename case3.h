#include <stdio.h>

void regrasDoJogo() {
    int opcao = -1;

    while(opcao != 0) {
        printf("\nREGRAS DO JOGO:\n");
        printf("1. Ver regras\n");
        printf("0. Voltar para o menu principal\n");
        scanf("%d", &opcao);
        printf("\n");


        switch (opcao) {
            case 1:
printf("\n• O jogo começa com um conjunto de 28 peças únicas e diferentes, variando de [0|0] até [6|6].\n");
printf("• Cada jogador começa comprando 7 peças.\n");
printf("• O jogador inicial eh o que possui a dupla mais alta. Se nenhum jogador possuir uma dupla, o que tiver a maior soma inicia. Em caso de empate na soma, o jogador com a peça de maior numero em sua composicao comeca.\n");
printf("• Em cada vez, o jogador deve realizar uma das tres acoes: jogar uma peça de sua mao, comprar pecas da mesa ate que seja possivel jogar ou passar a vez, se todas as pecas da mesa estiverem esgotadas.\n");
                printf("• As regras para jogar uma peça da mao para a mesa sao as seguintes: eh permitido jogar pecas que tenham um lado com o mesmo numero do lado esquerdo da peca mais a esquerda jogada ou um lado com o mesmo numero do lado direito da peca mais a direita. Se ambas as possibilidades forem o mesmo numero, o jogador pode escolher em que lado quer jogar a peca.\n");
                printf("• Apos a jogada, a peca jogada deve se conectar a peça que estava em mesa pelo lado com o numero em comum, formando assim uma sequencia linear de pecas.\n");
                break;
            case 0:
                printf("Voltando para o menu principal...\n");
                printf("\n");
          
                return; // Retorna ao menu principal

            default:
                printf("Opção invalida. Escolha novamente.\n");
        }
    }
}
