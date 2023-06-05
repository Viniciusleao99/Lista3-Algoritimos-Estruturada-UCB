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
    char site[MAX_DESCRICAO];
    char telefone[MAX_DESCRICAO];
    char UF[MAX_DESCRICAO];
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

int validarQuantidade(int min, int max, const char* tipo) {
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
        scanf("%s", novoFabricante.nome);
        printf("Site: ");
        scanf("%s", novoFabricante.site);
        printf("Telefone: ");
        scanf("%s", novoFabricante.telefone);
        printf("UF: ");
        scanf("%s", novoFabricante.UF);
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

void listarMarcas(const struct Fabricante fabricantes[], int numFabricantes) {
    printf("------ Marcas Cadastradas ------\n");
    for (int i = 0; i < numFabricantes; i++) {
        printf("Marca %d:\n", i + 1);
        printf("Nome: %s\n", fabricantes[i].nome);
        printf("Site: %s\n", fabricantes[i].site);
        printf("Telefone: %s\n", fabricantes[i].telefone);
        printf("UF: %s\n\n", fabricantes[i].UF);
    }
}

void listarProdutos(const struct Produto produtos[], int numProdutos, const struct Fabricante fabricantes[], int numFabricantes) {
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

void listarProdutosEstado(const struct Produto produtos[], int numProdutos, const struct Fabricante fabricantes[], int numFabricantes, const char* estado) {
    printf("------ Produtos do Estado %s ------\n", estado);
    int encontrado = 0;
    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            if (strcmp(fabricantes[fabricanteIndex - 1].UF, estado) == 0) {
                printf("Produto %d:\n", i + 1);
                printf("Descricao: %s\n", produtos[i].descricao);
                printf("Peso: %.2f\n", produtos[i].peso);
                printf("Valor de Compra: %.2f\n", produtos[i].valorCompra);
                printf("Valor de Venda: %.2f\n", produtos[i].valorVenda);
                printf("Valor do Lucro: %.2f\n", produtos[i].valorLucro);
                printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro);
                printf("Fabricante: %s\n", fabricantes[fabricanteIndex - 1].nome);
                printf("\n");
                encontrado = 1;
            }
        }
    }
    if (!encontrado) {
        printf("Nenhum produto encontrado para o estado %s.\n", estado);
    }
}

void listarProdutosMarca(const struct Produto produtos[], int numProdutos, const struct Fabricante fabricantes[], int numFabricantes, const char* marca) {
    printf("------ Produtos da Marca %s ------\n", marca);
    int encontrado = 0;
    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            if (strcmp(fabricantes[fabricanteIndex - 1].nome, marca) == 0) {
                printf("Produto %d:\n", i + 1);
                printf("Descricao: %s\n", produtos[i].descricao);
                printf("Peso: %.2f\n", produtos[i].peso);
                printf("Valor de Compra: %.2f\n", produtos[i].valorCompra);
                printf("Valor de Venda: %.2f\n", produtos[i].valorVenda);
                printf("Valor do Lucro: %.2f\n", produtos[i].valorLucro);
                printf("Percentual do Lucro: %.2f%%\n", produtos[i].percentualLucro);
                printf("Fabricante: %s\n", fabricantes[fabricanteIndex - 1].nome);
                printf("\n");
                encontrado = 1;
            }
        }
    }
    if (!encontrado) {
        printf("Nenhum produto encontrado para a marca %s.\n", marca);
    }
}

void estadoProdutoMaisCaro(const struct Produto produtos[], int numProdutos, const struct Fabricante fabricantes[], int numFabricantes) {
    float valorMaximo = -1;
    char estados[MAX_PRODUTOS][MAX_DESCRICAO];
    int numEstados = 0;

    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            if (produtos[i].valorVenda > valorMaximo) {
                valorMaximo = produtos[i].valorVenda;
                numEstados = 0;
                strcpy(estados[numEstados], fabricantes[fabricanteIndex - 1].UF);
                numEstados++;
            } else if (produtos[i].valorVenda == valorMaximo) {
                int encontrado = 0;
                for (int j = 0; j < numEstados; j++) {
                    if (strcmp(estados[j], fabricantes[fabricanteIndex - 1].UF) == 0) {
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    strcpy(estados[numEstados], fabricantes[fabricanteIndex - 1].UF);
                    numEstados++;
                }
            }
        }
    }

    if (valorMaximo > -1) {
        printf("Estado(s) onde está registrado o produto mais caro:\n");
        for (int i = 0; i < numEstados; i++) {
            printf("%s\n", estados[i]);
        }
    } else {
        printf("Nenhum produto cadastrado.\n");
    }
}

void fabricantesProdutoMaisBarato(const struct Produto produtos[], int numProdutos, const struct Fabricante fabricantes[], int numFabricantes) {
    float valorMinimo = -1;
    char fabricantesBaratos[MAX_PRODUTOS][MAX_DESCRICAO];
    int numFabricantesBaratos = 0;

    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtos[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            if (valorMinimo == -1 || produtos[i].valorVenda < valorMinimo) {
                valorMinimo = produtos[i].valorVenda;
                numFabricantesBaratos = 0;
                strcpy(fabricantesBaratos[numFabricantesBaratos], fabricantes[fabricanteIndex - 1].nome);
                numFabricantesBaratos++;
            } else if (produtos[i].valorVenda == valorMinimo) {
                int encontrado = 0;
                for (int j = 0; j < numFabricantesBaratos; j++) {
                    if (strcmp(fabricantesBaratos[j], fabricantes[fabricanteIndex - 1].nome) == 0) {
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    strcpy(fabricantesBaratos[numFabricantesBaratos], fabricantes[fabricanteIndex - 1].nome);
                    numFabricantesBaratos++;
                }
            }
        }
    }

    if (valorMinimo > -1) {
        printf("Fabricante(s) onde está registrado o produto mais barato:\n");
        for (int i = 0; i < numFabricantesBaratos; i++) {
            printf("%s\n", fabricantesBaratos[i]);
        }
    } else {
        printf("Nenhum produto cadastrado.\n");
    }
}

int compararValor(const void *p1, const void *p2) {
    const struct Produto *produto1 = (const struct Produto *)p1;
    const struct Produto *produto2 = (const struct Produto *)p2;
    if (produto1->valorVenda < produto2->valorVenda) {
        return -1;
    } else if (produto1->valorVenda > produto2->valorVenda) {
        return 1;
    } else {
        return 0;
    }
}

void listarProdutosOrdemCrescenteValor(const struct Produto produtos[], int numProdutos, const struct Fabricante fabricantes[], int numFabricantes) {
    struct Produto produtosOrdenados[MAX_PRODUTOS];
    memcpy(produtosOrdenados, produtos, numProdutos * sizeof(struct Produto));
    qsort(produtosOrdenados, numProdutos, sizeof(struct Produto), compararValor);

    printf("------ Produtos em Ordem Crescente de Valor ------\n");
    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtosOrdenados[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            printf("Produto %d:\n", i + 1);
            printf("Descricao: %s\n", produtosOrdenados[i].descricao);
            printf("Peso: %.2f\n", produtosOrdenados[i].peso);
            printf("Valor de Compra: %.2f\n", produtosOrdenados[i].valorCompra);
            printf("Valor de Venda: %.2f\n", produtosOrdenados[i].valorVenda);
            printf("Valor do Lucro: %.2f\n", produtosOrdenados[i].valorLucro);
            printf("Percentual do Lucro: %.2f%%\n", produtosOrdenados[i].percentualLucro);
            printf("Fabricante: %s\n", fabricantes[fabricanteIndex - 1].nome);
            printf("\n");
        }
    }
}

int compararLucro(const void *p1, const void *p2) {
    const struct Produto *produto1 = (const struct Produto *)p1;
    const struct Produto *produto2 = (const struct Produto *)p2;
    if (produto1->valorLucro < produto2->valorLucro) {
        return -1;
    } else if (produto1->valorLucro > produto2->valorLucro) {
        return 1;
    } else {
        return 0;
    }
}

void listarProdutosOrdemDecrescenteLucro(const struct Produto produtos[], int numProdutos, const struct Fabricante fabricantes[], int numFabricantes) {
    struct Produto produtosOrdenados[MAX_PRODUTOS];
    memcpy(produtosOrdenados, produtos, numProdutos * sizeof(struct Produto));
    qsort(produtosOrdenados, numProdutos, sizeof(struct Produto), compararLucro);

    printf("------ Produtos em Ordem Decrescente de Lucro ------\n");
    for (int i = 0; i < numProdutos; i++) {
        int fabricanteIndex = produtosOrdenados[i].fabricanteIndex;
        if (fabricanteIndex >= 1 && fabricanteIndex <= numFabricantes) {
            printf("Produto %d:\n", i + 1);
            printf("Descricao: %s\n", produtosOrdenados[i].descricao);
            printf("Peso: %.2f\n", produtosOrdenados[i].peso);
            printf("Valor de Compra: %.2f\n", produtosOrdenados[i].valorCompra);
            printf("Valor de Venda: %.2f\n", produtosOrdenados[i].valorVenda);
            printf("Valor do Lucro: %.2f\n", produtosOrdenados[i].valorLucro);
            printf("Percentual do Lucro: %.2f%%\n", produtosOrdenados[i].percentualLucro);
            printf("Fabricante: %s\n", fabricantes[fabricanteIndex - 1].nome);
            printf("\n");
        }
    }
}

int main() {
    struct Fabricante fabricantes[MAX_FABRICANTES];
    int numFabricantes = 0;

    struct Produto produtos[MAX_PRODUTOS];
    int numProdutos = 0;

    int opcao;
    do {
        printf("-------- Menu de Opcoes --------\n");
        printf("1. Cadastrar Fabricantes\n");
        printf("2. Cadastrar Produtos\n");
        printf("3. Listar Marcas\n");
        printf("4. Listar Produtos\n");
        printf("5. Listar Produtos de um Estado\n");
        printf("6. Listar Produtos de uma Marca\n");
        printf("7. Listar Estado(s) do Produto Mais Caro\n");
        printf("8. Listar Fabricante(s) do Produto Mais Barato\n");
        printf("9. Listar Produtos em Ordem Crescente de Valor\n");
        printf("10. Listar Produtos em Ordem Decrescente de Lucro\n");
        printf("0. Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFabricantes(fabricantes, &numFabricantes);
                break;
            case 2:
                cadastrarProdutos(produtos, numFabricantes, &numProdutos);
                break;
            case 3:
                listarMarcas(fabricantes, numFabricantes);
                break;
            case 4:
                listarProdutos(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 5: {
                char estado[MAX_DESCRICAO];
                printf("Informe o estado: ");
                scanf("%s", estado);
                listarProdutosEstado(produtos, numProdutos, fabricantes, numFabricantes, estado);
                break;
            }
            case 6: {
                char marca[MAX_DESCRICAO];
                printf("Informe a marca: ");
                scanf("%s", marca);
                listarProdutosMarca(produtos, numProdutos, fabricantes, numFabricantes, marca);
                break;
            }
            case 7:
                estadoProdutoMaisCaro(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 8:
                fabricantesProdutoMaisBarato(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 9:
                listarProdutosOrdemCrescenteValor(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 10:
                listarProdutosOrdemDecrescenteLucro(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Digite novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}
