#ifndef ArquivoIO_HPP
#define ArquivoIO_HPP

#include <vector>
#include <string>

class ArquivoIO
{
public:
  static std::vector<std::string> carregarLinhas(const std::string &caminho);
};

#endif
