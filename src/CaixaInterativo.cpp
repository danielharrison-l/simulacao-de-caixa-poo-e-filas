#include "../include/CaixaInterativo.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

CaixaInterativo::CaixaInterativo(const std::string &nomeCaixa, FilaClientes *filaClientes, std::vector<Produto> *listaProdutos)
    : caixa(nomeCaixa), fila(filaClientes), produtos(listaProdutos), clienteAtual(nullptr),
      vendasRealizadas(0), totalVendido(0.0), geradorClientes(nullptr)
{
    geradorClientes = new GeradorClientes(produtos);
}

void CaixaInterativo::limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CaixaInterativo::mostrarCabecalho()
{
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                    🏪 SUPERMERCADO TECH 🏪                   ║" << std::endl;
    std::cout << "║                     Sistema de Caixa v1.0                   ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

void CaixaInterativo::mostrarEstatisticas()
{
    std::cout << "┌─────────────────── ESTATÍSTICAS DO DIA ───────────────────┐" << std::endl;
    std::cout << "│ Vendas realizadas: " << std::setw(3) << vendasRealizadas << "                                   │" << std::endl;
    std::cout << "│ Total vendido: R$ " << std::fixed << std::setprecision(2) << std::setw(8) << totalVendido << "                          │" << std::endl;
    std::cout << "│ Clientes na fila: " << std::setw(3) << fila->tamanho() << "                                    │" << std::endl;
    std::cout << "└────────────────────────────────────────────────────────────┘" << std::endl;
    std::cout << std::endl;
}

void CaixaInterativo::iniciarSimulacao()
{
    std::cout << "Bem-vindo ao Sistema de Caixa Interativo!" << std::endl;
    std::cout << "Pressione Enter para começar...";
    std::cin.get();

    bool continuar = true;
    while (continuar)
    {
        verificarNovosClientes();

        limparTela();
        mostrarCabecalho();
        mostrarEstatisticas();

        if (clienteAtual)
        {
            std::cout << "🛒 CLIENTE ATUAL: " << clienteAtual->getNome()
                      << " (ID: " << clienteAtual->getId() << ")" << std::endl;
            std::cout << "📦 Itens no carrinho: " << clienteAtual->getCarrinho().getProdutos().size() << std::endl;
            std::cout << "💰 Total atual: R$ " << std::fixed << std::setprecision(2)
                      << clienteAtual->getCarrinho().calcularPrecoTotal() << std::endl;
            std::cout << std::endl;
        }
        else if (!filaVazia())
        {
            std::cout << "⏳ Aguardando próximo cliente..." << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Nenhum cliente na fila." << std::endl;
            std::cout << std::endl;
        }

        mostrarMenu();

        int opcao = obterOpcao();

        switch (opcao)
        {
        case 1:
            proximoCliente();
            break;
        case 2:
            visualizarFila();
            break;
        case 3:
            adicionarProduto();
            break;
        case 4:
            removerProduto();
            break;
        case 5:
            mostrarCarrinhoAtual();
            break;
        case 6:
            finalizarCompra();
            break;
        case 7:
            mostrarRelatorio();
            break;
        case 0:
            std::cout << "\n👋 Encerrando sistema... Até logo!" << std::endl;
            continuar = false;
            break;
        default:
            std::cout << "\n❌ Opção inválida! Pressione Enter para continuar...";
            std::cin.get();
            break;
        }
    }
}

void CaixaInterativo::mostrarMenu()
{
    std::cout << "┌─────────────────────── MENU PRINCIPAL ────────────────────────┐" << std::endl;
    std::cout << "│                                                               │" << std::endl;
    std::cout << "│  1. 👤 Chamar próximo cliente                                 │" << std::endl;
    std::cout << "│  2. 👥 Visualizar fila                                        │" << std::endl;
    std::cout << "│  3. ➕ Adicionar produto                                      │" << std::endl;
    std::cout << "│  4. ➖ Remover produto                                        │" << std::endl;
    std::cout << "│  5. 🛒 Ver carrinho atual                                     │" << std::endl;
    std::cout << "│  6. 💳 Finalizar compra                                       │" << std::endl;
    std::cout << "│  7. 📊 Relatório do dia                                       │" << std::endl;
    std::cout << "│  0. 🚪 Sair                                                   │" << std::endl;
    std::cout << "│                                                               │" << std::endl;
    std::cout << "└───────────────────────────────────────────────────────────────┘" << std::endl;
    std::cout << std::endl;
    std::cout << "Digite sua opção: ";
}

int CaixaInterativo::obterOpcao()
{
    int opcao;
    while (!(std::cin >> opcao))
    {
        std::cout << "❌ Entrada inválida! Digite um número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();
    return opcao;
}

void CaixaInterativo::proximoCliente()
{
    if (clienteAtual)
    {
        std::cout << "\n⚠️  Você já está atendendo " << clienteAtual->getNome()
                  << ". Finalize a compra primeiro!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    if (filaVazia())
    {
        std::cout << "\nNão há clientes na fila!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    static Cliente clienteTemp = fila->proximoCliente();
    clienteAtual = &clienteTemp;

    std::cout << "\n🔔 Chamando próximo cliente..." << std::endl;
    std::cout << "👤 Cliente: " << clienteAtual->getNome()
              << " (ID: " << clienteAtual->getId() << ")" << std::endl;
    std::cout << "📦 Produtos no carrinho: " << clienteAtual->getCarrinho().getProdutos().size() << std::endl;
    std::cout << "\nPressione Enter para continuar...";
    std::cin.get();
}

void CaixaInterativo::visualizarFila()
{
    std::cout << "\n┌─────────────────── FILA DE CLIENTES ───────────────────┐" << std::endl;

    if (filaVazia())
    {
        std::cout << "│                    Fila vazia 😴                       │" << std::endl;
    }
    else
    {
        std::cout << "│ Clientes aguardando: " << std::setw(3) << fila->tamanho() << "                          │" << std::endl;
        std::cout << "│                                                       │" << std::endl;

        std::cout << "│ Fila: ";
        for (size_t i = 0; i < fila->tamanho() && i < 8; ++i)
        {
            std::cout << "👤 ";
        }
        if (fila->tamanho() > 8)
        {
            std::cout << "...";
        }
        std::cout << std::endl;
    }

    std::cout << "└───────────────────────────────────────────────────────┘" << std::endl;
    std::cout << "\nPressione Enter para continuar...";
    std::cin.get();
}

void CaixaInterativo::adicionarProduto()
{
    if (!clienteAtual)
    {
        std::cout << "\n⚠️  Nenhum cliente sendo atendido!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    std::cout << "\n┌─────────────── ADICIONAR PRODUTO ───────────────┐" << std::endl;
    std::cout << "│ Produtos disponíveis:                           │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────┘" << std::endl;

    for (size_t i = 0; i < produtos->size(); ++i)
    {
        const auto &produto = (*produtos)[i];
        std::cout << std::setw(2) << (i + 1) << ". "
                  << std::setw(20) << std::left << produto.getNome()
                  << " - R$ " << std::fixed << std::setprecision(2) << produto.getPreco() << std::endl;
    }

    std::cout << "\nDigite o número do produto (0 para cancelar): ";
    int escolha = obterOpcao();

    if (escolha == 0)
    {
        return;
    }

    if (escolha < 1 || escolha > static_cast<int>(produtos->size()))
    {
        std::cout << "❌ Produto inválido!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    const auto &produtoEscolhido = (*produtos)[escolha - 1];
    clienteAtual->getCarrinho().adicionarProduto(produtoEscolhido);

    std::cout << "\n✅ Produto adicionado: " << produtoEscolhido.getNome() << std::endl;
    std::cout << "💰 Novo total: R$ " << std::fixed << std::setprecision(2)
              << clienteAtual->getCarrinho().calcularPrecoTotal() << std::endl;
    std::cout << "Pressione Enter para continuar...";
    std::cin.get();
}

void CaixaInterativo::removerProduto()
{
    if (!clienteAtual)
    {
        std::cout << "\n⚠️  Nenhum cliente sendo atendido!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    const auto &produtosCarrinho = clienteAtual->getCarrinho().getProdutos();

    if (produtosCarrinho.empty())
    {
        std::cout << "\n🛒 Carrinho vazio!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    std::cout << "\n┌─────────────── REMOVER PRODUTO ───────────────┐" << std::endl;
    std::cout << "│ Produtos no carrinho:                         │" << std::endl;
    std::cout << "└───────────────────────────────────────────────┘" << std::endl;

    for (size_t i = 0; i < produtosCarrinho.size(); ++i)
    {
        const auto &produto = produtosCarrinho[i];
        std::cout << std::setw(2) << (i + 1) << ". "
                  << std::setw(20) << std::left << produto.getNome()
                  << " - R$ " << std::fixed << std::setprecision(2) << produto.getPreco() << std::endl;
    }

    std::cout << "\nDigite o número do produto para remover (0 para cancelar): ";
    int escolha = obterOpcao();

    if (escolha == 0)
    {
        return;
    }

    if (escolha < 1 || escolha > static_cast<int>(produtosCarrinho.size()))
    {
        std::cout << "❌ Produto inválido!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    clienteAtual->getCarrinho().removerProduto(escolha);

    std::cout << "\n✅ Produto removido!" << std::endl;
    std::cout << "💰 Novo total: R$ " << std::fixed << std::setprecision(2)
              << clienteAtual->getCarrinho().calcularPrecoTotal() << std::endl;
    std::cout << "Pressione Enter para continuar...";
    std::cin.get();
}

void CaixaInterativo::mostrarCarrinhoAtual()
{
    if (!clienteAtual)
    {
        std::cout << "\n⚠️  Nenhum cliente sendo atendido!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    std::cout << "\n┌─────────────── CARRINHO ATUAL ───────────────┐" << std::endl;
    std::cout << "│ Cliente: " << std::setw(30) << std::left << clienteAtual->getNome() << "    │" << std::endl;
    std::cout << "└───────────────────────────────────────────────┘" << std::endl;

    clienteAtual->getCarrinho().imprimirLista();

    std::cout << "\n💰 Total: R$ " << std::fixed << std::setprecision(2)
              << clienteAtual->getCarrinho().calcularPrecoTotal() << std::endl;
    std::cout << "\nPressione Enter para continuar...";
    std::cin.get();
}

void CaixaInterativo::finalizarCompra()
{
    if (!clienteAtual)
    {
        std::cout << "\n⚠️  Nenhum cliente sendo atendido!" << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    double total = clienteAtual->getCarrinho().calcularPrecoTotal();

    if (total == 0.0)
    {
        std::cout << "\n⚠️  Carrinho vazio! Adicione produtos antes de finalizar." << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    std::cout << "\n┌─────────────── FINALIZAR COMPRA ───────────────┐" << std::endl;
    std::cout << "│ Cliente: " << std::setw(30) << std::left << clienteAtual->getNome() << "    │" << std::endl;
    std::cout << "│ Total: R$ " << std::fixed << std::setprecision(2) << std::setw(8) << total << "                          │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────┘" << std::endl;

    TipoPagamento tipoPagamento = escolherFormaPagamento();

    if (tipoPagamento == static_cast<TipoPagamento>(0))
    {
        std::cout << "\n❌ Compra cancelada." << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    if (processarPagamento(total, tipoPagamento))
    {
        caixa.processarCompra(*clienteAtual);

        vendasRealizadas++;
        totalVendido += total;

        std::cout << "\n✅ Compra finalizada com sucesso!" << std::endl;
        std::cout << "🧾 Comprovante salvo no sistema." << std::endl;
        std::cout << "👋 Obrigado, " << clienteAtual->getNome() << "!" << std::endl;

        clienteAtual = nullptr;

        std::cout << "\nPressione Enter para continuar...";
        std::cin.get();
    }
    else
    {
        std::cout << "\n❌ Pagamento não realizado. Tente outra forma de pagamento." << std::endl;
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
    }
}

void CaixaInterativo::mostrarRelatorio()
{
    std::cout << "\n╔═══════════════════ RELATÓRIO DO DIA ═══════════════════╗" << std::endl;
    std::cout << "║                                                        ║" << std::endl;
    std::cout << "║  📊 Vendas realizadas: " << std::setw(3) << vendasRealizadas << "                             ║" << std::endl;
    std::cout << "║  💰 Total vendido: R$ " << std::fixed << std::setprecision(2) << std::setw(8) << totalVendido << "                      ║" << std::endl;
    std::cout << "║  👥 Clientes na fila: " << std::setw(3) << fila->tamanho() << "                              ║" << std::endl;

    if (vendasRealizadas > 0)
    {
        double ticketMedio = totalVendido / vendasRealizadas;
        std::cout << "║  🎯 Ticket médio: R$ " << std::fixed << std::setprecision(2) << std::setw(8) << ticketMedio << "                       ║" << std::endl;
    }

    std::cout << "║                                                        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\nPressione Enter para continuar...";
    std::cin.get();
}

bool CaixaInterativo::temClienteAtual() const
{
    return clienteAtual != nullptr;
}

bool CaixaInterativo::filaVazia() const
{
    return fila->vazia();
}

TipoPagamento CaixaInterativo::escolherFormaPagamento()
{
    std::cout << "\n┌─────────────── FORMA DE PAGAMENTO ───────────────┐" << std::endl;
    std::cout << "│                                                  │" << std::endl;
    std::cout << "│  1. 💵 Dinheiro                                  │" << std::endl;
    std::cout << "│  2. 💳 Cartão de Débito                          │" << std::endl;
    std::cout << "│  3. 💳 Cartão de Crédito                         │" << std::endl;
    std::cout << "│  4. 📱 PIX                                       │" << std::endl;
    std::cout << "│  0. ❌ Cancelar                                  │" << std::endl;
    std::cout << "│                                                  │" << std::endl;
    std::cout << "└──────────────────────────────────────────────────┘" << std::endl;
    std::cout << "\nEscolha a forma de pagamento: ";

    int opcao = obterOpcao();

    if (opcao >= 1 && opcao <= 4)
    {
        return static_cast<TipoPagamento>(opcao);
    }

    return static_cast<TipoPagamento>(0);
}

bool CaixaInterativo::processarPagamento(double valorTotal, TipoPagamento tipo)
{
    std::cout << "\n💳 Processando pagamento via " << processadorPagamento.obterNomePagamento(tipo) << "..." << std::endl;

    ResultadoPagamento resultado(false, "");

    switch (tipo)
    {
    case TipoPagamento::DINHEIRO:
    {
        std::cout << "💰 Digite o valor pago: R$ ";
        double valorPago;
        std::cin >> valorPago;
        std::cin.ignore();

        resultado = processadorPagamento.processarDinheiro(valorTotal, valorPago);
        break;
    }
    case TipoPagamento::CARTAO_DEBITO:
        resultado = processadorPagamento.processarCartaoDebito(valorTotal);
        break;

    case TipoPagamento::CARTAO_CREDITO:
        resultado = processadorPagamento.processarCartaoCredito(valorTotal);
        break;

    case TipoPagamento::PIX:
        resultado = processadorPagamento.processarPix(valorTotal);
        break;
    }

    std::cout << "\n"
              << (resultado.sucesso ? "✅" : "❌") << " " << resultado.mensagem << std::endl;

    if (resultado.sucesso && resultado.troco > 0)
    {
        std::cout << "💰 Troco: R$ " << std::fixed << std::setprecision(2) << resultado.troco << std::endl;
    }

    return resultado.sucesso;
}

void CaixaInterativo::verificarNovosClientes()
{
    if (geradorClientes)
    {
        geradorClientes->adicionarClienteSeNecessario(*fila);
    }
}
