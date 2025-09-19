#ifndef UNIDADE_MEDIDA_HPP
#define UNIDADE_MEDIDA_HPP

#include <string>

enum class UnidadeMedida
{
    GRAMAS = 1,
    QUILOGRAMAS = 2,
    MILILITROS = 3,
    LITROS = 4,
    UNIDADES = 5
};

class UtilUnidade
{
public:
    static std::string obterNomeUnidade(UnidadeMedida unidade);
    static std::string obterSimbolo(UnidadeMedida unidade);
    static std::string formatarQuantidade(double quantidade, UnidadeMedida unidade);
    static UnidadeMedida determinarUnidadeAutomatica(double quantidade, const std::string &nomeCategoria);
    static UnidadeMedida stringParaUnidade(const std::string &unidadeStr);
    static double converterParaUnidadeBase(double quantidade, UnidadeMedida unidade);
    static bool isPeso(UnidadeMedida unidade);
    static bool isVolume(UnidadeMedida unidade);
};

#endif
