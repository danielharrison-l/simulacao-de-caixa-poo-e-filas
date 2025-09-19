#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#endif
#include "include/Produto.hpp"
#include "include/Carrinho.hpp"
#include "include/Cliente.hpp"
#include "include/FilaClientes.hpp"
#include "include/Caixa.hpp"
#include "include/CaixaInterativo.hpp"
#include "include/json.hpp"

using json = nlohmann::json;

void configurarAcentos()
{
#ifdef _WIN32
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);
  setlocale(LC_ALL, "Portuguese");
#endif
}

std::vector<Produto> carregarProdutosJSON(const std::string &caminho)
{
  std::vector<Produto> produtos;

  std::ifstream arquivo(caminho);
  if (!arquivo.is_open())
  {
    std::cout << "Arquivo JSON não encontrado. Usando produtos padrão." << std::endl;
    produtos.emplace_back(1, "Arroz 1kg", 9.90);
    produtos.emplace_back(2, "Feijão 1kg", 8.49);
    produtos.emplace_back(3, "Macarrão 500g", 5.29);
    produtos.emplace_back(4, "Leite 1L", 4.99);
    produtos.emplace_back(5, "Café 500g", 14.50);
    return produtos;
  }

  try
  {
    json dadosJSON;
    arquivo >> dadosJSON;

    for (const auto &item : dadosJSON["produtos"])
    {
      int id = item["id"];
      std::string nome = item["nome"];
      double preco = item["preco"];
      produtos.emplace_back(id, nome, preco);
    }

    std::cout << "Produtos carregados do arquivo JSON com sucesso!" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Erro ao ler JSON: " << e.what() << std::endl;
    std::cout << "Usando produtos padr?o." << std::endl;
    produtos.emplace_back(1, "Arroz 1kg", 9.90);
    produtos.emplace_back(2, "Feij?o 1kg", 8.49);
    produtos.emplace_back(3, "Macarr?o 500g", 5.29);
  }

  return produtos;
}

void gerarClientesAleatorios(FilaClientes &fila, const std::vector<Produto> &produtos)
{
  std::vector<std::string> nomes = {
      "Ana Silva", "Bruno Costa", "Carla Santos", "Diego Oliveira",
      "Elena Ferreira", "Felipe Lima", "Gabriela Rocha", "Hugo Alves",
      "Isabela Martins", "Jo?o Pereira", "Karina Souza", "Lucas Barbosa"};

  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> qtdClientesDist(3, 8);
  std::uniform_int_distribution<int> qtdProdutosDist(1, 6);
  std::uniform_int_distribution<int> nomeDist(0, nomes.size() - 1);
  std::uniform_int_distribution<int> produtoDist(0, produtos.size() - 1);

  int qtdClientes = qtdClientesDist(rng);

  for (int i = 0; i < qtdClientes; ++i)
  {
    Cliente cliente(i + 1, nomes[nomeDist(rng)]);

    int qtdProdutos = qtdProdutosDist(rng);
    for (int j = 0; j < qtdProdutos; ++j)
    {
      cliente.getCarrinho().adicionarProduto(produtos[produtoDist(rng)]);
    }

    fila.adicionarCliente(cliente);
  }
}

int main()
{
  configurarAcentos();

  std::cout << "?? Iniciando Sistema de Caixa Interativo..." << std::endl;
  std::cout << "? Carregando dados..." << std::endl;

  std::vector<Produto> produtos = carregarProdutosJSON("data/produtos.json");

  FilaClientes fila;
  gerarClientesAleatorios(fila, produtos);

  std::cout << "? Sistema carregado!" << std::endl;
  std::cout << "?? Produtos dispon?veis: " << produtos.size() << std::endl;
  std::cout << "?? Clientes na fila: " << fila.tamanho() << std::endl;
  std::cout << std::endl;

  CaixaInterativo caixaInterativo("Caixa 1", &fila, &produtos);
  caixaInterativo.iniciarSimulacao();

  std::cout << "\n?? Obrigado por usar o Sistema de Caixa Interativo!" << std::endl;

  return 0;
}
