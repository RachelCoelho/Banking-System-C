#include <stdio.h>
#include <string.h>
#include "conta.h"

//  FUNÇÕES DE BUSCA

int encontrar_conta_por_numero(const Conta contas[], int qtd, int numero) {
    for (int i = 0; i < qtd; i++) {
        if (contas[i].numero == numero) {
            return i;
        }
    }
    return -1;
}

int encontrar_conta_por_cpf(const Conta contas[], int qtd, const char* cpf) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(contas[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}


//  ABRIR CONTA

int abrir_conta(Conta contas[], int* qtd, int proximo_numero,
                const char* nome, const char* cpf,
                const char* agencia, const char* telefone)
{
    if (*qtd >= MAX_CONTAS) {
        printf("ERRO: limite maximo de contas atingido.\n");
        return 0;
    }

    // Verificar CPF duplicado (somente contas ativas)

    for (int i = 0; i < *qtd; i++) {
        if (contas[i].status == ATIVA && strcmp(contas[i].cpf, cpf) == 0) {
            printf("ERRO: ja existe conta ativa com esse CPF.\n");
            return 0;
        }
    }

    Conta nova;
    nova.numero = proximo_numero;
    strcpy(nova.nome, nome);
    strcpy(nova.cpf, cpf);
    strcpy(nova.agencia, agencia);
    strcpy(nova.telefone, telefone);
    nova.saldo = 0.0;
    nova.status = ATIVA;

    contas[*qtd] = nova;
    (*qtd)++;

    printf("Conta aberta com sucesso! Numero: %d\n", nova.numero);
    return 1;
}

//  DEPOSITAR

int depositar(Conta contas[], int qtd, int numero, double valor) {
    int idx = encontrar_conta_por_numero(contas, qtd, numero);

    if (idx < 0) { printf("Conta nao encontrada.\n"); return 0; }
    if (contas[idx].status == ENCERRADA) {
        printf("Conta encerrada. Operacao nao permitida.\n");
        return 0;
    }
    if (valor <= 0) { printf("Valor invalido.\n"); return 0; }

    contas[idx].saldo += valor;
    printf("Deposito realizado.\n");
    return 1;
}

//  SACAR

int sacar(Conta contas[], int qtd, int numero, double valor) {
    int idx = encontrar_conta_por_numero(contas, qtd, numero);

    if (idx < 0) { printf("Conta nao encontrada.\n"); return 0; }
    if (contas[idx].status == ENCERRADA) {
        printf("Conta encerrada. Operacao nao permitida.\n");
        return 0;
    }
    if (valor <= 0) { printf("Valor invalido.\n"); return 0; }
    if (valor > contas[idx].saldo) {
        printf("Saldo insuficiente.\n");
        return 0;
    }

    contas[idx].saldo -= valor;
    printf("Saque realizado.\n");
    return 1;
}

//  TRANSFERIR

int transferir(Conta contas[], int qtd, int origem, int destino, double valor) {
    int o = encontrar_conta_por_numero(contas, qtd, origem);
    int d = encontrar_conta_por_numero(contas, qtd, destino);

    if (o < 0 || d < 0) { printf("Conta origem/destino invalida.\n"); return 0; }
    if (contas[o].status == ENCERRADA || contas[d].status == ENCERRADA) {
        printf("Uma das contas esta encerrada.\n");
        return 0;
    }
    if (valor <= 0) { printf("Valor invalido.\n"); return 0; }
    if (valor > contas[o].saldo) {
        printf("Saldo insuficiente.\n");
        return 0;
    }

    contas[o].saldo -= valor;
    contas[d].saldo += valor;

    printf("Transferencia realizada.\n");
    return 1;
}

//  CONSULTAR DADOS

void mostrar_dados(const Conta* c) {
    printf("\n--- Dados da Conta ---\n");
    printf("Numero: %d\n", c->numero);
    printf("Nome: %s\n", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("Agencia: %s\n", c->agencia);
    printf("Telefone: %s\n", c->telefone);
    printf("Status: %s\n", c->status == ATIVA ? "Ativa" : "Encerrada");
    printf("Saldo: %.2f\n", c->saldo);
}

//  ATUALIZAR CONTATO

int atualizar_contato(Conta contas[], int qtd, int numero,
                      const char* novoTelefone, const char* novaAgencia)
{
    int idx = encontrar_conta_por_numero(contas, qtd, numero);

    if (idx < 0) { printf("Conta nao encontrada.\n"); return 0; }
    if (contas[idx].status == ENCERRADA) {
        printf("Conta encerrada. Nao e possivel alterar.\n");
        return 0;
    }

    strcpy(contas[idx].telefone, novoTelefone);
    strcpy(contas[idx].agencia, novaAgencia);

    printf("Contato atualizado.\n");
    return 1;
}

//  LISTAR CONTAS

void listar_contas(const Conta contas[], int qtd, int filtro_status) {
    printf("\n === LISTAGEM DE CONTAS ===\n");

    for (int i = 0; i < qtd; i++) {
        if (filtro_status == ATIVA && contas[i].status != ATIVA) continue;
        if (filtro_status == ENCERRADA && contas[i].status != ENCERRADA) continue;

        mostrar_dados(&contas[i]);
    }
}

//  ENCERRAR CONTA

int encerrar_conta(Conta contas[], int qtd, int numero) {
    int idx = encontrar_conta_por_numero(contas, qtd, numero);

    if (idx < 0) {
        printf("Conta nao encontrada.\n");
        return 0;
    }
    if (contas[idx].status == ENCERRADA) {
        printf("Conta ja esta encerrada.\n");
        return 0;
    }
    if (contas[idx].saldo != 0) {
        printf("Saldo precisa ser zero para encerrar.\n");
        return 0;
    }

    contas[idx].status = ENCERRADA;
    printf("Conta encerrada com sucesso.\n");
    return 1;
}
