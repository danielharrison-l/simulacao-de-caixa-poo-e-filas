#include "../include/FilaClientes.hpp"
#include <stdexcept>

void FilaClientes::adicionarCliente(const Cliente &cliente)
{
  fila.push(cliente);
}

Cliente FilaClientes::proximoCliente()
{
  if (!fila.empty())
  {
    Cliente c = fila.front();
    fila.pop();
    return c;
  }
  throw std::runtime_error("Fila de clientes vazia!");
}

bool FilaClientes::vazia() const
{
  return fila.empty();
}

size_t FilaClientes::tamanho() const
{
  return fila.size();
}
