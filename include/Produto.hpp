#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

class Produto
{
private:
  int id;
  std::string nome;
  double preco;

public:
  Produto(int id, const std::string &nome, double preco);

  int getId() const;
  std::string getNome() const;
  double getPreco() const;

  void setNome(const std::string &nome);
  void setPreco(double preco);

  std::string toString() const;
};

#endif
