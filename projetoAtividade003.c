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
    char estado[3];
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

void calcularLucro(struct Produto *produto);

int validarQuantidade(int min, int max, char* tipo);

void cadastrarFabricantes(struct Fabricante fabricantes[], int *numFabricantes);

const char* unidadeFederativa();

void cadastrarProdutos(struct Produto produtos[], int numFabricantes, int *numProdutos);

void exibirFabricantes(struct Fabricante fabricantes[], int numFabricantes);

void exibirProdutos(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes);

void listarMarcas(struct Fabricante fabricantes[], int numFabricantes);

void listarProdutos(struct Produto produtos[], int numProdutos);

void listarProdutosEstado(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes);

void listarProdutosMarca(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes);

void estadoProdutoMaisCaro(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes);

void fabricanteProdutoMaisBarato(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes);

void listarProdutosOrdenadosValor(struct Produto produtos[], int numProdutos);

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
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}

void calcularLucro(struct Produto *produto) {
    produto->valorLucro = produto->valorVenda - produto->valorCompra;
    produto->percentualLucro = (produto->valorLucro / produto->valorCompra) * 100;
}

int validarQuantidade(int min, int max, char* tipo) {
    int quantidade;
    do {
        printf("Digite a quantidade de %s (min: %d, max: %d): ", tipo, min, max);
        scanf("%d", &quantidade);
        if (quantidade < min || quantidade > max) {
            printf("Quantidade invalida. Tente novamente.\n");
        }
    } while (quantidade < min || quantidade > max);

    return quantidade;
}

void cadastrarFabricantes(struct Fabricante fabricantes[], int *numFabricantes) {
    int quantidade = validarQuantidade(MIN_FABRICANTES, MAX_FABRICANTES, "fabricantes");

    for (int i = 0; i < quantidade; i++) {
        struct Fabricante novoFabricante;
        printf("\n--- Cadastro de Fabricante %d ---\n", *numFabricantes + 1);

        printf("Nome: ");
        scanf(" %[^\n]", novoFabricante.nome);

        printf("Site: ");
        scanf(" %[^\n]", novoFabricante.site);

        printf("Telefone: ");
        scanf(" %[^\n]", novoFabricante.telefone);

        printf("Estado (UF): ");
        strcpy(novoFabricante.estado, unidadeFederativa());

        fabricantes[*numFabricantes] = novoFabricante;
        (*numFabricantes)++;
    }

    printf("Fabricantes cadastrados com sucesso!\n");
}

const char* unidadeFederativa() {
    int opcao;
    const char* uf;
    do {
        printf("Selecione a unidade federativa:\n");
        printf("1. AC - Acre\n");
        printf("2. AL - Alagoas\n");
        printf("3. AP - Amapá\n");
        printf("4. AM - Amazonas\n");
        printf("5. BA - Bahia\n");
        printf("6. CE - Ceará\n");
        printf("7. DF - Distrito Federal\n");
        printf("8. ES - Espírito Santo\n");
        printf("9. GO - Goiás\n");
        printf("10. MA - Maranhão\n");
        printf("11. MT - Mato Grosso\n");
        printf("12. MS - Mato Grosso do Sul\n");
        printf("13. MG - Minas Gerais\n");
        printf("14. PA - Pará\n");
        printf("15. PB - Paraíba\n");
        printf("16. PR - Paraná\n");
        printf("17. PE - Pernambuco\n");
        printf("18. PI - Piauí\n");
        printf("19. RJ - Rio de Janeiro\n");
        printf("20. RN - Rio Grande do Norte\n");
        printf("21. RS - Rio Grande do Sul\n");
        printf("22. RO - Rondônia\n");
        printf("23. RR - Roraima\n");
        printf("24. SC - Santa Catarina\n");
        printf("25. SP - São Paulo\n");
        printf("26. SE - Sergipe\n");
        printf("27. TO - Tocantins\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                uf = "AC";
                break;
            case 2:
                uf = "AL";
                break;
            case 3:
                uf = "AP";
                break;
            case 4:
                uf = "AM";
                break;
            case 5:
                uf = "BA";
                break;
            case 6:
                uf = "CE";
                break;
            case 7:
                uf = "DF";
                break;
            case 8:
                uf = "ES";
                break;
            case 9:
                uf = "GO";
                break;
            case 10:
                uf = "MA";
                break;
            case 11:
                uf = "MT";
                break;
            case 12:
                uf = "MS";
                break;
            case 13:
                uf = "MG";
                break;
            case 14:
                uf = "PA";
                break;
            case 15:
                uf = "PB";
                break;
            case 16:
                uf = "PR";
                break;
            case 17:
                uf = "PE";
                break;
            case 18:
                uf = "PI";
                break;
            case 19:
                uf = "RJ";
                break;
            case 20:
                uf = "RN";
                break;
            case 21:
                uf = "RS";
                break;
            case 22:
                uf = "RO";
                break;
            case 23:
                uf = "RR";
                break;
            case 24:
                uf = "SC";
                break;
            case 25:
                uf = "SP";
                break;
            case 26:
                uf = "SE";
                break;
            case 27:
                uf = "TO";
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao < 1 || opcao > 27);

    return uf;
}

void cadastrarProdutos(struct Produto produtos[], int numFabricantes, int *numProdutos) {
    int quantidade = validarQuantidade(MIN_PRODUTOS, MAX_PRODUTOS, "produtos");

    for (int i = 0; i < quantidade; i++) {
        struct Produto novoProduto;
        printf("\n--- Cadastro de Produto ---\n");
        printf("Produto %d:\n", i + 1);
        printf("Descricao: ");
        scanf(" %[^\n]", novoProduto.descricao);

        printf("Peso: ");
        scanf("%f", &novoProduto.peso);

        printf("Valor de Compra: ");
        scanf("%f", &novoProduto.valorCompra);

        printf("Valor de Venda: ");
        scanf("%f", &novoProduto.valorVenda);

        printf("Fabricante Index (1 a %d): ", numFabricantes);
        scanf("%d", &novoProduto.fabricanteIndex);

        //novoProduto.fabricanteIndex = -1;
        //while (novoProduto.fabricanteIndex < 0 || novoProduto.fabricanteIndex >= numFabricantes) {
            //printf("Fabricante indice (1 a %d):", numFabricantes);
            //scanf("%d", &novoProduto.fabricanteIndex);
            //if (novoProduto.fabricanteIndex < 0 || novoProduto.fabricanteIndex > numFabricantes) {
                //printf("Indice de fabricante invalido. Tente novamente.\n");
            //}
        //}

        calcularLucro(&novoProduto);
        produtos[*numProdutos] = novoProduto;
        (*numProdutos)++;
    }

    printf("Produtos cadastrados com sucesso!\n");
}

void exibirFabricantes(struct Fabricante fabricantes[], int numFabricantes) {
    printf("\n--- Fabricantes Cadastrados ---\n");
    if (numFabricantes == 0) {
        printf("Nenhum fabricante cadastrado.\n");
    } else {
        for (int i = 0; i < numFabricantes; i++) {
            printf("Fabricante %d:\n", i + 1);
            printf("Nome: %s\n", fabricantes[i].nome);
            printf("Site: %s\n", fabricantes[i].site);
            printf("Telefone: %s\n", fabricantes[i].telefone);
            printf("Estado: %s\n", fabricantes[i].estado);
            printf("\n");
        }
    }
}

void exibirProdutos(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    printf("\n--- Produtos Cadastrados ---\n");
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        for (int i = 0; i < numProdutos; i++) {
            printf("Produto %d:\n", i + 1);
            printf("Descricao: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de Compra: %.2f\n", produtos[i].valorCompra);
            printf("Valor de Venda: %.2f\n", produtos[i].valorVenda);
            printf("Valor de Lucro: %.2f\n", produtos[i].valorLucro);
            printf("Percentual de Lucro: %.2f%%\n", produtos[i].percentualLucro);

            int fabricanteIndex = produtos[i].fabricanteIndex;
            if (fabricanteIndex >= 0 && fabricanteIndex < numFabricantes) {
                printf("Fabricante: %s\n", fabricantes[fabricanteIndex].nome);
            } else {
                printf("Fabricante: Nao informado\n");
            }

            printf("\n");
        }
    }
}

void listarMarcas(struct Fabricante fabricantes[], int numFabricantes) {
    printf("\n--- Lista de Marcas ---\n");
    if (numFabricantes == 0) {
        printf("Nenhum fabricante cadastrado.\n");
    } else {
        for (int i = 0; i < numFabricantes; i++) {
            printf("%d. %s\n", i + 1, fabricantes[i].nome);
        }
    }
}

void listarProdutos(struct Produto produtos[], int numProdutos) {
    printf("\n--- Lista de Produtos ---\n");
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        for (int i = 0; i < numProdutos; i++) {
            printf("%d. %s\n", i + 1, produtos[i].descricao);
        }
    }
}

void listarProdutosEstado(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    printf("\n--- Lista de Produtos por Estado ---\n");
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        char estado[3];
        printf("Digite o estado (UF): ");
        scanf(" %[^\n]", estado);

        int encontrado = 0;
        for (int i = 0; i < numProdutos; i++) {
            int fabricanteIndex = produtos[i].fabricanteIndex;
            if (fabricanteIndex >= 0 && fabricanteIndex < numFabricantes) {
                if (strcmp(fabricantes[fabricanteIndex].estado, estado) == 0) {
                    printf("Produto: %s\n", produtos[i].descricao);
                    printf("Fabricante: %s\n", fabricantes[fabricanteIndex].nome);
                    printf("Valor de Venda: %.2f\n", produtos[i].valorVenda);
                    printf("\n");
                    encontrado = 1;
                }
            }
        }

        if (!encontrado) {
            printf("Nenhum produto encontrado para o estado informado.\n");
        }
    }
}

void listarProdutosMarca(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    printf("\n--- Lista de Produtos por Marca ---\n");
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        int marcaIndex;
        listarMarcas(fabricantes, numFabricantes);
        printf("Digite o indice da marca: ");
        scanf("%d", &marcaIndex);
        marcaIndex--;

        if (marcaIndex >= 0 && marcaIndex < numFabricantes) {
            int encontrado = 0;
            for (int i = 0; i < numProdutos; i++) {
                int fabricanteIndex = produtos[i].fabricanteIndex;
                if (fabricanteIndex == marcaIndex) {
                    printf("Produto: %s\n", produtos[i].descricao);
                    printf("Valor de Venda: %.2f\n", produtos[i].valorVenda);
                    printf("\n");
                    encontrado = 1;
                }
            }

            if (!encontrado) {
                printf("Nenhum produto encontrado para a marca selecionada.\n");
            }
        } else {
            printf("Indice de marca invalido.\n");
        }
    }
}

void estadoProdutoMaisCaro(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    printf("\n--- Estado do Produto Mais Caro ---\n");
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        int indiceProdutoMaisCaro = 0;
        float valorMaisCaro = produtos[0].valorVenda;

        for (int i = 1; i < numProdutos; i++) {
            if (produtos[i].valorVenda > valorMaisCaro) {
                valorMaisCaro = produtos[i].valorVenda;
                indiceProdutoMaisCaro = i;
            }
        }

        int fabricanteIndex = produtos[indiceProdutoMaisCaro].fabricanteIndex;
        if (fabricanteIndex >= 0 && fabricanteIndex < numFabricantes) {
            printf("Estado: %s\n", fabricantes[fabricanteIndex].estado);
        } else {
            printf("Estado: Nao informado\n");
        }
    }
}

void fabricanteProdutoMaisBarato(struct Produto produtos[], int numProdutos, struct Fabricante fabricantes[], int numFabricantes) {
    printf("\n--- Fabricante do Produto Mais Barato ---\n");
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        int indiceProdutoMaisBarato = 0;
        float valorMaisBarato = produtos[0].valorVenda;

        for (int i = 1; i < numProdutos; i++) {
            if (produtos[i].valorVenda < valorMaisBarato) {
                valorMaisBarato = produtos[i].valorVenda;
                indiceProdutoMaisBarato = i;
            }
        }

        int fabricanteIndex = produtos[indiceProdutoMaisBarato].fabricanteIndex;
        if (fabricanteIndex >= 0 && fabricanteIndex < numFabricantes) {
            printf("Fabricante: %s\n", fabricantes[fabricanteIndex].nome);
        } else {
            printf("Fabricante: Nao informado\n");
        }
    }
}

void listarProdutosOrdenadosValor(struct Produto produtos[], int numProdutos) {
    printf("\n--- Lista de Produtos Ordenados por Valor ---\n");
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        struct Produto produtosOrdenados[MAX_PRODUTOS];
        for (int i = 0; i < numProdutos; i++) {
            produtosOrdenados[i] = produtos[i];
        }

        for (int i = 0; i < numProdutos - 1; i++) {
            for (int j = 0; j < numProdutos - i - 1; j++) {
                if (produtosOrdenados[j].valorVenda > produtosOrdenados[j + 1].valorVenda) {
                    struct Produto temp = produtosOrdenados[j];
                    produtosOrdenados[j] = produtosOrdenados[j + 1];
                    produtosOrdenados[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < numProdutos; i++) {
            printf("%d. %s - R$ %.2f\n", i + 1, produtosOrdenados[i].descricao, produtosOrdenados[i].valorVenda);
        }
    }
}
