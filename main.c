#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRICAO 100
#define MAX_SITE 100
#define MAX_TELEFONE 20
#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50
#define MIN_FABRICANTES 2
#define MIN_PRODUTOS 5

struct Fabricante {
    char nome[MAX_DESCRICAO];
    char site[MAX_SITE];
    char telefone[MAX_TELEFONE];
    char estado
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
        printf("Quantidade inválida. Informe novamente a quantidade de %s (%d a %d): ", tipo, min, max);
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
        scanf("%[^\n]%s", novoFabricante.nome);
        printf("Site: ");
        scanf("%[^\n]%s", novoFabricante.site);
        printf("Telefone: ");
        scanf("%[^\n]%s", novoFabricante.telefone);
        fabricantes[*numFabricantes] = novoFabricante;
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
        scanf("%[^\n]%s", novoProduto.descricao);
        printf("Peso: ");
        scanf("%f", &novoProduto.peso);
        printf("Valor de Compra: ");
        scanf("%f", &novoProduto.valorCompra);
        printf("Valor de Venda: ");
        scanf("%f", &novoProduto.valorVenda);
        printf("Fabricante Index (1 a %d): ", numFabricantes);
        scanf("%d", &novoProduto.fabricanteIndex);
        calcularLucro(&novoProduto);
        produtos[*numProdutos] = novoProduto;
        (*numProdutos)++;
        printf("\n");
    }
}

void exibirFabricantes(struct Fabricante fabricantes[], int numFabricantes) {
    printf("------ Fabricantes Cadastrados ------\n");
    for (int i = 0; i < numFabricantes; i++) {
        printf("Fabricante %d:\n", i + 1);
        printf("Nome: %s\n", fabricantes[i].nome);
        printf("Site: %s\n", fabricantes[i].site);
        printf("Telefone: %s\n", fabricantes[i].telefone);
        printf("\n");
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

void listarMarcas(struct Fabricante fabricantes[], int numFabricantes) {
    printf("------ Marcas Cadastradas ------\n");
    for (int i = 0; i < numFabricantes; i++) {
        printf("%s\n", fabricantes[i].nome);
    }
    printf("\n");
}

void listarProdutos(struct Produto produtos[], int numProdutos) {
    printf("------ Produtos Cadastrados ------\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("%s\n", produtos[i].descricao);
    }
    printf("\n");
}

void listarProdutosEstado(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    char estado[3];
    printf("Informe o estado (UF) para listar os produtos: ");
    scanf("%[^\n]%s", estado);
    printf("------ Produtos do Estado %s ------\n", estado);
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            if (strcmp(fabricantes[fabricanteIndex - 1].estado, estado) == 0) {
                printf("Produto: %s\n", produtos[i].descricao);
                encontrou = 1;
            }
        }
    }
    if (!encontrou) {
        printf("Nenhum produto encontrado para o estado %s.\n", estado);
    }
    printf("\n");
}

void listarProdutosMarca(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    char marca[MAX_DESCRICAO];
    printf("Informe a marca para listar os produtos: ");
    scanf("%[^\n]%s", marca);
    printf("------ Produtos da Marca %s ------\n", marca);
    int encontrou = 0;
    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            if (strcmp(fabricantes[fabricanteIndex - 1].nome, marca) == 0) {
                printf("Produto: %s\n", produtos[i].descricao);
                encontrou = 1;
            }
        }
    }
    if (!encontrou) {
        printf("Nenhum produto encontrado para a marca %s.\n", marca);
    }
    printf("\n");
}

void estadoProdutoMaisCaro(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    float maiorValor = 0.0;
    char estados[MAX_FABRICANTES][3];
    int numEstados = 0;

    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            float valorVenda = produtos[i].valorVenda;
            if (valorVenda > maiorValor) {
                maiorValor = valorVenda;
                strcpy(estados[0], fabricantes[fabricanteIndex - 1].estado);
                numEstados = 1;
            } else if (valorVenda == maiorValor) {
                strcpy(estados[numEstados], fabricantes[fabricanteIndex - 1].estado);
                numEstados++;
            }
        }
    }

    printf("Estado(s) onde está registrado o produto mais caro:\n");
    for (int i = 0; i < numEstados; i++) {
        printf("%s\n", estados[i]);
    }
    printf("\n");
}

void fabricanteProdutoMaisBarato(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    float menorValor = produtos[0].valorVenda;
    int fabricantesIndices[MAX_FABRICANTES];
    int numFabricantesIndices = 0;

    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            float valorVenda = produtos[i].valorVenda;
            if (valorVenda < menorValor) {
                menorValor = valorVenda;
                fabricantesIndices[0] = fabricanteIndex;
                numFabricantesIndices = 1;
            } else if (valorVenda == menorValor) {
                fabricantesIndices[numFabricantesIndices] = fabricanteIndex;
                numFabricantesIndices++;
            }
        }
    }

    printf("Fabricante(s) onde está registrado o produto mais barato:\n");
    for (int i = 0; i < numFabricantesIndices; i++) {
        printf("%s\n", fabricantes[fabricantesIndices[i] - 1].nome);
    }
    printf("\n");
}

void listarProdutosOrdenadosValor(struct Produto produtos[], int numProdutos) {
    struct Produto produtosOrdenados[MAX_PRODUTOS];
    memcpy(produtosOrdenados, produtos, sizeof(struct Produto) * numProdutos);

    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            if (produtosOrdenados[j].valorVenda > produtosOrdenados[j + 1].valorVenda) {
                struct Produto temp = produtosOrdenados[j];
                produtosOrdenados[j] = produtosOrdenados[j + 1];
                produtosOrdenados[j + 1] = temp;
            }
        }
    }

    printf("------ Produtos Ordenados por Valor de Venda ------\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Produto: %s\n", produtosOrdenados[i].descricao);
        printf("Valor de Venda: %.2f\n", produtosOrdenados[i].valorVenda);
        printf("\n");
    }
}

int main() {
    struct Fabricante fabricantes[MAX_FABRICANTES];
    struct Produto produtos[MAX_PRODUTOS];
    int numFabricantes = 0;
    int numProdutos = 0;

    int opcao;
    do {
        printf("------ Menu de Opcoes ------\n");
        printf("1. Cadastrar Fabricantes\n");
        printf("2. Cadastrar Produtos\n");
        printf("3. Exibir Fabricantes Cadastrados\n");
        printf("4. Exibir Produtos Cadastrados\n");
        printf("5. Listar Marcas\n");
        printf("6. Listar Produtos\n");
        printf("7. Listar Produtos por Estado\n");
        printf("8. Listar Produtos por Marca\n");
        printf("9. Estado do Produto Mais Caro\n");
        printf("10. Fabricante do Produto Mais Barato\n");
        printf("11. Listar Produtos Ordenados por Valor de Venda\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFabricantes(fabricantes, &numFabricantes);
                break;
            case 2:
                cadastrarProdutos(produtos, numFabricantes, &numProdutos);
                break;
            case 3:
                exibirFabricantes(fabricantes, numFabricantes);
                break;
            case 4:
                exibirProdutos(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 5:
                listarMarcas(fabricantes, numFabricantes);
                break;
            case 6:
                listarProdutos(produtos, numProdutos);
                break;
            case 7:
                listarProdutosEstado(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 8:
                listarProdutosMarca(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 9:
                estadoProdutoMaisCaro(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 10:
                fabricanteProdutoMaisBarato(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 11:
                listarProdutosOrdenadosValor(produtos, numProdutos);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Por favor, escolha novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
