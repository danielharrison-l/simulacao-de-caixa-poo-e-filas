#include "../include/Carrinho.hpp"
#include <iostream>
#include <iomanip>

void Carrinho::adicionarProduto(const Produto &produto)
{
  carrinhoDeCompras.push_back(produto);
}

void Carrinho::removerProduto(int indice)
{
  if (indice > 0 && indice <= (int)carrinhoDeCompras.size())
  {
    carrinhoDeCompras.erase(carrinhoDeCompras.begin() + (indice - 1));
    std::cout << "Produto removido com sucesso!" << std::endl;
  }
  else
  {
    std::cout << "Índice inválido!" << std::endl;
  }
}

double Carrinho::calcularPrecoTotal() const
{
  double total = 0;
  for (const auto &produto : carrinhoDeCompras)
  {
    total += produto.getPreco();
  }
  return total;
}

void Carrinho::imprimirLista() const
{
  imprimirLista(std::cout);
}

void Carrinho::imprimirLista(std::ostream &os) const
{
  if (carrinhoDeCompras.empty())
  {
    os << "Seu carrinho está vazio!\n";
    return;
  }

  os << "-------------------------- Produtos no Carrinho --------------------------\n";
  int numero = 1;
  for (const auto &produto : carrinhoDeCompras)
  {
    os << numero << ". " << produto.toString() << std::endl;
    numero++;
  }
  os << "-------------------------------------------------------------------------\n";
}

const std::vector<Produto>& Carrinho::getProdutos() const
{
  return carrinhoDeCompras;
}
