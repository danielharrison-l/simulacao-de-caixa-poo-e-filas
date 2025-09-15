#ifndef carrinho
#define carrinho
#include <iostream>
#include <vector>
#include <variant>
#include <string>
using namespace std;

using dados = variant<int,double,string>;

class Carrinho {
private:
    vector<vector<dados>> carrinhoDeCompras;

public:
    
    void adicionarAoCarrinho(const vector<dados>& compras){
        carrinhoDeCompras.push_back(compras);
    }

    
    
    void imprimirLista() const {
        for(const auto& produto : carrinhoDeCompras){
            for(const auto& item : produto) {
                visit([](auto&& resultado){
                    cout << resultado << " ";
                },item);
            }
            cout << endl;
        }

    }

    void imprimirPrecoEQuantidade() const{
        for(const auto& indice : carrinhoDeCompras){
            for(int index : {1,2} ){
                if(index >= 0 && (int)indice.size()){
                    visit([](auto&& valores){
                        cout << valores << " ";
                    },indice[index]);
                }
             }
             cout << endl;
            }
            
        }   
};

#endif