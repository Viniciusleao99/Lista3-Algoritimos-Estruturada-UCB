#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRICAO 100
#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50
#define MIN_FABRICANTES 2
#define MIN_PRODUTOS 5

struct Fabricante {
    char nome[MAX_DESCRICAO];
};

struct Produto {
    char descricao[MAX_DESCRICAO];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    int fabricanteIndex;
};

void calcularLucro(struct Produto *produto) {
    produto->valorLucro = produto->valorVenda - produto->valorCompra;
    produto->percentualLucro = (produto->valorLucro / produto->valorCompra) * 100;
}

int validarQuantidade(int min, int max, char* tipo) {
    int quantidade;
    printf("Informe a quantidade de %s (%d a %d): ", tipo, min, max);
    scanf("%d", &quantidade);
    while (quantidade < min || quantidade > max) {
        printf("Quantidade invalida. Informe novamente a quantidade de %s (%d a %d): ", tipo, min, max);
        scanf("%d", &quantidade);
    }
    return quantidade;
}

void cadastrarFabricantes(struct Fabricante fabricantes[], int *numFabricantes) {
    int quantidade = validarQuantidade(MIN_FABRICANTES, MAX_FABRICANTES, "fabricantes");
    printf("-------- Cadastro de Fabricantes --------\n");
    for (int i = 0; i < quantidade; i++) {
        struct Fabricante novoFabricante;
        printf("Fabricante %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", novoFabricante.nome);
        fabricantes[i] = novoFabricante;
        (*numFabricantes)++;
        printf("\n");
    }
}

void cadastrarProdutos(struct Produto produtos[], int numFabricantes, int *numProdutos) {
    int quantidade = validarQuantidade(MIN_PRODUTOS, MAX_PRODUTOS, "produtos");
    printf("-------- Cadastro de Produtos --------\n");
    for (int i = 0; i < quantidade; i++) {
        struct Produto novoProduto;
        printf("Produto %d:\n", i + 1);
        printf("Descricao: ");
        scanf("%s", novoProduto.descricao);
        printf("Peso: ");
        scanf("%f", &novoProduto.peso);
        printf("Valor de Compra: ");
        scanf("%f", &novoProduto.valorCompra);
        printf("Valor de Venda: ");
        scanf("%f", &novoProduto.valorVenda);
        printf("Fabricante Index (1 a %d): ", numFabricantes);
        scanf("%d", &novoProduto.fabricanteIndex);
        calcularLucro(&novoProduto);
        produtos[i] = novoProduto;
        (*numProdutos)++;
        printf("\n");
    }
}

void exibirFabricantes(struct Fabricante fabricantes[], int numFabricantes) {
    printf("------ Fabricantes Cadastrados ------\n");
    for (int i = 0; i < numFabricantes; i++) {
        printf("Fabricante %d:\n", i + 1);
        printf("Nome: %s\n\n", fabricantes[i].nome);
    }
}

void exibirProdutos(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    printf("------ Produtos Cadastrados ------\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Produto %d:\n", i + 1);
        printf("Descricao: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de Compra: %.2f\n", produtos[i].valorCompra);
        printf("Valor de Venda: %.2f\n", produtos[i].valorVenda);
        printf("Valor do Lucro: %.2f\n", produtos[i].valorLucro);
        printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro);
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            printf("Fabricante: %s\n", fabricantes[fabricanteIndex - 1].nome);
        } else {
            printf("Fabricante: N/A\n");
        }
        printf("\n");
    }
}

int main() {
    struct Fabricante fabricantes[MAX_FABRICANTES];
    struct Produto produtos[MAX_PRODUTOS];
    int numFabricantes = 0;
    int numProdutos = 0;

    cadastrarFabricantes(fabricantes, &numFabricantes);
    cadastrarProdutos(produtos, numFabricantes, &numProdutos);
    exibirProdutos(produtos, numProdutos, fabricantes, numFabricantes);

    return 0;
}


