#ifndef GERADOR_CLIENTES_HPP
#define GERADOR_CLIENTES_HPP

#include "Cliente.hpp"
#include "Produto.hpp"
#include "FilaClientes.hpp"
#include <vector>
#include <string>
#include <random>
#include <chrono>

class GeradorClientes
{
private:
    std::vector<std::string> nomes;
    std::vector<std::string> sobrenomes;
    std::vector<Produto> *produtos;
    std::mt19937 rng;
    int proximoId;

    std::chrono::steady_clock::time_point ultimaGeracao;
    std::uniform_int_distribution<int> intervaloChegada;
    std::uniform_int_distribution<int> qtdProdutosDist;
    std::uniform_int_distribution<int> nomeDist;
    std::uniform_int_distribution<int> sobrenomeDist;
    std::uniform_int_distribution<int> produtoDist;

    void inicializarNomes();
    std::string gerarNomeAleatorio();

public:
    GeradorClientes(std::vector<Produto> *listaProdutos);

    Cliente criarClienteAleatorio();
    bool deveGerarNovoCliente();
    void adicionarClienteSeNecessario(FilaClientes &fila);

    void setIntervaloChegada(int minSegundos, int maxSegundos);
    void setQuantidadeProdutos(int min, int max);

    int getTotalClientesGerados() const;
};

#endif
