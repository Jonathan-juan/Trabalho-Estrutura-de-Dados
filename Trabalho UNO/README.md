# Jogo de UNO Simplificado em C

## Nome do Jogo
UNO Simplificado

## Regras Básicas
Este é um UNO mais simples, feito para dois jogadores. O objetivo é acabar com suas cartas primeiro.

**Tipos de Cartas:**
- **Números:** De 0 a 9, em Vermelho, Verde, Azul, Amarelo.
- **Especiais:**
    - **+2:** Próximo jogador compra 2 cartas e perde a vez.
    - **Pular:** Próximo jogador perde a vez.
    - **Inverter:** Muda o sentido do jogo (aqui, funciona como Pular).
    - **Coringa:** Você escolhe a cor que o jogo segue.
    - **+4:** Próximo jogador compra 4 cartas, perde a vez e você escolhe a cor.

**Como Jogar:**
1. Cada um começa com 7 cartas.
2. Uma carta é virada para começar a pilha de descarte.
3. Na sua vez, jogue uma carta que combine com a cor ou o número/símbolo da carta de cima da pilha.
4. Se não tiver carta para jogar, compre uma. Se puder jogar a que comprou, jogue. Se não, a vez passa.
5. Quem ficar sem cartas primeiro, ganha a rodada.

**Pontuação:**
- O vencedor da rodada ganha 100 pontos.
- As pontuações são salvas no arquivo `placar.txt` automaticamente.

## Como Compilar e Rodar

### O que você precisa
Um compilador de C, tipo o GCC.

### Para Compilar
Abra o terminal na pasta onde estão os arquivos `main.c` e `uno.c` e digite:

```bash
gcc main.c uno.c -o uno_game
```

Isso vai criar um arquivo executável chamado `uno_game`.

### Para Rodar
No terminal, digite:

```bash
./uno_game
```

O jogo vai aparecer no terminal, com opções para começar ou ver o placar.

## Como o Código Está Organizado

O projeto tem três arquivos principais:

-   `main.c`: É onde o jogo "acontece". Tem a parte principal que roda o jogo, interage com você e chama as outras funções.

-   `uno.h`: Este é o "sumário" do projeto. Ele mostra o que são as cartas (`struct Carta`), os jogadores (`struct Jogador`), o baralho (`struct Baralho`), e os tipos de cor (`enum Cor`) e carta (`enum TipoCarta`). Também lista as funções que existem no `uno.c`.

-   `uno.c`: Aqui estão as "receitas" de como as coisas funcionam. Por exemplo, como criar cartas, embaralhar, distribuir, jogar, comprar, descartar, e como salvar e mostrar as pontuações.

### Funções Importantes:

-   `inicializar_baralho`: Monta o baralho completo do UNO.
-   `embaralhar_baralho`: Mistura as cartas.
-   `distribuir_cartas`: Dá as cartas para os jogadores no começo.
-   `exibir_mao`: Mostra as cartas que você tem na mão.
-   `pode_jogar`: Vê se a carta que você quer jogar é válida.
-   `comprar_carta`: Pega uma carta do baralho.
-   `descartar_carta`: Coloca uma carta na pilha de descarte.
-   `salvar_pontuacao`: Guarda a pontuação no `placar.txt`.
-   `exibir_placar`: Mostra as pontuações salvas.
-   `remover_carta`: Tira uma carta da sua mão.

