#include <stdio.h>
#include <stdlib.h>

typedef struct{             //o typedef serve para criar uma struct que seu nome e Produto, logo criei um tipo de dado chamado Produto. Quando referencio Produto na main estou me referindo a essa struct.
    char descricao[500];
    double peso;
    double valorDeCompra;
    double valorDeVenda:
    double valorDoLucro;
    double porcentagemDeLucro:
    char fabricante[100];

}Produto;

typedef struct{             //mesma coisa aqui com o typedef
    char nomeDaFabrica[100];
    char site[200];
    char telefone[20];
    char unidadeFederativa[3];
    Produto produtos[1];  // aqui estou criando um vetor da struct Produtos, que se chama produtos.
                        //mudar o tamanho do vetor depois, tem que ser no minimo 3 maximo 50
}Fabricante;


int main(){
    system("clear");
    

    return 0;
}