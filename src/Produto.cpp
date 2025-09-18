#include "Produto.hpp"
#include <sstream>

Produto::Produto(int id, const std::string &nome, double preco)
    : id(id), nome(nome), preco(preco) {}

int Produto::getId() const
{
  return this->id;
}

std::string Produto::getNome() const
{
  return this->nome;
}

double Produto::getPreco() const
{
  return this->preco;
}

void Produto::setNome(const std::string &nome)
{
  this->nome = nome;
}

void Produto::setPreco(double preco)
{
  this->preco = preco;
}

std::string Produto::toString() const
{
  std::ostringstream oss;
  oss << "Produto [ID: " << id
      << ", Nome: " << nome
      << ", Preço: R$" << preco << "]";
  return oss.str();
}
