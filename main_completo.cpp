#include <iostream>
#include <vector>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif
#include "include/Produto.hpp"
#include "include/Carrinho.hpp"
#include "include/Cliente.hpp"
#include "include/FilaClientes.hpp"
#include "include/Caixa.hpp"
#include "include/CaixaInterativo.hpp"
#include "include/FormaPagamento.hpp"
#include "include/GeradorClientes.hpp"
#include "include/UnidadeMedida.hpp"
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

      if (item.contains("quantidade") && item.contains("unidade"))
      {
        double quantidade = item["quantidade"];
        std::string unidadeStr = item["unidade"];
        UnidadeMedida unidade = UtilUnidade::stringParaUnidade(unidadeStr);
        produtos.emplace_back(id, nome, preco, quantidade, unidade);
      }
      else if (item.contains("peso"))
      {
        Compatibilidade com formato antigo double peso = item["peso"];
        produtos.emplace_back(id, nome, preco, peso);
      }
      else
      {
        Produto sem medida
            produtos.emplace_back(id, nome, preco);
      }
    }

    std::cout << "Produtos carregados do arquivo JSON com sucesso!" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Erro ao ler JSON: " << e.what() << std::endl;
    std::cout << "Usando produtos padrão." << std::endl;
    produtos.emplace_back(1, "Arroz 1kg", 9.90);
    produtos.emplace_back(2, "Feijão 1kg", 8.49);
    produtos.emplace_back(3, "Macarrão 500g", 5.29);
  }

  return produtos;
}

void gerarClientesIniciais(FilaClientes &fila, GeradorClientes &gerador, int quantidade)
{
  std::cout << "Gerando clientes iniciais..." << std::endl;

  for (int i = 0; i < quantidade; ++i)
  {
    Cliente cliente = gerador.criarClienteAleatorio();
    fila.adicionarCliente(cliente);
  }

  std::cout << "✅ " << quantidade << " clientes adicionados à fila inicial!" << std::endl;
}

int main()
{
  configurarAcentos();

  std::cout << "🏪 ========================================== 🏪" << std::endl;
  std::cout << "    SISTEMA DE CAIXA INTERATIVO COMPLETO" << std::endl;
  std::cout << "         Com Pagamentos e Geração Dinâmica" << std::endl;
  std::cout << "🏪 ========================================== 🏪" << std::endl;
  std::cout << std::endl;

  std::cout << "⏳ Carregando sistema..." << std::endl;

  Carregar produtos
      std::vector<Produto>
          produtos = carregarProdutosJSON("data/produtos.json");

  Criar fila e gerador
      FilaClientes fila;
  GeradorClientes gerador(&produtos);

  Configurar gerador(clientes chegam a cada 15 - 45 segundos)
      gerador.setIntervaloChegada(15, 45);
  gerador.setQuantidadeProdutos(1, 10);

  Gerar alguns clientes iniciais
      gerarClientesIniciais(fila, gerador, 3);

  std::cout << std::endl;
  std::cout << "✅ Sistema carregado com sucesso!" << std::endl;
  std::cout << "📦 Produtos disponíveis: " << produtos.size() << std::endl;
  std::cout << "👥 Clientes na fila inicial: " << fila.tamanho() << std::endl;
  std::cout << "🔄 Geração dinâmica: ATIVADA" << std::endl;
  std::cout << "💳 Formas de pagamento: ATIVADAS" << std::endl;
  std::cout << std::endl;

  std::cout << "🎮 FUNCIONALIDADES DISPONÍVEIS:" << std::endl;
  std::cout << "   • Clientes chegam automaticamente a cada 15-45 segundos" << std::endl;
  std::cout << "   • 4 formas de pagamento (Dinheiro, Débito, Crédito, PIX)" << std::endl;
  std::cout << "   • Simulação de falhas de pagamento realísticas" << std::endl;
  std::cout << "   • Cálculo automático de troco" << std::endl;
  std::cout << "   • Histórico completo salvo em JSON" << std::endl;
  std::cout << std::endl;

  Iniciar sistema interativo
      CaixaInterativo caixaInterativo("Caixa Premium", &fila, &produtos);
  caixaInterativo.iniciarSimulacao();

  std::cout << "\n🎉 Obrigado por usar o Sistema de Caixa Completo!" << std::endl;
  std::cout << "📊 Verifique o arquivo 'data/historico_compras.json' para ver todas as vendas!" << std::endl;

  return 0;
}
