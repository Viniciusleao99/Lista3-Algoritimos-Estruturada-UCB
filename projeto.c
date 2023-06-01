#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRICAO 100
#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50
#define MIN_FABRICANTES 2
#define MIN_PRODUTOS 5

struct Fabricante {
    char nome[MAX_DESCRICAO]; // Estrutura que representa um fabricante com o campo 'nome'
};

struct Produto {
    char descricao[MAX_DESCRICAO]; // Estrutura que representa um produto com campos como 'descricao', 'peso', 'valorCompra', 'valorVenda', entre outros
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    int fabricanteIndex; // Índice do fabricante ao qual o produto está associado
};

void calcularLucro(struct Produto *produto) {
    produto->valorLucro = produto->valorVenda - produto->valorCompra; // Calcula o valor do lucro subtraindo o valor de venda do valor de compra
    produto->percentualLucro = (produto->valorLucro / produto->valorCompra) * 100; // Calcula o percentual de lucro em relação ao valor de compra
}

int validarQuantidade(int min, int max, char* tipo) {
    int quantidade;
    printf("Informe a quantidade de %s (%d a %d): ", tipo, min, max); // Solicita ao usuário a quantidade de um determinado tipo (fabricantes ou produtos) dentro de um intervalo mínimo e máximo
    scanf("%d", &quantidade);
    while (quantidade < min || quantidade > max) { // Valida se a quantidade fornecida está dentro do intervalo permitido
        printf("Quantidade invalida. Informe novamente a quantidade de %s (%d a %d): ", tipo, min, max); // Solicita novamente ao usuário uma quantidade válida
        scanf("%d", &quantidade);
    }
    return quantidade; // Retorna a quantidade válida fornecida pelo usuário
}

void cadastrarFabricantes(struct Fabricante fabricantes[], int *numFabricantes) {
    int quantidade = validarQuantidade(MIN_FABRICANTES, MAX_FABRICANTES, "fabricantes"); // Solicita ao usuário a quantidade de fabricantes dentro de um intervalo mínimo e máximo
    printf("-------- Cadastro de Fabricantes --------\n");
    for (int i = 0; i < quantidade; i++) { // Loop para cadastrar os fabricantes
        struct Fabricante novoFabricante;
        printf("Fabricante %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", novoFabricante.nome); // Lê o nome do fabricante fornecido pelo usuário
        fabricantes[i] = novoFabricante; // Armazena o novo fabricante no array de fabricantes
        (*numFabricantes)++; // Incrementa o contador de fabricantes
        printf("\n");
    }
}

void cadastrarProdutos(struct Produto produtos[], int numFabricantes, int *numProdutos) {
    int quantidade = validarQuantidade(MIN_PRODUTOS, MAX_PRODUTOS, "produtos"); // Solicita ao usuário a quantidade de produtos dentro de um intervalo mínimo e máximo
    printf("-------- Cadastro de Produtos --------\n");
    for (int i = 0; i < quantidade; i++) { // Loop para cadastrar os produtos
        struct Produto novoProduto;
        printf("Produto %d:\n", i + 1);
        printf("Descricao: ");
        scanf("%s", novoProduto.descricao); // Lê a descrição do produto fornecida pelo usuário
        printf("Peso: ");
        scanf("%f", &novoProduto.peso); // Lê o peso do produto fornecido pelo usuário
        printf("Valor de Compra: ");
        scanf("%f", &novoProduto.valorCompra); // Lê o valor de compra do produto fornecido pelo usuário
        printf("Valor de Venda: ");
        scanf("%f", &novoProduto.valorVenda); // Lê o valor de venda do produto fornecido pelo usuário
        printf("Fabricante Index (1 a %d): ", numFabricantes);
        scanf("%d", &novoProduto.fabricanteIndex); // Lê o índice do fabricante ao qual o produto está associado
        calcularLucro(&novoProduto); // Calcula o lucro e o percentual de lucro do produto
        produtos[i] = novoProduto; // Armazena o novo produto no array de produtos
        (*numProdutos)++; // Incrementa o contador de produtos
        printf("\n");
    }
}

void exibirFabricantes(struct Fabricante fabricantes[], int numFabricantes) {
    printf("------ Fabricantes Cadastrados ------\n");
    for (int i = 0; i < numFabricantes; i++) { // Loop para exibir os fabricantes cadastrados
        printf("Fabricante %d:\n", i + 1);
        printf("Nome: %s\n\n", fabricantes[i].nome); // Exibe o nome do fabricante
    }
}

void exibirProdutos(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    printf("------ Produtos Cadastrados ------\n");
    for (int i = 0; i < numProdutos; i++) { // Loop para exibir os produtos cadastrados
        printf("Produto %d:\n", i + 1);
        printf("Descricao: %s\n", produtos[i].descricao); // Exibe a descrição do produto
        printf("Peso: %.2f\n", produtos[i].peso); // Exibe o peso do produto
        printf("Valor de Compra: %.2f\n", produtos[i].valorCompra); // Exibe o valor de compra do produto
        printf("Valor de Venda: %.2f\n", produtos[i].valorVenda); // Exibe o valor de venda do produto
        printf("Valor do Lucro: %.2f\n", produtos[i].valorLucro); // Exibe o valor do lucro do produto
        printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro); // Exibe o percentual de lucro do produto
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            printf("Fabricante: %s\n", fabricantes[fabricanteIndex - 1].nome); // Exibe o nome do fabricante associado ao produto
        } else {
            printf("Fabricante: N/A\n"); // Caso o índice do fabricante seja inválido, exibe "N/A" (não aplicável)
        }
        printf("\n");
    }
}

int main() {
    struct Fabricante fabricantes[MAX_FABRICANTES];
    struct Produto produtos[MAX_PRODUTOS];
    int numFabricantes = 0;
    int numProdutos = 0;

    cadastrarFabricantes(fabricantes, &numFabricantes); // Função para cadastrar os fabricantes
    cadastrarProdutos(produtos, numFabricantes, &numProdutos); // Função para cadastrar os produtos
    exibirProdutos(produtos, numProdutos, fabricantes, numFabricantes); // Função para exibir os produtos cadastrados

    return 0;
}
