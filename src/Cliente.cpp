#include "Cliente.hpp"
#include <sstream>

// Construtor
Cliente::Cliente(int id, const std::string &nome)
    : id(id), nome(nome), carrinho() {}

// Getters
int Cliente::getId() const
{
  return id;
}

std::string Cliente::getNome() const
{
  return nome;
}

// Setter
void Cliente::setNome(const std::string &nome)
{
  this->nome = nome;
}

// Retorna referência ao carrinho
Carrinho &Cliente::getCarrinho()
{
  return carrinho;
}

// Representação em string
std::string Cliente::toString() const
{
  std::ostringstream oss;
  oss << "Cliente [ID: " << id << ", Nome: " << nome << "]";
  return oss.str();
}
