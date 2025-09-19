#include "Carrinho.hpp"
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
  if (carrinhoDeCompras.empty())
  {
    std::cout << "Seu carrinho está vazio!\n";
    return;
  }

  std::cout << "-------------------------- Produtos no Carrinho --------------------------\n";
  int numero = 1;
  for (const auto &produto : carrinhoDeCompras)
  {
    std::cout << numero << ". " << produto.toString() << std::endl;
    numero++;
  }
  std::cout << "-------------------------------------------------------------------------\n";
}
