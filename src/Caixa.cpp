#include "Cliente.hpp"
#include "Caixa.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

Caixa::Caixa(const std::string &nome) : nomeCaixa(nome) {}

void Caixa::processarCompra(Cliente &cliente)
{
  std::cout << "Cliente: " << cliente.getNome() << std::endl;
  std::cout << "Carrinho do cliente:" << std::endl;

  cliente.getCarrinho().imprimirLista();

  double total = cliente.getCarrinho().calcularPrecoTotal();
  std::cout << "Total a pagar: R$" << std::fixed << std::setprecision(2) << total << std::endl;

  salvarCompraEmArquivo(cliente);
}

void Caixa::salvarCompraEmArquivo(const Cliente &cliente) const
{
  std::string nomeArquivo = "compra_cliente_" + std::to_string(cliente.getId()) + ".txt";
  std::ofstream arquivo(nomeArquivo);

  if (!arquivo.is_open())
  {
    std::cerr << "Erro ao criar arquivo para salvar a compra!" << std::endl;
    return;
  }
}
