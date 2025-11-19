#include <stdio.h>
#include <string.h>

/*
    Definição da struct Territorio:
    Agrupa dados relacionados a um território:
    - nome: nome do território (string)
    - cor: cor do exército no território (string)
    - tropas: quantidade de tropas (inteiro)
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Vetor capaz de armazenar 5 territórios
    Territorio territorios[5];

    int i; // índice para os laços

    printf("=== Cadastro de Territorios ===\n\n");

    /*
        Laço de entrada de dados:
        - Percorre as 5 posições do vetor
        - Em cada iteração, solicita ao usuário
          o nome, a cor do exército e o número de tropas
    */
    for (i = 0; i < 5; i++) {
        printf(">>> Cadastro do territorio %d\n", i + 1);

        // Limpa o buffer de entrada antes de ler strings com espaços
        
        fflush(stdin); 

        printf("Digite o nome do territorio: ");
        // Lê uma linha com até 29 caracteres (deixa 1 para o '\0')
        scanf(" %29[^\n]", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        // Aqui usamos %9s, assumindo que a cor não terá espaços
        scanf(" %9s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    /*
        Exibição dos dados:
        - Após o cadastro, percorremos o vetor novamente
        - Exibimos os dados de cada território em uma
          formatação clara para o usuário
    */
    printf("\n=== Territorios cadastrados ===\n\n");
    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome : %s\n", territorios[i].nome);
        printf("  Cor  : %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
