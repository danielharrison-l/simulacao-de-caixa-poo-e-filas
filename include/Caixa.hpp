#ifndef CAIXA_HPP
#define CAIXA_HPP

#include <string>
#include "Cliente.hpp"

class Caixa
{
private:
  std::string nomeCaixa;

public:
  Caixa(const std::string &nome);

  void processarCompra(Cliente &cliente);

  void salvarCompraEmArquivo(const Cliente &cliente) const;
};

#endif
