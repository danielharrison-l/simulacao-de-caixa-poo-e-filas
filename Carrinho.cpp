#include "Carrinho.h"

int main(){
    Carrinho carrinhoDeCompras;
    vector<dados> carro1 = {"Batata",3.5,10};
    vector<dados> carro2 = {"Pizza",15.5,2};
    
    carrinhoDeCompras.adicionarItemAoCarrinho(carro1);
    carrinhoDeCompras.adicionarItemAoCarrinho(carro2);

    carrinhoDeCompras.imprimirLista();

    
    

    carrinhoDeCompras.deletarOuAdicionarAoCarrinho();

    carrinhoDeCompras.imprimirLista();
    cout << "Seu subtotal: R$" << carrinhoDeCompras.calcularPrecoTotalDoCarrinho();
    return 0;
}