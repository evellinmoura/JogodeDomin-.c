#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "case1.h"
#include "case2.h"
#include "case3.h"


int main() {
    int resp_m;//variavel pra ser a opção do usuario 
    int contador_m = 10; // variavel pra fazer o while rodar 

    while (contador_m == 10) { // enquanto o contador for igual a 10 ele continua rodando
        printf("\nSEJA BEM VINDO AO DOMINOS!!!\n"); //printa isso na tela pro usuario ler 
        printf("Escolha uma ação:\n");
        printf("1. Jogar (2 jogadores)\n");
        printf("2. Jogar jogo salvo\n");
        printf("3. Regras do Jogo\n");
        printf("4. Sair do jogo\n");
        printf("Digite o numero da opção: ");
        if (scanf("%d", &resp_m) != 1 ) { // Caso a opção dele for diferente de um inteiro ele retorna o print aqui:
            printf("Entrada inválida! Por favor, digite um número.\n");
            scanf("%*s"); // limpar buffer do teclado
            continue;//continua, volta pro menu dnv
        }

        switch (resp_m) { //faz a escolha do usuario
            case 1:
                jogarDominos(); // chama a função jogarDominos
              
                break;

            case 2:
                jogoSalvo();
                break;

            case 3:
                regrasDoJogo();
                break;

            case 4:
                contador_m = 11;
                break;

            default:
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
        }
    }

    return 0;
}
