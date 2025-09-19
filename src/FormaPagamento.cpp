#include "../include/FormaPagamento.hpp"
#include <iostream>
#include <iomanip>

ProcessadorPagamento::ProcessadorPagamento()
    : rng(std::random_device{}()), chanceSucesso(0.0, 1.0)
{
}

ResultadoPagamento ProcessadorPagamento::processarDinheiro(double valorTotal, double valorPago)
{
    if (valorPago < valorTotal)
    {
        return ResultadoPagamento(false, "Valor insuficiente! Faltam R$ " +
                                             std::to_string(valorTotal - valorPago));
    }

    double troco = valorPago - valorTotal;

    if (troco > 100.0)
    {
        if (chanceSucesso(rng) < 0.1)
        {
            return ResultadoPagamento(false, "Não temos troco para essa quantia. Tem um valor menor?");
        }
    }

    std::string mensagem = "Pagamento em dinheiro aprovado!";
    if (troco > 0)
    {
        mensagem += " Troco: R$ " + std::to_string(troco);
    }

    return ResultadoPagamento(true, mensagem, troco);
}

ResultadoPagamento ProcessadorPagamento::processarCartaoDebito(double valorTotal)
{
    std::cout << "Processando cartão de débito..." << std::endl;

    if (chanceSucesso(rng) < 0.95)
    {
        return ResultadoPagamento(true, "Pagamento no débito aprovado!");
    }
    else
    {
        double tipoErro = chanceSucesso(rng);
        if (tipoErro < 0.4)
        {
            return ResultadoPagamento(false, "Cartão recusado - saldo insuficiente");
        }
        else if (tipoErro < 0.7)
        {
            return ResultadoPagamento(false, "Erro na comunicação com o banco. Tente novamente");
        }
        else
        {
            return ResultadoPagamento(false, "Cartão bloqueado. Entre em contato com seu banco");
        }
    }
}

ResultadoPagamento ProcessadorPagamento::processarCartaoCredito(double valorTotal)
{
    std::cout << "Processando cartão de crédito..." << std::endl;

    if (chanceSucesso(rng) < 0.92)
    {
        return ResultadoPagamento(true, "Pagamento no crédito aprovado!");
    }
    else
    {
        double tipoErro = chanceSucesso(rng);
        if (tipoErro < 0.3)
        {
            return ResultadoPagamento(false, "Cartão recusado - limite insuficiente");
        }
        else if (tipoErro < 0.6)
        {
            return ResultadoPagamento(false, "Transação negada pela operadora");
        }
        else if (tipoErro < 0.8)
        {
            return ResultadoPagamento(false, "Erro na comunicação. Tente novamente");
        }
        else
        {
            return ResultadoPagamento(false, "Cartão vencido ou inválido");
        }
    }
}

ResultadoPagamento ProcessadorPagamento::processarPix(double valorTotal)
{
    std::cout << "Gerando QR Code do PIX..." << std::endl;
    std::cout << "Aguardando confirmação do cliente..." << std::endl;

    if (chanceSucesso(rng) < 0.98)
    {
        return ResultadoPagamento(true, "PIX recebido com sucesso!");
    }
    else
    {
        double tipoErro = chanceSucesso(rng);
        if (tipoErro < 0.5)
        {
            return ResultadoPagamento(false, "PIX cancelado pelo cliente");
        }
        else
        {
            return ResultadoPagamento(false, "Erro na conexão. Tente novamente");
        }
    }
}

std::string ProcessadorPagamento::obterNomePagamento(TipoPagamento tipo)
{
    switch (tipo)
    {
    case TipoPagamento::DINHEIRO:
        return "Dinheiro";
    case TipoPagamento::CARTAO_DEBITO:
        return "Cartão de Débito";
    case TipoPagamento::CARTAO_CREDITO:
        return "Cartão de Crédito";
    case TipoPagamento::PIX:
        return "PIX";
    default:
        return "Desconhecido";
    }
}

std::string ProcessadorPagamento::obterEmojiPagamento(TipoPagamento tipo)
{
    switch (tipo)
    {
    case TipoPagamento::DINHEIRO:
        return "💵";
    case TipoPagamento::CARTAO_DEBITO:
        return "💳";
    case TipoPagamento::CARTAO_CREDITO:
        return "💳";
    case TipoPagamento::PIX:
        return "📱";
    default:
        return "❓";
    }
}
