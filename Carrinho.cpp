#include "Carrinho.h"

int main(){
    Carrinho carrinhoDeCompras;
    vector<dados> carro1 = {"Batata",3.5,10};
    vector<dados> carro2 = {"Pizza",15,2};

    carrinhoDeCompras.adicionarAoCarrinho(carro1);
    carrinhoDeCompras.adicionarAoCarrinho(carro2);

    carrinhoDeCompras.imprimirLista();

    carrinhoDeCompras.imprimirPrecoEQuantidade();


    return 0;
}