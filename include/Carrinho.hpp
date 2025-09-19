#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>
#include "Produto.hpp"
#include <ostream>

class Carrinho
{
private:
    std::vector<Produto> carrinhoDeCompras;

public:
    void adicionarProduto(const Produto &produto);
    void removerProduto(int indice);
    void imprimirLista() const;
    void imprimirLista(std::ostream &os) const;
    double calcularPrecoTotal() const;
    const std::vector<Produto>& getProdutos() const;
};

#endif
