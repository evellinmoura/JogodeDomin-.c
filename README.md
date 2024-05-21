# JogodeDomin-.c
Esse projeto consiste em um programa de jogo de domino 
feito todo em llinguagem C, com as seguintas capacidades:
1. Salvar, a qualquer momento, o estado atual da partida em um arquivo externo;
2. Continuar um jogo em andamento lendo suas informações/estados a partir de um
arquivo externo, salvo após o fechamento do programa;
3. Simular uma partida completa de dominó para 2 jogadores, cada um com seu próprio
turno;
4. Ter uma Interface compreensível o suficiente para facilitar a jogatina, exibindo a mão
atual do jogador, a quantidade de peças na mão do adversário, as peças em campo e a
quantidade de peças disponíveis para compra em cada turno.
------------------------------------------------------------------------------------------
Regras do jogo de dominó:
• O jogo começa com um conjunto de 28 peças únicas e diferentes, variando de
[0|0] até [6|6].
• Cada jogador começa comprando 7 peças.
• O jogador inicial é o que possui a dupla mais alta. Se nenhum jogador possuir
uma dupla, o que tiver a maior soma inicia. Em caso de empate na soma, o
jogador com a peça de maior número em sua composição começa.
• Em cada vez, o jogador deve realizar uma das três ações: jogar uma peça de sua
mão, comprar peças da mesa até que seja possível jogar ou passar a vez, se todas
as peças da mesa estiverem esgotadas.
• As regras para jogar uma peça da mão para a mesa são as seguintes: é permitido
jogar peças que tenham um lado com o mesmo número do lado esquerdo da
peça mais à esquerda jogada ou um lado com o mesmo número do lado direito
da peça mais à direita. Se ambas as possibilidades forem o mesmo número, o
jogador pode escolher em que lado quer jogar a peça.
• Após a jogada, a peça jogada deve se conectar à peça que estava em mesa pelo
lado com o número em comum, formando assim uma sequência linear de peças.
