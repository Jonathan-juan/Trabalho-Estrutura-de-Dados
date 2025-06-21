#ifndef UNO_H
#define UNO_H

typedef enum {
    VERMELHO, VERDE, AZUL, AMARELO, CORINGA
} Cor;

typedef enum {
    NUMERO, MAIS_DOIS, PULAR, INVERTER, MAIS_QUATRO 
} TipoCarta;

typedef struct Carta {
    Cor cor;
    TipoCarta tipo;
    int valor; 
    struct Carta *prox;
} Carta;

typedef struct {
    char nome[50];
    Carta *mao;
    int pontuacao;
} Jogador;

typedef struct {
    Carta *topo;
} Baralho;

void adicionar_carta(Carta **lista, Carta *nova);
Carta* remover_carta(Carta **lista, int indice);
Carta* comprar_carta(Baralho *baralho);
void descartar_carta(Carta **pilha_descarte, Carta *carta);

void inicializar_baralho(Baralho *baralho);
void embaralhar_baralho(Baralho *baralho);
void distribuir_cartas(Baralho *baralho, Jogador *jogadores, int qtd);
void exibir_mao(Jogador jogador);
int pode_jogar(Carta *carta, Carta *pilha_topo);

void salvar_pontuacao(Jogador *jogadores, int qtd);
void exibir_placar();

#endif