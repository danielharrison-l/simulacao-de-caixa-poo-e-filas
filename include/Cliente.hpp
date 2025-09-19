#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include "Carrinho.hpp"

class Cliente
{
private:
  int id;
  std::string nome;
  Carrinho carrinho; // cada cliente tem um carrinho próprio

public:
  // Construtor
  Cliente(int id, const std::string &nome);

  // Getters
  int getId() const;
  std::string getNome() const;

  // Setter
  void setNome(const std::string &nome);

  // Acesso ao carrinho
  Carrinho &getCarrinho();

  // Representação em string
  std::string toString() const;
};

#endif // CLIENTE_HPP
