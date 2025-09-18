#include "ArquivoIO.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
  std::string caminho = "./data/produtos.txt";
  std::vector<std::string> linhas = ArquivoIO::carregarLinhas(caminho);

  for (const auto &linha : linhas)
  {
    std::cout << linha << std::endl;
  }

  return 0;
}
