#include "../include/Produto.hpp"
#include <sstream>
#include <iomanip>

Produto::Produto(int id, const std::string &nome, double preco, double quantidade, UnidadeMedida unidade)
    : id(id), nome(nome), preco(preco), quantidade(quantidade), unidade(unidade) {}

Produto::Produto(int id, const std::string &nome, double preco, double peso)
    : id(id), nome(nome), preco(preco), quantidade(peso), unidade(UnidadeMedida::GRAMAS) {}

Produto::Produto(int id, const std::string &nome, double preco)
    : id(id), nome(nome), preco(preco), quantidade(0.0), unidade(UnidadeMedida::UNIDADES) {}

int Produto::getId() const
{
  return id;
}

std::string Produto::getNome() const
{
  return nome;
}

double Produto::getPreco() const
{
  return preco;
}

double Produto::getQuantidade() const
{
  return quantidade;
}

UnidadeMedida Produto::getUnidade() const
{
  return unidade;
}

double Produto::getPeso() const
{
  if (UtilUnidade::isPeso(unidade))
  {
    return UtilUnidade::converterParaUnidadeBase(quantidade, unidade);
  }
  return 0.0;
}

void Produto::setNome(const std::string &nome)
{
  this->nome = nome;
}

void Produto::setPreco(double preco)
{
  this->preco = preco;
}

void Produto::setQuantidade(double quantidade)
{
  this->quantidade = quantidade;
}

void Produto::setUnidade(UnidadeMedida unidade)
{
  this->unidade = unidade;
}

void Produto::setPeso(double peso)
{
  this->quantidade = peso;
  this->unidade = UnidadeMedida::GRAMAS;
}

std::string Produto::toString() const
{
  std::ostringstream oss;
  oss << "Produto [ID: " << id
      << ", Nome: " << nome
      << ", Preço: R$" << std::fixed << std::setprecision(2) << preco;

  if (quantidade > 0.0)
  {
    oss << ", " << UtilUnidade::formatarQuantidade(quantidade, unidade);
  }

  oss << "]";
  return oss.str();
}
