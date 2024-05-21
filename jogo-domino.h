#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PECAS_JOGO 28
#define MAX_PECAS_MAOS 21
#define MAX_PECA_MESA  28

// Structs:
typedef struct {
  int ladoE, ladoD;
} PecaDomino;
typedef struct {
  PecaDomino mao[MAX_PECAS_MAOS];
  int Num_Pecas_Mao;
} Jogador; // participantes
typedef struct {
  PecaDomino pecas[MAX_PECA_MESA];
  int Num_Pecas_Mesa;
} Mesa; // local

// variveis globais
PecaDomino pecas[MAX_PECAS_JOGO];
Jogador jogadores[2];
int qtdPecasCompradas;
Mesa mesa;
int turno;
 
// Função para inicializar as peças de domino
void inicializarPecas() {
  int index = 0;                 // indice
  for (int i = 0; i <= 6; i++) { // defini o primeiro numero da peça do domino
    for (int j = i; j <= 6; j++) { // começa em i e vai até 6,
      pecas[index].ladoE = i;
           // atribue os valores i e j aos lados A e B (respectivamente)
      pecas[index].ladoD = j;
      index++;
    }
  }
}
// funcao para embaralhar as pecas
void embaralharPecas() {
  srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios com base no tempo atual. 
  for (int i = 0; i < MAX_PECAS_JOGO; i++) {// percorre todas as peças no array pecas.
    int k = rand() % MAX_PECAS_JOGO;// Gera um número aleatório k que será usado para selecionar uma posição aleatória no array pecas.
    PecaDomino copia_p = pecas[i];// Faz uma cópia da peça na posição i do array pecas e armazena em copia_p.
    pecas[i] = pecas[k];//A peça na posição i do array pecas recebe a peça na posição aleatória k. Isso realiza a troca das peças.
    pecas[k] = copia_p;
    // A peça na posição aleatória k do array pecas recebe a cópia da peça que estava originalmente na posição i. Isso completa a troca das peças, garantindo o embaralhamento.
  }
}
// funcao para distribuir as pecas
void distribuirPecas() {
  for (int i = 0; i < 7; i++) {
    jogadores[0].mao[i] = pecas[i]; // vai pegar as peças de  0 a 6 do vetor
    jogadores[1].mao[i] = pecas[i + 7]; // de 7 a 13
  }
  jogadores[0].Num_Pecas_Mao = 7;// atribui 7 a numero de peças na mão do jogador 1
  jogadores[1].Num_Pecas_Mao = 7;// atribui 7 a numero de peças na mão do jogador 2 
  qtdPecasCompradas = 14; // atribui 14 a quantidade de peças compradas
  // Ele coloca 7 pro numero de peças da mão de cada um
  //e como eles tem 7 cada um, eles compraram 14 peças
  //Nas structs tem definiada a variavel int Num_Pecas_Mao; que ela quarda o numero de peças na mão de cada jogador Seja o jogador [0] ou o jogador[1] 
}

// funcao para mostrar a mes
void mostrarMesa() {
  printf("\n      Pecas na mesa:      \n");
  for (int i = 0; i < mesa.Num_Pecas_Mesa; i++) {// vai de 0 até o nomero de peças na mesa
    printf("[%d|%d]", mesa.pecas[i].ladoE, mesa.pecas[i].ladoD);//printa o lado D e E das peças
  }
  printf("\n");
}
// funcao mostrar mao
void mostrarMao(int idjogador) {// id jogador é pra idicar qual jogador ele vai imprimir a mão
  printf("\nSua mao:\n");
  for (int i = 0; i < jogadores[idjogador].Num_Pecas_Mao; i++) {
    printf("(%d) [%d|%d]\n", i, jogadores[idjogador].mao[i].ladoE,
           jogadores[idjogador].mao[i].ladoD); // imprime lado E e D da peça
  }
  printf("\n");
}



// Função pra adicionar peça a MEsa
void adicionarPecaMesa(PecaDomino peca, int idJogador, int indicePeca,int lado) {
  /*
PecaDomino peca: representa a peça de dominó que será adicionada à mesa.
int idJogador: identifica o jogador (embora não seja utilizado explicitamente na função).
int indicePeca: indica o índice da peça na mão do jogador (também não usado na função).
int lado: determina em qual lado da mesa a peça será adicionada (1 para esquerda, 2 para direita).
 */
  // 1 == esquerda, 2 == direita
  if (lado == 1) {
    // Empurrar todo o vetor Mesa uma casa para a direita
    for (int i = mesa.Num_Pecas_Mesa - 1; i >= 0; i--) {
      /*i é inicializado com mesa.Num_Pecas_Mesa - 1, que é o índice da última peça na mesa.
      A condição i >= 0 garante que o loop seja executado até que todas as peças sejam deslocadas, indo do índice mesa.Num_Pecas_Mesa - 1 até 0. ( como se fosse enquanto 9>=0) */
      mesa.pecas[i + 1] = mesa.pecas[i];
    }
    mesa.Num_Pecas_Mesa++; // Incrementa onumero  de peças na Mesa apos o deslocamento     
    mesa.pecas[0] = peca; // Adiciona a peça na posiição 0 do vetor Mesa
    
  } else if (lado == 2) {
    mesa.pecas[mesa.Num_Pecas_Mesa] =peca; 
    /*A nova peça é colocada na posição mesa.Num_Pecas_Mesa, que representa a próxima posição disponível na mesa (no final do vetor de peças).
O número total de peças na mesa é incrementado (mesa.Num_Pecas_Mesa++).
*/
    mesa.Num_Pecas_Mesa++;
  }
}
// função que verificar quem começa e joga a peça na mesa do jogador que começar
void quemComeca() {
  PecaDomino maiorPeca[2]= {-1, -1}; //
 // maiorPeca[0].ladoE = -1; maiorPeca[0].ladoD = -1;
 //maiorPeca[1].ladoE = -1; maiorPeca[1].ladoD = -1;
  int indiceMaiorPeca1, indiceMaiorPeca2;

  // Encontra a maior peça de cada jogador com valor duplo (ladoA == ladoB) e guarda o indice dela 
  for (int i = 0; i < 7; i++) {
    if (jogadores[0].mao[i].ladoE == jogadores[0].mao[i].ladoD) { //[9|9] > []
      if (jogadores[0].mao[i].ladoE > maiorPeca[0].ladoE) {
        maiorPeca[0] = jogadores[0].mao[i];
        indiceMaiorPeca1 = i;
      }
    } 
    if (jogadores[1].mao[i].ladoE == jogadores[1].mao[i].ladoD) {
      if (jogadores[1].mao[i].ladoE > maiorPeca[1].ladoE) {
        maiorPeca[1] = jogadores[1].mao[i];
        indiceMaiorPeca2 = i;
      }
    }
  }

  // Adiciona a peça do jogador com a maior peça dupla a mesa
  if (maiorPeca[0].ladoE > maiorPeca[1].ladoE) {//maior peça do jogador 1 > maior peça do jogador 2
    //Usa adicionarPecaMesa para colocar a maior peça do jogador na mesa.
    adicionarPecaMesa(jogadores[0].mao[indiceMaiorPeca1], 0, indiceMaiorPeca1,2);
    printf("Jogador 1 jogou a peca [%d|%d]\n", 
    jogadores[0].mao[indiceMaiorPeca1].ladoE,jogadores[0].mao[indiceMaiorPeca1].ladoD);
    
    //percorre a da mão do jogador a partir da posição da peça que foi jogada (indiceMaiorPeca1).
    //A cada iteração, move a peça na posição i + 1 para a posição i. 
    //Desloca todas as peças à direita da peça jogada uma posição à esquerda.
    for (int i = indiceMaiorPeca1; i < jogadores[0].Num_Pecas_Mao - 1; i++) {
      jogadores[0].mao[i] = jogadores[0].mao[i + 1];
    }
    jogadores[0].Num_Pecas_Mao--;//Reduz o número total de peças na mão do jogador 1 em 1, 
    turno=2;
    return;
  } 
  else if (maiorPeca[0].ladoE < maiorPeca[1].ladoE) {///maior peça do jogador 1 < maior peça do jogador 2
    //Usa adicionarPecaMesa para colocar a maior peça do jogador na mesa.
    adicionarPecaMesa(jogadores[1].mao[indiceMaiorPeca2], 1, indiceMaiorPeca2, 2);
    printf("Jogador 2 jogou a peca [%d|%d]\n",
           jogadores[1].mao[indiceMaiorPeca2].ladoE,jogadores[1].mao[indiceMaiorPeca2].ladoD);
    //percorre a da mão do jogador a partir da posição da peça que foi jogada (indiceMaiorPeca1).
    //A cada iteração, move a peça na posição i + 1 para a posição i. 
    //Desloca todas as peças à direita da peça jogada uma posição à esquerda.
    for (int i = indiceMaiorPeca2; i < jogadores[1].Num_Pecas_Mao - 1; i++) {
      jogadores[1].mao[i] = jogadores[1].mao[i + 1];
    }
      jogadores[1].Num_Pecas_Mao--;
      turno=1;
      return;
  }

  //-------------------------------------------------------------------------//

  int maiorSomaPeca[2] = {-1, -1}; // Inicializa como -1  para encontrar a maior soma da peça
  int indiceMaiorSomaPeca1,indiceMaiorSomaPeca2; //variavei pra guardar o indice 
  
  // Encontra a maior soma das peças de cada jogador
  for (int i = 0; i < 7; i++) {
    // ele verifica se a soma dos lados de uma peça é maior que -1(maiorSomaPeça)
    if ((jogadores[0].mao[i].ladoE + jogadores[0].mao[i].ladoD) > maiorSomaPeca[0]) {
      maiorSomaPeca[0] = jogadores[0].mao[i].ladoE + jogadores[0].mao[i].ladoD;//se for ele substitui
      indiceMaiorSomaPeca1 = i;//gurada o indice
    }
    if ((jogadores[1].mao[i].ladoE + jogadores[1].mao[i].ladoD) >maiorSomaPeca[1]) {
      maiorSomaPeca[1] = jogadores[1].mao[i].ladoE + jogadores[1].mao[i].ladoD;
      indiceMaiorSomaPeca2 = i;
    }
  }
  
//verifica quem tem a maior soma e coloca essa peça na mesa 
  if (maiorSomaPeca[0] > maiorSomaPeca[1]) { 
     adicionarPecaMesa(jogadores[0].mao[indiceMaiorSomaPeca1], 0,indiceMaiorSomaPeca1, 2);
     printf("Jogador 1 jogou a peca [%d|%d]\n",jogadores[0].mao[indiceMaiorPeca1].ladoE,
      jogadores[0].mao[indiceMaiorPeca1].ladoD);
    //percorre a da mão do jogador a partir da posição da peça que foi jogada (indiceMaiorPeca1).
    //A cada iteração, move a peça na posição i + 1 para a posição i. 
    //Desloca todas as peças à direita da peça jogada uma posição à esquerda.
      for (int i = indiceMaiorPeca1; i < jogadores[0].Num_Pecas_Mao - 1; i++) {
          jogadores[0].mao[i] = jogadores[0].mao[i + 1];
       }
      jogadores[0].Num_Pecas_Mao--;//Reduz o número total de peças na mão do jogador 1 em 1,
      turno=2;
      return;
    } 
  else {
    adicionarPecaMesa(jogadores[1].mao[indiceMaiorSomaPeca2], 1,indiceMaiorSomaPeca2, 2);
    printf("Jogador 2 jogou a peca [%d|%d]\n",jogadores[1].mao[indiceMaiorPeca2].ladoE,
           jogadores[1].mao[indiceMaiorPeca2].ladoD);
    //percorre a da mão do jogador a partir da posição da peça que foi jogada (indiceMaiorPeca1).
    //A cada iteração, move a peça na posição i + 1 para a posição i. 
    //Desloca todas as peças à direita da peça jogada uma posição à esquerda.
    for (int i = indiceMaiorPeca2; i < jogadores[1].Num_Pecas_Mao - 1; i++) {
      jogadores[1].mao[i] = jogadores[1].mao[i + 1];
    }
    jogadores[1].Num_Pecas_Mao--;//Reduz o número total de peças na mão do jogador 1 em 1,
    turno=1;
    return;
  }
}






// Função para inverter a peça
void inverterPeca(PecaDomino *peca) {// A função inverterPeca recebe um ponteiro para uma estrutura PecaDomino como argumento.
  int temp = peca->ladoE; //Salva o valor do ladoE da estrutura apontada por peca na variável temporária temp.
  peca->ladoE = peca->ladoD;//Atribui o valor do ladoD da estrutura apontada por peca ao membro ladoE, efetivamente trocando os valores.
  peca->ladoD = temp; //Atribui o valor temporário (temp) aoladoD da estrutura, completando a troca. Agora, ladoD contém o valor original de ladoE.

  //peca->ladoE é uma forma de acessar o valor da variável ladoE dentro da estrutura peca.
}
// funcao para poder jogar
int podeJogar(PecaDomino *peca) {//recebe um ponteiro para uma estrutura PecaDomino chamada peca.
  // Verificar se é possivel jogar a peçaa em alguma das extremidades da Mesa

  // Lado E e Lado D da peça que se deseja jogar
  int ladoE = peca->ladoE;
  int ladoD = peca->ladoD;

//lado esquerdo primeira peça da mesa
  int mesaladoE = mesa.pecas[0].ladoE;

  // Verificar se a peça pode ser jogada no lado esquerdo da Mesa
  if (ladoD == mesaladoE) {
    return 1;
  } else if (ladoE == mesaladoE) {
    inverterPeca(peca);
    return 1;
  }
  // Verificar se a peça pode ser jogada no lado direito da Mesa
  int ultimaPecaMesa = mesa.Num_Pecas_Mesa - 1;
  int ultimaPecaladoD = mesa.pecas[ultimaPecaMesa].ladoD;
  if (ladoE == ultimaPecaladoD) {
    return 2;
  } else if (ladoD == ultimaPecaladoD) {
    // Inverter a peça e retornar 2 se for possivel jogar 
    inverterPeca(peca);
    return 2;
  }
  return 0; // Retornar 0 se nao puder jogar
}
/*

Este argumento identifica o jogador que está comprando a peça. Isso permite que a função atualize a mão do jogador correto dentro da estrutura jogadores.

jogadores[idJogador].mao: Acessa a mão do jogador determinado por idJogador.

[jogadores[idJogador].Num_Pecas_Mao]: Representa a próxima posição disponível na mão do jogador para colocar a peça adquirida.

pecas[qtdPecasCompradas]: Obtém a próxima peça do conjunto de peças disponíveis (pecas) com base no contador qtdPecasCompradas.

jogadores[idJogador].Num_Pecas_Mao++;: Incrementa o número de peças na mão do jogador após a compra.
qtdPecasCompradas++;: Atualiza o contador qtdPecasCompradas, indicando que uma nova peça foi retirada do conjunto de peças disponíveis para o jogo.

*/
// Função para comprar peça
void comprarPeca(int idJogador) {
  // Adiciona a peça comprada à mão do jogador
  jogadores[idJogador].mao[jogadores[idJogador].Num_Pecas_Mao] = pecas[qtdPecasCompradas];
  // Incrementa o número de peças na mão do jogador
  jogadores[idJogador].Num_Pecas_Mao++;
  // Atualiza o contador de peças compradas
  qtdPecasCompradas++;
}



// Função para imprimir a vez do jogador
void imprimirVezJogador( ) {
  if (turno == 1) {
    printf("\nVez do Jogador 1");
  } else {
    printf("\nVez do Jogador 2");
  }
}
//Função que salva o jogo 
void salvarJogo() {
  FILE *pecasTxt, *jogadoresTxt, *mesaTxt, *turnoTxt, *qtdPecasCompradasTxt;
  pecasTxt = fopen("pecas.txt", "wb+");
  jogadoresTxt = fopen("jogadores.txt", "wb+");
  mesaTxt = fopen("mesa.txt", "wb+");
  turnoTxt = fopen("turno.txt", "wb+");
  qtdPecasCompradasTxt = fopen("qtdPecasCompradas.txt", "wb+");
/*ptr: Ponteiro para os dados que você deseja escrever.
  size: Tamanho em bytes de cada elemento de dados.
  count: Número de elementos de dados (ou registros) que você deseja escrever.
  stream: Ponteiro para o arquivo.*/
  fwrite(&pecas, sizeof(PecaDomino) * 28, 1, pecasTxt);
  fwrite(&turno, sizeof(int), 1, jogadoresTxt);
  fwrite(&mesa, sizeof(Mesa), 1, mesaTxt);
  fwrite(&turno, sizeof(int), 1, turnoTxt);
  fwrite(&qtdPecasCompradas, sizeof(int), 1, qtdPecasCompradasTxt);
  fclose(pecasTxt);
  fclose(jogadoresTxt);
  fclose(mesaTxt);
  fclose(turnoTxt);
  fclose(qtdPecasCompradasTxt);
}
//Função que apos o jogo ser salvo, chama o que foi salvo
void carregarJogo() {
  FILE *pecasTxt, *jogadoresTxt, *mesaTxt, *turnoTxt, *qtdPecasCompradasTxt;
  pecasTxt = fopen("pecas.txt", "wb+");
  jogadoresTxt = fopen("jogadores.txt", "wb+");
  mesaTxt = fopen("mesa.txt", "wb+");
  turnoTxt = fopen("turno.txt", "wb+");
  qtdPecasCompradasTxt = fopen("qtdPecasCompradas.txt", "wb+");

  fread(&pecas, sizeof(PecaDomino) * 28, 1, pecasTxt);
  fread(&turno, sizeof(int), 1, jogadoresTxt);
  fread(&mesa, sizeof(Mesa), 1, mesaTxt);
  fread(&turno, sizeof(int), 1, turnoTxt);
  fread(&qtdPecasCompradas, sizeof(int), 1, qtdPecasCompradasTxt);
  fclose(pecasTxt);
  fclose(jogadoresTxt);
  fclose(mesaTxt);
  fclose(turnoTxt);
  fclose(qtdPecasCompradasTxt);
}
//função para passar a vez
void Passarvez() {
  if (qtdPecasCompradas >= MAX_PECAS_JOGO) {
    printf("Nenhuma peça disponível para compra. Você passou a vez.\n");
    if (turno == 1) {
      turno = 2;
    } else {
      turno = 1;
    }
  } else {
    printf("Ainda existem peças disponíveis para compra. Você não pode passar a vez.\n");

  }
  // Adicionar troca de turno após passar a vez

}


int doisJogadores() { // dentro dela ta o menu do jogo
  while (jogadores[0].Num_Pecas_Mao > 0 && jogadores[1].Num_Pecas_Mao > 0) {
    mostrarMesa();
    imprimirVezJogador();
    int opcao;
    if (turno == 1) {
      mostrarMao(0);
      printf("Digite qual a opcao desejada\n");
      printf("1. Jogar \n");
      printf("2. Comprar peca \n");
      printf("3. Passa a vez \n");
      printf("4. Salvar \n");
      printf("0. Retornar ao menu principal \n");

      if (scanf("%d", &opcao) != 1) { // Caso a opção dele for diferente de um inteiro ele retorna o print aqui:
          printf("Entrada inválida! Por favor, digite um número.\n");
          continue;//continua, volta pro menu dnv
      }
      
      switch (opcao) {
      case 1: {
        int escolha;
        printf("Jogador 1, escolha o numero da peca que deseja jogar "
               "(começando do 0): ");
       
        if (scanf("%d", &escolha) != 1) { // Caso a opção dele for diferente de um inteiro ele retorna o print aqui:
            printf("Entrada inválida! Por favor, digite um número.\n");
            scanf("%*s"); // Limpa o buffer de entrada pro usuario digitar dnv
            continue;//continua, volta pro menu dnv
        }
        
        PecaDomino pecaSelecionada = jogadores[0].mao[escolha];
        int consegueJogar = podeJogar(&pecaSelecionada);
        if (consegueJogar != 0) {
          adicionarPecaMesa(pecaSelecionada, turno - 1, escolha, consegueJogar);
          printf("\n");
          printf("Jogador 1 jogou a peca [%d|%d] ", pecaSelecionada.ladoE,
                 pecaSelecionada.ladoD);
          if (consegueJogar == 1) {
            printf("na esquerda!\n");
          } else {
            printf("na direita!\n");
          }
          for (int i = escolha; i < jogadores[0].Num_Pecas_Mao - 1; i++) {
            jogadores[0].mao[i] = jogadores[0].mao[i + 1];
          }
          jogadores[0].Num_Pecas_Mao = jogadores[0].Num_Pecas_Mao - 1;
          turno = 2;
        } else {
          printf("\n");
          printf("Voce nao pode jogar essa peca. Escolha outra.\n");
          printf("\n");
          continue;
        }
        break;
      }

      case 2: {
        if (qtdPecasCompradas < 28) {
          comprarPeca(0);
        }
        break;
      }

      case 3: {
        Passarvez();
        
      }

      case 4: {
        salvarJogo();
        break;
      }

      case 0: {
        return 0;
      }
        default:
        printf("Opção inválida! Por favor, escolha uma opção válida.\n");
      }
    }

    else {
      mostrarMao(1);
      printf("Digite qual a opcao desejada\n");
      printf("1. Jogar \n");
      printf("2. Comprar peca \n");
      printf("3. Passa a vez \n");
      printf("4. Salvar \n");
      printf("0. Retornar ao menu principal \n");

      if (scanf("%d", &opcao) != 1) { // Caso a opção dele for diferente de um inteiro ele retorna o print aqui:
          printf("Entrada inválida! Por favor, digite um número.\n");
          scanf("%*s"); // Limpa o buffer de entrada pro usuario digitar dnv
          continue;//continua, volta pro menu dnv
      }
      
      switch (opcao) {
      case 1: {
        int escolha;
        printf("Jogador 2, escolha o numero da peca que deseja jogar "
               "(começando do 0): ");

        if (scanf("%d", &escolha) != 1) { // Caso a opção dele for diferente de um inteiro ele retorna o print aqui:
            printf("Entrada inválida! Por favor, digite um número.\n");
            scanf("%*s"); // Limpa o buffer de entrada pro usuario digitar dnv
            continue;//continua, volta pro menu dnv
        }
        
        PecaDomino pecaSelecionada = jogadores[1].mao[escolha];
        int consegueJogar = podeJogar(&pecaSelecionada);
        if (consegueJogar != 0) {
          adicionarPecaMesa(pecaSelecionada, turno - 1, escolha, consegueJogar);
          printf("\n");
          printf("Jogador 2 jogou a peca [%d|%d] ", pecaSelecionada.ladoE,
                 pecaSelecionada.ladoD);
          if (consegueJogar == 1) {
            printf("na esquerda!\n");
          } else {
            printf("na direita!\n");
          }
          printf("\n");
          for (int i = escolha; i < jogadores[1].Num_Pecas_Mao - 1; i++) {
            jogadores[1].mao[i] = jogadores[1].mao[i + 1];
          }
          jogadores[1].Num_Pecas_Mao = jogadores[1].Num_Pecas_Mao - 1;
          turno = 1;
        } else {
          printf("\nVoce nao pode jogar essa peca. Escolha outra.\n");
          continue;
        }
        break;
      }
      case 2: {
        if (qtdPecasCompradas < 28) {
          comprarPeca(1);
        }
        break;
      }
        case 3:{
          Passarvez();
          
        }
      case 4: {
        salvarJogo();
        break;
      }
      case 0: {
        return 0;
      }
        default:
        printf("Opção inválida! Por favor, escolha uma opção válida.\n");
      }
    }
  }

  if (jogadores[0].Num_Pecas_Mao == 0) {
    printf("Jogador 1 venceu!\n");
    return 0;
  } else {
    printf("Jogador 2 venceu!\n");
    return 0;
  }

  return 0;
}
