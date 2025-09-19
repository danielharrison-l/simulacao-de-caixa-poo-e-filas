#ifndef CAIXA_INTERATIVO_HPP
#define CAIXA_INTERATIVO_HPP

#include "Caixa.hpp"
#include "FilaClientes.hpp"
#include "Produto.hpp"
#include <vector>
#include <string>

class CaixaInterativo
{
private:
    Caixa caixa;
    FilaClientes *fila;
    std::vector<Produto> *produtos;
    Cliente *clienteAtual;
    int vendasRealizadas;
    double totalVendido;

    void limparTela();
    void mostrarCabecalho();
    void mostrarEstatisticas();

public:
    CaixaInterativo(const std::string &nomeCaixa, FilaClientes *filaClientes, std::vector<Produto> *listaProdutos);

    void iniciarSimulacao();
    void mostrarMenu();
    int obterOpcao();

    void proximoCliente();
    void visualizarFila();
    void adicionarProduto();
    void removerProduto();
    void finalizarCompra();
    void mostrarRelatorio();
    void mostrarCarrinhoAtual();

    bool temClienteAtual() const;
    bool filaVazia() const;
};

#endif
