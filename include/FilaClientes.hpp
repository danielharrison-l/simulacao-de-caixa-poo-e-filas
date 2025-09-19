#ifndef FILACLIENTES_HPP
#define FILACLIENTES_HPP

#include <queue>
#include "Cliente.hpp"

class FilaClientes
{
private:
  std::queue<Cliente> fila;

public:
  void adicionarCliente(const Cliente &cliente);

  Cliente proximoCliente();

  bool vazia() const;

  size_t tamanho() const;
};

#endif
