#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>
#include "UnidadeMedida.hpp"

class Produto
{
private:
  int id;
  std::string nome;
  double preco;
  double quantidade;
  UnidadeMedida unidade;

public:
  Produto(int id, const std::string &nome, double preco, double quantidade, UnidadeMedida unidade);

  Produto(int id, const std::string &nome, double preco, double peso);

  Produto(int id, const std::string &nome, double preco);

  int getId() const;
  std::string getNome() const;
  double getPreco() const;
  double getQuantidade() const;
  UnidadeMedida getUnidade() const;

  double getPeso() const;

  void setNome(const std::string &nome);
  void setPreco(double preco);
  void setQuantidade(double quantidade);
  void setUnidade(UnidadeMedida unidade);
  void setPeso(double peso);

  std::string toString() const;
};

#endif
