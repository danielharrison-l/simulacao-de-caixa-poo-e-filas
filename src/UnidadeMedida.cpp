#include "../include/UnidadeMedida.hpp"
#include <iomanip>
#include <sstream>
#include <algorithm>

std::string UtilUnidade::obterNomeUnidade(UnidadeMedida unidade)
{
    switch (unidade)
    {
    case UnidadeMedida::GRAMAS:
        return "Gramas";
    case UnidadeMedida::QUILOGRAMAS:
        return "Quilogramas";
    case UnidadeMedida::MILILITROS:
        return "Mililitros";
    case UnidadeMedida::LITROS:
        return "Litros";
    case UnidadeMedida::UNIDADES:
        return "Unidades";
    default:
        return "Desconhecido";
    }
}

std::string UtilUnidade::obterSimbolo(UnidadeMedida unidade)
{
    switch (unidade)
    {
    case UnidadeMedida::GRAMAS:
        return "g";
    case UnidadeMedida::QUILOGRAMAS:
        return "kg";
    case UnidadeMedida::MILILITROS:
        return "ml";
    case UnidadeMedida::LITROS:
        return "L";
    case UnidadeMedida::UNIDADES:
        return "un";
    default:
        return "?";
    }
}

std::string UtilUnidade::formatarQuantidade(double quantidade, UnidadeMedida unidade)
{
    std::ostringstream oss;

    switch (unidade)
    {
    case UnidadeMedida::GRAMAS:
        if (quantidade >= 1000.0)
        {
            oss << std::fixed << std::setprecision(2) << (quantidade / 1000.0) << "kg";
        }
        else
        {
            oss << std::fixed << std::setprecision(0) << quantidade << "g";
        }
        break;

    case UnidadeMedida::QUILOGRAMAS:
        oss << std::fixed << std::setprecision(2) << quantidade << "kg";
        break;

    case UnidadeMedida::MILILITROS:
        if (quantidade >= 1000.0)
        {
            oss << std::fixed << std::setprecision(2) << (quantidade / 1000.0) << "L";
        }
        else
        {
            oss << std::fixed << std::setprecision(0) << quantidade << "ml";
        }
        break;

    case UnidadeMedida::LITROS:
        oss << std::fixed << std::setprecision(2) << quantidade << "L";
        break;

    case UnidadeMedida::UNIDADES:
        oss << std::fixed << std::setprecision(0) << quantidade << "un";
        break;

    default:
        oss << quantidade << "?";
        break;
    }

    return oss.str();
}

UnidadeMedida UtilUnidade::determinarUnidadeAutomatica(double quantidade, const std::string &nomeCategoria)
{
    std::string categoria = nomeCategoria;

    for (auto &c : categoria)
    {
        c = std::tolower(c);
    }

    if (categoria.find("bebida") != std::string::npos ||
        categoria.find("laticinios") != std::string::npos ||
        categoria.find("oleo") != std::string::npos)
    {
        return quantidade >= 1000.0 ? UnidadeMedida::LITROS : UnidadeMedida::MILILITROS;
    }

    if (categoria.find("higiene") != std::string::npos ||
        categoria.find("padaria") != std::string::npos)
    {
        return UnidadeMedida::UNIDADES;
    }

    return quantidade >= 1000.0 ? UnidadeMedida::QUILOGRAMAS : UnidadeMedida::GRAMAS;
}

double UtilUnidade::converterParaUnidadeBase(double quantidade, UnidadeMedida unidade)
{
    switch (unidade)
    {
    case UnidadeMedida::QUILOGRAMAS:
        return quantidade * 1000.0;
    case UnidadeMedida::LITROS:
        return quantidade * 1000.0;
    case UnidadeMedida::GRAMAS:
    case UnidadeMedida::MILILITROS:
    case UnidadeMedida::UNIDADES:
    default:
        return quantidade;
    }
}

bool UtilUnidade::isPeso(UnidadeMedida unidade)
{
    return unidade == UnidadeMedida::GRAMAS || unidade == UnidadeMedida::QUILOGRAMAS;
}

bool UtilUnidade::isVolume(UnidadeMedida unidade)
{
    return unidade == UnidadeMedida::MILILITROS || unidade == UnidadeMedida::LITROS;
}

UnidadeMedida UtilUnidade::stringParaUnidade(const std::string &unidadeStr)
{
    std::string str = unidadeStr;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (str == "gramas" || str == "g")
        return UnidadeMedida::GRAMAS;
    if (str == "quilogramas" || str == "kg")
        return UnidadeMedida::QUILOGRAMAS;
    if (str == "mililitros" || str == "ml")
        return UnidadeMedida::MILILITROS;
    if (str == "litros" || str == "l")
        return UnidadeMedida::LITROS;
    if (str == "unidades" || str == "un")
        return UnidadeMedida::UNIDADES;

    return UnidadeMedida::UNIDADES;
}
