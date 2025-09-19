#ifndef FILACLIENTES_H
#define FILACLIENTES_H


#include <iostream>
#include <queue>
#include "Cliente.h"

class FilaClientes{
    private: std::queue <Cliente> fila;

    public:
void entrarNaFila(const Cliente& cliente);

Cliente proximoCliente();

bool filaVazia() const;

size_t tamanhoFila() const;
};

#endif



