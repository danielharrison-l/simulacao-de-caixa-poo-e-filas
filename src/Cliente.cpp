#include "Cliente.hpp"
#include <sstream>

Cliente::Cliente(int id, const std::string &nome)
    : id(id), nome(nome), carrinho() {}

int Cliente::getId() const
{
  return id;
}

std::string Cliente::getNome() const
{
  return nome;
}

void Cliente::setNome(const std::string &nome)
{
  this->nome = nome;
}

Carrinho &Cliente::getCarrinho()
{
  return carrinho;
}

std::string Cliente::toString() const
{
  std::ostringstream oss;
  oss << "Cliente [ID: " << id << ", Nome: " << nome << "]";
  return oss.str();
}
