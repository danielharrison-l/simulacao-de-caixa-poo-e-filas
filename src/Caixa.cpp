#include "../include/Cliente.hpp"
#include "../include/Caixa.hpp"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <map>

using json = nlohmann::json;

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
  std::string nomeArquivo = "data/historico_compras.json";
  json historicoCompleto;

  std::ifstream arquivoLeitura(nomeArquivo);
  if (arquivoLeitura.is_open())
  {
    try
    {
      arquivoLeitura >> historicoCompleto;
    }
    catch (const std::exception &e)
    {
      std::cout << "Arquivo JSON corrompido ou vazio. Criando novo histórico." << std::endl;
      historicoCompleto = json::object();
    }
    arquivoLeitura.close();
  }
  else
  {
    historicoCompleto = json::object();
  }

  if (!historicoCompleto.contains("compras"))
  {
    historicoCompleto["compras"] = json::array();
  }

  json novaCompra;
  novaCompra["id_compra"] = historicoCompleto["compras"].size() + 1;
  novaCompra["caixa"] = nomeCaixa;
  novaCompra["cliente"]["id"] = cliente.getId();
  novaCompra["cliente"]["nome"] = cliente.getNome();

  std::time_t agora = std::time(nullptr);
  char buffer[100];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&agora));
  novaCompra["timestamp"] = buffer;

  const auto &carrinho = cliente.getCarrinho();
  novaCompra["total"] = carrinho.calcularPrecoTotal();

  novaCompra["itens"] = json::array();
  const auto &produtos = carrinho.getProdutos();

  std::map<int, int> contadorProdutos;
  for (const auto &produto : produtos)
  {
    contadorProdutos[produto.getId()]++;
  }

  for (const auto &par : contadorProdutos)
  {
    const Produto *produtoEncontrado = nullptr;
    for (const auto &produto : produtos)
    {
      if (produto.getId() == par.first)
      {
        produtoEncontrado = &produto;
        break;
      }
    }

    if (produtoEncontrado)
    {
      json itemJson;
      itemJson["id"] = produtoEncontrado->getId();
      itemJson["nome"] = produtoEncontrado->getNome();
      itemJson["preco_unitario"] = produtoEncontrado->getPreco();
      itemJson["quantidade"] = par.second;
      itemJson["subtotal"] = produtoEncontrado->getPreco() * par.second;

      novaCompra["itens"].push_back(itemJson);
    }
  }

  historicoCompleto["compras"].push_back(novaCompra);

  historicoCompleto["total_compras"] = historicoCompleto["compras"].size();
  historicoCompleto["ultima_atualizacao"] = buffer;

  std::ofstream arquivoEscrita(nomeArquivo);
  if (!arquivoEscrita.is_open())
  {
    std::cerr << "Erro ao salvar histórico de compras!" << std::endl;
    return;
  }

  arquivoEscrita << historicoCompleto.dump(4);
  arquivoEscrita.close();

  std::cout << "Compra #" << novaCompra["id_compra"] << " adicionada ao histórico: " << nomeArquivo << std::endl;
}
