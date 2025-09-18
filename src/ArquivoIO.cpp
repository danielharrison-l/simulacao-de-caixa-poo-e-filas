#include "ArquivoIO.hpp"
#include <fstream>
#include <iostream>

std::vector<std::string> ArquivoIO::carregarLinhas(const std::string &caminho)
{
  std::vector<std::string> linhas;
  std::ifstream arquivo(caminho);

  if (!arquivo.is_open())
  {
    std::cerr << "Erro ao abrir arquivo: " << caminho << std::endl;
    return linhas;
  }

  std::string linha;
  while (std::getline(arquivo, linha))
  {
    if (!linha.empty())
    {
      linhas.push_back(linha);
    }
  }

  return linhas;
}
