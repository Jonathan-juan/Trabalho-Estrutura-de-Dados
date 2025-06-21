#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uno.h"

int main() {
    Baralho baralho;
    Jogador jogadores[2] = { {"Alice", NULL, 0}, {"Bob", NULL, 0} };
    Carta *pilha_descarte = NULL; 
    int opcao;

    do {
        printf("\n=== JOGO DE UNO SIMPLIFICADO ===\n");
        printf("1. Novo jogo\n2. Ver placar\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
           
            jogadores[0].mao = NULL;
            jogadores[1].mao = NULL;
            pilha_descarte = NULL;

            inicializar_baralho(&baralho);
            embaralhar_baralho(&baralho);
            distribuir_cartas(&baralho, jogadores, 2);

            
            Carta *primeira_carta = comprar_carta(&baralho);
            if (primeira_carta) {
                descartar_carta(&pilha_descarte, primeira_carta);
                printf("\nCarta inicial na mesa: ");
               
                switch (pilha_descarte->cor) {
                    case VERMELHO: printf("Vermelho "); break;
                    case VERDE: printf("Verde "); break;
                    case AZUL: printf("Azul "); break;
                    case AMARELO: printf("Amarelo "); break;
                    case CORINGA: printf("Curinga "); break;
                }
                if (pilha_descarte->tipo == NUMERO) printf("%d\n", pilha_descarte->valor);
                else if (pilha_descarte->tipo == MAIS_DOIS) printf("+2\n");
                else if (pilha_descarte->tipo == PULAR) printf("Pular\n");
                else if (pilha_descarte->tipo == INVERTER) printf("Inverter\n");
                else if (pilha_descarte->tipo == MAIS_QUATRO) printf("+4\n");
            }

            int jogador_atual_idx = 0;
            int sentido_horario = 1; 
            int jogo_terminou = 0;

            while (!jogo_terminou) {
                Jogador *jogador_atual = &jogadores[jogador_atual_idx];
                printf("\n--- Vez de %s ---\n", jogador_atual->nome);
                printf("Carta no topo da pilha: ");
                switch (pilha_descarte->cor) {
                    case VERMELHO: printf("Vermelho "); break;
                    case VERDE: printf("Verde "); break;
                    case AZUL: printf("Azul "); break;
                    case AMARELO: printf("Amarelo "); break;
                    case CORINGA: printf("Curinga "); break;
                }
                if (pilha_descarte->tipo == NUMERO) printf("%d\n", pilha_descarte->valor);
                else if (pilha_descarte->tipo == MAIS_DOIS) printf("+2\n");
                else if (pilha_descarte->tipo == PULAR) printf("Pular\n");
                else if (pilha_descarte->tipo == INVERTER) printf("Inverter\n");
                else if (pilha_descarte->tipo == MAIS_QUATRO) printf("+4\n");

                exibir_mao(*jogador_atual);

                int escolha_carta;
                printf("Escolha o número da carta para jogar (0 para comprar): ");
                scanf("%d", &escolha_carta);

                if (escolha_carta == 0) {
                    Carta *nova_carta = comprar_carta(&baralho);
                    if (nova_carta) {
                        adicionar_carta(&jogador_atual->mao, nova_carta);
                        printf("%s comprou uma carta.\n", jogador_atual->nome);
                    } else {
                        printf("Baralho vazio! Não é possível comprar.\n");
                    }
                } else {
                    Carta *carta_jogada = remover_carta(&jogador_atual->mao, escolha_carta - 1);
                    if (carta_jogada && pode_jogar(carta_jogada, pilha_descarte)) {
                        printf("%s jogou uma carta!\n", jogador_atual->nome);
                        descartar_carta(&pilha_descarte, carta_jogada);

                        
                        if (carta_jogada->tipo == PULAR) {
                            printf("Vez pulada!\n");
                            jogador_atual_idx = (jogador_atual_idx + sentido_horario + 2) % 2; 
                        } else if (carta_jogada->tipo == INVERTER) {
                            printf("Sentido invertido!\n");
                            sentido_horario *= -1;
                        } else if (carta_jogada->tipo == MAIS_DOIS) {
                            printf("Próximo jogador compra 2 cartas!\n");
                            int proximo_jogador_idx = (jogador_atual_idx + sentido_horario + 2) % 2;
                            for (int i = 0; i < 2; i++) {
                                Carta *c = comprar_carta(&baralho);
                                if (c) adicionar_carta(&jogadores[proximo_jogador_idx].mao, c);
                            }
                        } else if (carta_jogada->tipo == MAIS_QUATRO) {
                            printf("Próximo jogador compra 4 cartas e a cor muda!\n");
                            int proximo_jogador_idx = (jogador_atual_idx + sentido_horario + 2) % 2;
                            for (int i = 0; i < 4; i++) {
                                Carta *c = comprar_carta(&baralho);
                                if (c) adicionar_carta(&jogadores[proximo_jogador_idx].mao, c);
                            }
                            
                            int nova_cor_escolha;
                            printf("Escolha a nova cor (0-Vermelho, 1-Verde, 2-Azul, 3-Amarelo): ");
                            scanf("%d", &nova_cor_escolha);
                            pilha_descarte->cor = (Cor)nova_cor_escolha;
                        } else if (carta_jogada->cor == CORINGA) {
                            printf("Coringa jogado! Escolha a nova cor.\n");
                            int nova_cor_escolha;
                            printf("Escolha a nova cor (0-Vermelho, 1-Verde, 2-Azul, 3-Amarelo): ");
                            scanf("%d", &nova_cor_escolha);
                            pilha_descarte->cor = (Cor)nova_cor_escolha;
                        }

                        
                        if (jogador_atual->mao == NULL) {
                            printf("%s venceu a rodada!\n", jogador_atual->nome);
                            jogador_atual->pontuacao += 100; 
                            jogo_terminou = 1;
                        }
                    } else {
                        printf("Jogada inválida! Tente novamente.\n");
                        adicionar_carta(&jogador_atual->mao, carta_jogada); 
                    }
                }

                if (!jogo_terminou) {
                    jogador_atual_idx = (jogador_atual_idx + sentido_horario + 2) % 2;
                }
            }

            salvar_pontuacao(jogadores, 2);
        } else if (opcao == 2) {
            exibir_placar();
        } else if (opcao != 0) {
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    printf("Obrigado por jogar!\n");
    return 0;
}


