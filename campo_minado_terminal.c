/*Campo Minado no terminal*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
const int TAMANHO = 10;

void limpar_buffer() {
    char c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

int contar_pontos(int tamanho, int matriz[tamanho][tamanho]) {
    int i, j;
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            if (matriz[i][j] == 0) {
                return 0;
            }
        }
    }
    
    return 1;
}

void criar_tabuleiro(int tamanho, int matriz[tamanho][tamanho])  {
    int i, j, k;
    srand(time(NULL));
    
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            matriz[i][j] = 0;
        }
    }
    
    for (k = 1; k <= tamanho*2; k++) {
        matriz[rand() % tamanho][rand() % tamanho] = -1;
    }
    
}

void imprimir_tabuleiro(int tamanho, int matriz[tamanho][tamanho]) {
    int i, j;
    
    for (i = -1; i < tamanho; i++) {
        for (j = -1; j < tamanho; j++) {
            if (i == -1 && j == -1) {
                printf("    ");
            } else if (i == -1) {
                printf(" %d ", j+1);
            } else if (j == -1) {
                if (i+1 < tamanho) {
                    printf(" %d  ", i+1);
                } else {
                    printf(" %d ", i+1);
                }
            } else if (matriz[i][j] == 0 || matriz[i][j] == -1) {
                printf(" # ");
            } else if (matriz[i][j] == 10) {
                printf(" - ");
            } else if (matriz[i][j] == -2) {
                printf(" B ");
            } else {
                printf(" %d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

int contar_vizinhos(int tamanho, int matriz[tamanho][tamanho] ,int x, int y) {
    int i, j, cont = 0;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (x+i >= 0 && y+j >= 0 && x+i < tamanho && y+j < tamanho && (i != 0 || j != 0)) {
                if (matriz[x+i][y+j] == -1 || matriz[x+i][y+j] == -2) {
                    cont += 1;
                }
            }
        
        }
    }
    
    return cont;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int x, y, game_over = 0, perdeu = 0, ganhou = 0;
    char jogada;
    
    criar_tabuleiro(TAMANHO, tabuleiro);
    
    while (!game_over) {
        imprimir_tabuleiro(TAMANHO, tabuleiro);
        printf("Informe se quer testar (T) ou jogar a bandeira (B): ");
        scanf("%c", &jogada);
        limpar_buffer();

        while (jogada != 'T' && jogada != 'B')
        {
            printf("So pode jogar B ou T: ");
            scanf("%c", &jogada);
            limpar_buffer();
        }
        

        printf("Informe uma posicao para testar ou colocar a bandeira (x, y): ");
        scanf("%d%d", &x, &y);
        limpar_buffer();
        x--, y--;
        
        while (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO)
        {
            printf("Partida invalida, informe novamente: ");
            scanf("%d%d", &x, &y);
            limpar_buffer();
            x--, y--;
        }
        
        if (jogada == 'T') {
            if (tabuleiro[x][y] == -1 || tabuleiro[x][y] == -2) {
                game_over = 1;
                perdeu = 1;
            } else if (contar_vizinhos(TAMANHO, tabuleiro, x, y) > 0) {
                tabuleiro[x][y] = contar_vizinhos(TAMANHO, tabuleiro, x, y);
            } else {
                tabuleiro[x][y] = 10;
            }
        } else {
            if (tabuleiro[x][y] == -1) {
                tabuleiro[x][y] = -2;
            } else {
                game_over = 1;
                perdeu = 1;
            }
        }
        
        if (!game_over) {
            game_over = contar_pontos(TAMANHO, tabuleiro);
        }
        ganhou = !perdeu;
    }
    
    if (ganhou) {
        printf("Parabens! voce ganhou!");
    }
    
    if (perdeu) {
        printf("Infelizmente voce perdeu, tente novamente.");
    }
    
    getch();
    return 0;
}