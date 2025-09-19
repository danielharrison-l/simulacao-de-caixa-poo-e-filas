#ifndef FORMA_PAGAMENTO_HPP
#define FORMA_PAGAMENTO_HPP

#include <string>
#include <random>

enum class TipoPagamento
{
    DINHEIRO = 1,
    CARTAO_DEBITO = 2,
    CARTAO_CREDITO = 3,
    PIX = 4
};

struct ResultadoPagamento
{
    bool sucesso;
    std::string mensagem;
    double troco;
    
    ResultadoPagamento(bool s, const std::string& msg, double t = 0.0)
        : sucesso(s), mensagem(msg), troco(t) {}
};

class ProcessadorPagamento
{
private:
    std::mt19937 rng;
    std::uniform_real_distribution<double> chanceSucesso;
    
public:
    ProcessadorPagamento();
    
    ResultadoPagamento processarDinheiro(double valorTotal, double valorPago);
    ResultadoPagamento processarCartaoDebito(double valorTotal);
    ResultadoPagamento processarCartaoCredito(double valorTotal);
    ResultadoPagamento processarPix(double valorTotal);
    
    std::string obterNomePagamento(TipoPagamento tipo);
    std::string obterEmojiPagamento(TipoPagamento tipo);
};

#endif
