#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ------------------------- STRUCT TERRITÓRIO ------------------------- */

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ----------------------- PROTÓTIPOS DE FUNÇÕES ----------------------- */

void cadastrarTerritorios(Territorio *mapa, int qtd);
void exibirMapa(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);

void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int qtd);

void liberarMemoria(Territorio *mapa, char *missaoJog1, char *missaoJog2);

/* --------------------------------------------------------------------- */
/* ------------------------- FUNÇÃO CADASTRO --------------------------- */
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Cadastro de Territórios ===\n");

    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome do Território: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do Exército: ");
        scanf(" %9s", mapa[i].cor);

        printf("Quantidades de Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/* --------------------------------------------------------------------- */
/* ------------------------- EXIBIR MAPA ------------------------------- */
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n======= MAPA ATUAL ========\n");

    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] %s\n", i, mapa[i].nome);
        printf("    Cor do Território: %s\n", mapa[i].cor);
    printf("    Quantidade de Tropas: %d\n", mapa[i].tropas);
    }
}

/* --------------------------------------------------------------------- */
/* --------------------------- ATAQUE ---------------------------------- */
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 1) {
        printf("\n❌ Tropas insuficientes para atacar!\n");
        return;
    }

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n🎲 Rolando os Dados(Boa Sorte!):\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoA);
    printf("Defensor  (%s): %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("\n🔥 Ataque bem-sucedido!\n");

        strcpy(defensor->cor, atacante->cor);

        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;

    } else {
        printf("\n🛡 Defesa bem-sucedida! Atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

/* --------------------------------------------------------------------- */
/* --------------------- MISSÕES: SORTEIO ------------------------------ */

void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

/* --------------------------------------------------------------------- */
/* ----------------------- VERIFICAR MISSÃO ---------------------------- */

int verificarMissao(char *missao, Territorio *mapa, int qtd) {

    /* MISSÃO 1 – Conquistar 3 territórios */
    if (strstr(missao, "3 territorios") != NULL) {
        int contador = 0;

        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                contador++;
        }

        return contador >= 3;
    }

    /* MISSÃO 2 – Eliminar cor vermelha */
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0)
                return 0;
        }
        return 1;
    }

    /* MISSÃO 3 – Ter mais de 20 tropas */
    if (strstr(missao, "20 tropas") != NULL) {
        int total = 0;

        for (int i = 0; i < qtd; i++)
            total += mapa[i].tropas;

        return total >= 20;
    }

    /* MISSÃO 4 – Dominar território azul */
    if (strstr(missao, "territorio azul") != NULL) {
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                return 1;
        }
        return 0;
    }

    /* MISSÃO 5 – Reduzir tropa inimiga para 0 */
    if (strstr(missao, "0 tropas") != NULL) {
        for (int i = 0; i < qtd; i++) {
            if (mapa[i].tropas == 0)
                return 1;
        }
        return 0;
    }

    return 0;
}

/* --------------------------------------------------------------------- */
/* --------------------- LIBERAR MEMÓRIA ------------------------------- */

void liberarMemoria(Territorio *mapa, char *missaoJog1, char *missaoJog2) {
    free(mapa);
    free(missaoJog1);
    free(missaoJog2);

    printf("\nMemória liberada com sucesso!\n");
}

/* --------------------------------------------------------------------- */
/* ------------------------------ MAIN --------------------------------- */

int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    Territorio *mapa = calloc(qtd, sizeof(Territorio));
    cadastrarTerritorios(mapa, qtd);

    /* ------------ MISSÕES ------------ */
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar todas as tropas da cor vermelha",
        "Ter mais de 20 tropas somadas",
        "Dominar qualquer territorio azul",
        "Reduzir qualquer territorio inimigo a 0 tropas"
    };

    int totalMissoes = 5;

    /* Missões atribuídas dinamicamente */
    char *missaoJog1 = malloc(200);
    char *missaoJog2 = malloc(200);

    atribuirMissao(missaoJog1, missoes, totalMissoes);
    atribuirMissao(missaoJog2, missoes, totalMissoes);

    printf("\nMissão do Jogador 1: %s\n", missaoJog1);
    printf("Missão do Jogador 2: %s\n\n", missaoJog2);

    /* Loop principal */
    int op;
    do {
        exibirMapa(mapa, qtd);

        printf("\n1 - Atacar\n0 - Sair\nEscolha: ");
        scanf("%d", &op);

        if (op == 1) {
            int a, d;
            printf("Atacante: ");
            scanf("%d", &a);
            printf("Defensor: ");
            scanf("%d", &d);

            atacar(&mapa[a], &mapa[d]);

            /* Verifica Missões */
            if (verificarMissao(missaoJog1, mapa, qtd)) {
                printf("\n🎉 Jogador 1 completou sua missão e venceu!\n");
                break;
            }

            if (verificarMissao(missaoJog2, mapa, qtd)) {
                printf("\n🎉 Jogador 2 completou sua missão e venceu!\n");
                break;
            }
        }

    } while (op != 0);

    liberarMemoria(mapa, missaoJog1, missaoJog2);

    return 0;
}
