#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Struct Territorio:
    Armazena nome, cor do exército e quantidade de tropas.
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
    Função: cadastrarTerritorios
    Objetivo: preencher o vetor dinâmico de territórios.
*/
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Cadastro de Territórios ===\n");

    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);

        fflush(stdin);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/*
    Função: exibirTerritorios
    Objetivo: mostrar todos os territórios cadastrados.
*/
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] %s\n", i, mapa[i].nome);
        printf("    Cor: %s\n", mapa[i].cor);
        printf("    Tropas: %d\n", mapa[i].tropas);
    }
}

/*
    Função: atacar
    Objetivo: simular ataque usando números aleatórios (dados)
*/
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Você não pode atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n❌ O território atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    printf("\n🎲 Rolando dados...\n");

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado defensor  (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n🔥 O atacante venceu o combate!\n");

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;

        printf("⚔ %s conquistou %s!\n", atacante->nome, defensor->nome);

    } else {
        printf("\n🛡 O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
        printf("O atacante perdeu 1 tropa.\n");
    }
}

/*
    Função: liberarMemoria
    Objetivo: liberar memória alocada dinamicamente
*/
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

int main() {
    srand(time(NULL)); // garante aleatoriedade nos dados

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica do vetor de territórios
    Territorio *mapa = calloc(qtd, sizeof(Territorio));

    cadastrarTerritorios(mapa, qtd);

    int op;
    do {
        exibirTerritorios(mapa, qtd);

        printf("\n=== MENU ===\n");
        printf("1 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op == 1) {
            int a, d;

            printf("\nDigite o número do território ATACANTE: ");
            scanf("%d", &a);

            printf("Digite o número do território DEFENSOR: ");
            scanf("%d", &d);

            if (a >= 0 && a < qtd && d >= 0 && d < qtd) {
                atacar(&mapa[a], &mapa[d]);
            } else {
                printf("\n❌ Território inválido!\n");
            }
        }

    } while (op != 0);

    liberarMemoria(mapa);

    return 0;
}
