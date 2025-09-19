#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include "Carrinho.hpp"

class Cliente
{
private:
  int id;
  std::string nome;
  Carrinho carrinho;

public:
  Cliente(int id, const std::string &nome);

  int getId() const;
  std::string getNome() const;

  void setNome(const std::string &nome);

  Carrinho &getCarrinho();
  const Carrinho &getCarrinho() const;

  std::string toString() const;
};

#endif
