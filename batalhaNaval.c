#include <stdio.h>

/*
    Curso: Análise e Desenvolvimento de Sistemas
    Trabalho: Batalha Naval – Nível Mestre
    Nível: Mestre
    Aluno: Gilberto Junior

    Descrição:
    Implementação final do nível Mestre do desafio de Batalha Naval,
    contendo tabuleiro 10x10, posicionamento de navios, matrizes de
    habilidades (cone, cruz e octaedro), e aplicação das áreas de efeito
    no tabuleiro utilizando estruturas de repetição aninhadas e condicionais.
*/


#define TAM 10
#define H 5
#define AGUA 0
#define NAVIO 3
#define HAB 5

// ------------------------------ FUNÇÕES AUXILIARES ------------------------------

void inicializar(int m[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            m[i][j] = AGUA;
}

void imprimirTabuleiro(int m[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
    printf("\n");
}

// ------------------------------ NAVIOS ------------------------------

void navioVertical(int m[TAM][TAM], int lin, int col, int tam) {
    for (int i = 0; i < tam; i++)
        m[lin + i][col] = NAVIO;
}

void navioHorizontal(int m[TAM][TAM], int lin, int col, int tam) {
    for (int j = 0; j < tam; j++)
        m[lin][col + j] = NAVIO;
}

void navioDiagonalPrincipal(int m[TAM][TAM], int lin, int col, int tam) {
    for (int k = 0; k < tam; k++)
        m[lin + k][col + k] = NAVIO;
}

void navioDiagonalSecundaria(int m[TAM][TAM], int lin, int col, int tam) {
    for (int k = 0; k < tam; k++)
        m[lin + k][col - k] = NAVIO;
}

void posicionarNavios(int m[TAM][TAM]) {
    navioVertical(m, 0, 2, 4);            // vertical
    navioHorizontal(m, 5, 0, 3);          // horizontal
    navioDiagonalPrincipal(m, 2, 5, 4);   // diagonal →
    navioDiagonalSecundaria(m, 7, 9, 3);  // diagonal ←
}

// ------------------------------ HABILIDADES ------------------------------

void habilidadeCone(int h[H][H]) {
    int centro = H / 2;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            int distancia = j - centro;
            if (distancia < 0) distancia = -distancia;

            if (distancia <= i)  // abertura aumenta conforme desce
                h[i][j] = 1;
            else
                h[i][j] = 0;
        }
    }
}

void habilidadeCruz(int h[H][H]) {
    int centro = H / 2;

    for (int i = 0; i < H; i++)
        for (int j = 0; j < H; j++)
            h[i][j] = (i == centro || j == centro) ? 1 : 0;
}

void habilidadeOctaedro(int h[H][H]) {
    int centro = H / 2;
    int raio = 1;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            int dif = abs(i - centro) + abs(j - centro);
            h[i][j] = (dif <= raio) ? 1 : 0;
        }
    }
}

// Aplica a matriz de habilidade 5x5 ao tabuleiro 10x10
void aplicarHabilidade(int m[TAM][TAM], int h[H][H], int orLin, int orCol) {
    int centro = H / 2;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (h[i][j] == 1) {
                int lin = orLin + (i - centro);
                int col = orCol + (j - centro);

                if (lin >= 0 && lin < TAM && col >= 0 && col < TAM)
                    m[lin][col] = HAB;
            }
        }
    }
}

// ------------------------------ MAIN (NÍVEL MESTRE) ------------------------------

int main() {

    int tab[TAM][TAM];
    int cone[H][H], cruz[H][H], oct[H][H];

    inicializar(tab);
    posicionarNavios(tab);

    // Criando matrizes de habilidades
    habilidadeCone(cone);
    habilidadeCruz(cruz);
    habilidadeOctaedro(oct);

    // Aplicando habilidades no tabuleiro
    aplicarHabilidade(tab, cone, 2, 2);
    aplicarHabilidade(tab, cruz, 5, 5);
    aplicarHabilidade(tab, oct, 7, 3);

    printf("TABULEIRO FINAL (0 = água, 3 = navio, 5 = habilidade):\n\n");
    imprimirTabuleiro(tab);

    return 0;
}
