// Como Compilar o programa: 
// Abra o terminal e digite: cd (endereço de onde a pasta do programa está salva no computador) e pressione enter, 
// a seguir digite: gcc main.c conta.c -o banco e pressione enter,
// então digite: .\banco e pressione enter, pronto, o programa estará rodando.


#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 2
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_AGENCIA 10
#define TAM_TELEFONE 20
#define ATIVA 1
#define ENCERRADA 0

typedef struct {
    int numero;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status;
} Conta;

// PROTÓTIPOS

int encontrar_conta_por_numero(const Conta contas[], int qtd, int numero);
int encontrar_conta_por_cpf(const Conta contas[], int qtd, const char* cpf);
int abrir_conta(Conta contas[], int* qtd, int proximo_numero,
                const char* nome, const char* cpf,
                const char* agencia, const char* telefone);
int depositar(Conta contas[], int qtd, int numero, double valor);
int sacar(Conta contas[], int qtd, int numero, double valor);
int transferir(Conta contas[], int qtd, int origem, int destino, double valor);
int atualizar_contato(Conta contas[], int qtd, int numero,
                      const char* novo_telefone, const char* nova_agencia);
int encerrar_conta(Conta contas[], int qtd, int numero);
void listar_contas(const Conta contas[], int qtd, int filtro_status);
void mostrar_dados(const Conta* c);


// MAIN 


int main() {

    Conta contas[MAX_CONTAS];
    int qtd = 0;                 // quantidade de contas cadastradas
    int proximo_numero = 1;      // gerador de números de conta
    int op;

    do {
        printf("\n===== MENU DO SISTEMA BANCARIO =====\n");
        printf("1. Abrir conta\n");
        printf("2. Depositar\n");
        printf("3. Sacar\n");
        printf("4. Transferir\n");
        printf("5. Consultar saldo e dados\n");
        printf("6. Atualizar telefone e agencia\n");
        printf("7. Listar contas\n");
        printf("8. Encerrar conta\n");
        printf("9. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar(); // limpar buffer

        if (op == 1) {
            char nome[TAM_NOME], cpf[TAM_CPF], agencia[TAM_AGENCIA], telefone[TAM_TELEFONE];

            printf("Nome: ");
            fgets(nome, TAM_NOME, stdin); nome[strcspn(nome, "\n")] = 0;

            printf("CPF: ");
            fgets(cpf, TAM_CPF, stdin); cpf[strcspn(cpf, "\n")] = 0;

            printf("Agencia: ");
            fgets(agencia, TAM_AGENCIA, stdin); agencia[strcspn(agencia, "\n")] = 0;

            printf("Telefone: ");
            fgets(telefone, TAM_TELEFONE, stdin); telefone[strcspn(telefone, "\n")] = 0;

            if (abrir_conta(contas, &qtd, proximo_numero, nome, cpf, agencia, telefone)) {
                printf("Conta aberta com sucesso! Numero da conta: %d\n", proximo_numero);
                proximo_numero++;
            } else {
                printf("ERRO ao abrir conta.\n");
            }

        } else if (op == 2) { // Depositar
            int numero;
            double valor;

            printf("Numero da conta: ");
            scanf("%d", &numero);

            printf("Valor do depósito: ");
            scanf("%lf", &valor);

            if (depositar(contas, qtd, numero, valor))
                printf("Deposito realizado.\n");
            else
                printf("ERRO ao depositar.\n");

        } else if (op == 3) { // Sacar
            int numero;
            double valor;

            printf("Numero da conta: ");
            scanf("%d", &numero);

            printf("Valor do saque: ");
            scanf("%lf", &valor);

            if (sacar(contas, qtd, numero, valor))
                printf("Saque realizado.\n");
            else
                printf("ERRO ao sacar.\n");

        } else if (op == 4) { // Transferir
            int origem, destino;
            double valor;

            printf("Conta de origem: ");
            scanf("%d", &origem);

            printf("Conta de destino: ");
            scanf("%d", &destino);

            printf("Valor da transferencia: ");
            scanf("%lf", &valor);

            if (transferir(contas, qtd, origem, destino, valor))
                printf("Transferencia realizada.\n");
            else
                printf("ERRO na transferencia.\n");

        } else if (op == 5) { // Consultar saldo e dados
            int escolha;
            printf("Buscar por: 1) Numero da conta  2) CPF\n");
            scanf("%d", &escolha);
            getchar();

            if (escolha == 1) {
                int numero;
                printf("Numero da conta: ");
                scanf("%d", &numero);
                int idx = encontrar_conta_por_numero(contas, qtd, numero);
                if (idx >= 0)
                    mostrar_dados(&contas[idx]);
                else
                    printf("Conta nao encontrada.\n");

            } else {
                char cpf[TAM_CPF];
                printf("CPF: ");
                fgets(cpf, TAM_CPF, stdin); cpf[strcspn(cpf, "\n")] = 0;

                int idx = encontrar_conta_por_cpf(contas, qtd, cpf);
                if (idx >= 0)
                    mostrar_dados(&contas[idx]);
                else
                    printf("Conta nao encontrada.\n");
            }

        } else if (op == 6) { // Atualizar contato
            int numero;
            char telefone[TAM_TELEFONE], agencia[TAM_AGENCIA];

            printf("Numero da conta: ");
            scanf("%d", &numero);
            getchar();

            printf("Novo telefone: ");
            fgets(telefone, TAM_TELEFONE, stdin); telefone[strcspn(telefone, "\n")] = 0;

            printf("Nova agencia: ");
            fgets(agencia, TAM_AGENCIA, stdin); agencia[strcspn(agencia, "\n")] = 0;

            if (atualizar_contato(contas, qtd, numero, telefone, agencia))
                printf("Dados atualizados.\n");
            else
                printf("ERRO ao atualizar dados.\n");

        } else if (op == 7) { // Listar contas
            int filtro;
            printf("Filtro: 1) Ativas  0) Encerradas  3) Todas\n");
            scanf("%d", &filtro);
            listar_contas(contas, qtd, filtro);

        } else if (op == 8) { // Encerrar conta
            int numero;
            printf("Numero da conta: ");
            scanf("%d", &numero);

            if (encerrar_conta(contas, qtd, numero))
                printf("Conta encerrada.\n");
            else
                printf("ERRO ao encerrar conta.\n");
        }

    } while (op != 9);

    printf("Sistema encerrado.\n");
    return 0;
}
