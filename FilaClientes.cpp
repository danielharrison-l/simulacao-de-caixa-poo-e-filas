#include "FilaClientes.h"
#include <iostream>
#include <stdexcept>

using namespace std; //evita ter que escrever "std:"

void FilaClientes::entrarNaFila( const Cliente& cliente){
    fila.push(cliente);
    cout<< "cliente"<< cliente.getId()<< "Entrou na fila"<< "Posição na fila:"<< fila.size()<< endl;
}


Cliente FilaClientes:: proximoCliente(){
    if (filaVazia()){
    throw runtime_error("Fila vazia");

}

Cliente proximo = fila.front();
fila.pop();
    cout <<"Cliente: "<< proximo.getId()<< " foi atendido"<< endl;
}

bool FilaClientes::filaVazia() const{
    return fila.empty();
}

size_t FilaClientes::tamanhoFila() const{
    return fila.size();
}
