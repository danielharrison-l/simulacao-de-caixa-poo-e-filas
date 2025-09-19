#include <vector>
#include "Produto.hpp"

class Carrinho
{
private:
    std::vector<Produto> carrinhoDeCompras;

public:
    void adicionarProduto(const Produto &produto);
    void removerProduto(int indice);
    void imprimirLista() const;
    double calcularPrecoTotal() const;
};
