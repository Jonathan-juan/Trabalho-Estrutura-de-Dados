#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "uno.h"

Carta* criar_carta(Cor cor, TipoCarta tipo, int valor) {
    Carta *c = malloc(sizeof(Carta));
    c->cor = cor;
    c->tipo = tipo;
    c->valor = valor;
    c->proxima = NULL;
    return c;
}

void adicionar_carta(Carta **lista, Carta *nova) {
    nova->proxima = *lista;
    *lista = nova;
}

Carta* remover_carta(Carta **lista, int indice) {
    if (*lista == NULL) return NULL;

    Carta *atual = *lista;
    Carta *anterior = NULL;
    int i = 0;

    if (indice == 0) {
        *lista = atual->proxima;
        atual->proxima = NULL;
        return atual;
    }

    while (atual != NULL && i < indice) {
        anterior = atual;
        atual = atual->proxima;
        i++;
    }

    if (atual == NULL) return NULL; 
    anterior->proxima = atual->proxima;
    atual->proxima = NULL;
    return atual;
}

void inicializar_baralho(Baralho *baralho) {
    baralho->topo = NULL;
    for (int c = 0; c < 4; c++) { 
        adicionar_carta(&baralho->topo, criar_carta(c, NUMERO, 0));
        for (int v = 1; v <= 9; v++) {
            adicionar_carta(&baralho->topo, criar_carta(c, NUMERO, v));
            adicionar_carta(&baralho->topo, criar_carta(c, NUMERO, v));
        }
        adicionar_carta(&baralho->topo, criar_carta(c, MAIS_DOIS, -1));
        adicionar_carta(&baralho->topo, criar_carta(c, MAIS_DOIS, -1));
        adicionar_carta(&baralho->topo, criar_carta(c, PULAR, -1));
        adicionar_carta(&baralho->topo, criar_carta(c, PULAR, -1));
        adicionar_carta(&baralho->topo, criar_carta(c, INVERTER, -1));
        adicionar_carta(&baralho->topo, criar_carta(c, INVERTER, -1));
    }
    for (int i = 0; i < 4; i++) {
        adicionar_carta(&baralho->topo, criar_carta(CORINGA, NUMERO, -1));
        adicionar_carta(&baralho->topo, criar_carta(CORINGA, MAIS_QUATRO, -1)); 
    }
}

void embaralhar_baralho(Baralho *baralho) {
    if (baralho->topo == NULL || baralho->topo->proxima == NULL) return;

    int count = 0;
    Carta *atual = baralho->topo;
    while (atual) {
        count++;
        atual = atual->proxima;
    }

    Carta **array_cartas = malloc(count * sizeof(Carta*));
    atual = baralho->topo;
    for (int i = 0; i < count; i++) {
        array_cartas[i] = atual;
        atual = atual->proxima;
    }

    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta *temp = array_cartas[i];
        array_cartas[i] = array_cartas[j];
        array_cartas[j] = temp;
    }

    baralho->topo = array_cartas[0];
    for (int i = 0; i < count - 1; i++) {
        array_cartas[i]->proxima = array_cartas[i+1];
    }
    array_cartas[count-1]->ima = NULL;

    free(array_cartas);
}

void distribuir_cartas(Baralho *baralho, Jogador *jogadores, int qtd) {
    for (int i = 0; i < 7; i++) { 
        for (int j = 0; j < qtd; j++) {prox
            Carta *c = comprar_carta(baralho);
            if (c) {
                adicionar_carta(&jogadores[j].mao, c);
            }
        }
    }
}

void exibir_mao(Jogador jogador) {
    printf("Mão de %s:\n", jogador.nome);
    Carta *atual = jogador.mao;
    int i = 1;
    while (atual) {
        printf("%d) ", i++);
        switch (atual->cor) {
            case VERMELHO: printf("Vermelho "); break;
            case VERDE: printf("Verde "); break;
            case AZUL: printf("Azul "); break;
            case AMARELO: printf("Amarelo "); break;
            case CORINGA: printf("Curinga "); break;
        }
        if (atual->tipo == NUMERO) printf("%d", atual->valor);
        else if (atual->tipo == MAIS_DOIS) printf("+2");
        else if (atual->tipo == PULAR) printf("Pular");
        else if (atual->tipo == INVERTER) printf("Inverter");
        else if (atual->tipo == MAIS_QUATRO) printf("+4");
        printf("\n");
        atual = atual->proxima;
    }
}

int pode_jogar(Carta *carta, Carta *pilha_topo) {
    
    if (carta->cor == CORINGA) return 1;

    return carta->cor == pilha_topo->cor ||
           (carta->tipo == NUMERO && pilha_topo->tipo == NUMERO && carta->valor == pilha_topo->valor) ||
           carta->tipo == pilha_topo->tipo;
}

Carta* comprar_carta(Baralho *baralho) {
    if (baralho->topo == NULL) return NULL;
    Carta *c = baralho->topo;
    baralho->topo = c->proxima;
    c->proxima = NULL;
    return c;
}

void descartar_carta(Carta **pilha_descarte, Carta *carta) {
    adicionar_carta(pilha_descarte, carta);
}

void salvar_pontuacao(Jogador *jogadores, int qtd) {
    FILE *f = fopen("placar.txt", "a");
    if (!f) {
        printf("Erro ao abrir o arquivo placar.txt para escrita.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        fprintf(f, "%s: %d pontos\n", jogadores[i].nome, jogadores[i].pontuacao);
    }
    fclose(f);
}

void exibir_placar() {
    FILE *f = fopen("placar.txt", "r");
    if (!f) {
        printf("Nenhum placar salvo.\n");
        return;
    }
    printf("\n=== PLACAR ===\n");
    char linha[100];
    while (fgets(linha, sizeof(linha), f)) {
        printf("%s", linha);
    }
    fclose(f);
}


