#include "../include/GeradorClientes.hpp"
#include <iostream>

GeradorClientes::GeradorClientes(std::vector<Produto> *listaProdutos)
    : produtos(listaProdutos), rng(std::random_device{}()), proximoId(1),
      ultimaGeracao(std::chrono::steady_clock::now()),
      intervaloChegada(10, 30),
      qtdProdutosDist(1, 8),
      nomeDist(0, 0), sobrenomeDist(0, 0), produtoDist(0, 0)
{
    inicializarNomes();

    if (produtos && !produtos->empty())
    {
        produtoDist = std::uniform_int_distribution<int>(0, produtos->size() - 1);
    }
}

void GeradorClientes::inicializarNomes()
{
    nomes = {
        "Ana", "Bruno", "Carla", "Diego", "Elena", "Felipe", "Gabriela", "Hugo",
        "Isabela", "João", "Karina", "Lucas", "Maria", "Nicolas", "Olivia", "Pedro",
        "Rafaela", "Samuel", "Tatiana", "Victor", "Yasmin", "Zeca", "Amanda", "Carlos",
        "Daniela", "Eduardo", "Fernanda", "Gustavo", "Helena", "Igor", "Julia", "Kevin",
        "Larissa", "Marcos", "Natalia", "Otavio", "Patricia", "Ricardo", "Sabrina", "Thiago"};

    sobrenomes = {
        "Silva", "Santos", "Oliveira", "Souza", "Rodrigues", "Ferreira", "Alves", "Pereira",
        "Lima", "Gomes", "Costa", "Ribeiro", "Martins", "Carvalho", "Almeida", "Lopes",
        "Soares", "Fernandes", "Vieira", "Barbosa", "Rocha", "Dias", "Monteiro", "Cardoso",
        "Reis", "Araujo", "Cavalcanti", "Nascimento", "Moreira", "Campos", "Freitas", "Cunha"};

    nomeDist = std::uniform_int_distribution<int>(0, nomes.size() - 1);
    sobrenomeDist = std::uniform_int_distribution<int>(0, sobrenomes.size() - 1);
}

std::string GeradorClientes::gerarNomeAleatorio()
{
    return nomes[nomeDist(rng)] + " " + sobrenomes[sobrenomeDist(rng)];
}

Cliente GeradorClientes::criarClienteAleatorio()
{
    Cliente cliente(proximoId++, gerarNomeAleatorio());

    if (!produtos || produtos->empty())
    {
        return cliente;
    }

    int qtdProdutos = qtdProdutosDist(rng);

    for (int i = 0; i < qtdProdutos; ++i)
    {
        const auto &produto = (*produtos)[produtoDist(rng)];
        cliente.getCarrinho().adicionarProduto(produto);
    }

    return cliente;
}

bool GeradorClientes::deveGerarNovoCliente()
{
    auto agora = std::chrono::steady_clock::now();
    auto tempoDecorrido = std::chrono::duration_cast<std::chrono::seconds>(agora - ultimaGeracao).count();

    int intervaloNecessario = intervaloChegada(rng);

    if (tempoDecorrido >= intervaloNecessario)
    {
        ultimaGeracao = agora;
        return true;
    }

    return false;
}

void GeradorClientes::adicionarClienteSeNecessario(FilaClientes &fila)
{
    if (deveGerarNovoCliente())
    {
        Cliente novoCliente = criarClienteAleatorio();
        fila.adicionarCliente(novoCliente);

        std::cout << "\n🚶 Novo cliente chegou: " << novoCliente.getNome()
                  << " (" << novoCliente.getCarrinho().getProdutos().size() << " itens)" << std::endl;
        std::cout << "👥 Clientes na fila: " << fila.tamanho() << std::endl;
    }
}

void GeradorClientes::setIntervaloChegada(int minSegundos, int maxSegundos)
{
    intervaloChegada = std::uniform_int_distribution<int>(minSegundos, maxSegundos);
}

void GeradorClientes::setQuantidadeProdutos(int min, int max)
{
    qtdProdutosDist = std::uniform_int_distribution<int>(min, max);
}

int GeradorClientes::getTotalClientesGerados() const
{
    return proximoId - 1;
}
