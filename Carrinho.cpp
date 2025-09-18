#include "Carrinho.h"

int main(){
    Carrinho carrinhoDeCompras;
    
    carrinhoDeCompras.imprimirLista();

    carrinhoDeCompras.deletarOuAdicionarAoCarrinho();

    carrinhoDeCompras.imprimirLista();
    carrinhoDeCompras.calcularPrecoTotalDoCarrinho();
    return 0;
}