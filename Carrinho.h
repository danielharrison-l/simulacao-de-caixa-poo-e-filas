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

    void deletarOuAdicionarAoCarrinho(){
        // bool funcinando;
        int escolha;
        int quantidade;
        int indice;

        cout << "Escolha um produto selecionando seu numero:";
        cin >> indice;
        cout <<  "Voce dejesa retirar ou adicionar itens do produto?\n" << "1 - Adicionar\n2 - Retirar\nEscolha: ";
        cin >> escolha;
        // while(!funcinando){
            if(escolha == 1){

                cout << "Digite quanto do produto deseja adicionar: ";
                cin >> quantidade;

                if(indice - 1 >= 0 && indice - 1 < (int)carrinhoDeCompras.size()){
                    auto& produto = carrinhoDeCompras[indice - 1];
                        if(holds_alternative<int>(produto[2])) {
                            int totalDeProdutos = get<int>(produto[2]);
                            totalDeProdutos += quantidade;
                            produto[2] = totalDeProdutos;
                            cout << "Quantidade atualizada!" << endl;
                            // funcinando = false;
                            
                        }   
                }

            }
            else if(escolha == 2){
                cout << "Digite quanto do produto deseja retirar: ";
                cin >> quantidade;

                if(indice - 1 >= 0 && indice - 1 < (int)carrinhoDeCompras.size()){
                    auto& produto = carrinhoDeCompras[indice - 1];

                    if(holds_alternative<int>(produto[2])){
                        int totalDeprodutos = get<int>(produto[2]);

                        if(totalDeprodutos > quantidade){
                            totalDeprodutos -= quantidade;
                            produto[2] = totalDeprodutos;
                            cout << "Lista atualizada!" << endl;
                        }

                        else if(totalDeprodutos <= quantidade){
                            carrinhoDeCompras.erase(carrinhoDeCompras.begin() + indice - 1);
                            cout << "Voce retirou um item do carrinho" << endl;
                        }
                    }
                }
            }
            else{
                cout << "Escolha uma opção válida";
            }
        // }
    }
    
    void imprimirLista() const {
        int indice = 1;
        cout << "--------------------------Produtos no Carrinho--------------------------" << endl;
        cout << "Produto | Preco | Quantidade " << endl;
            for(const auto& produto : carrinhoDeCompras){
                cout << indice << ". ";
                for(const auto& item : produto) {
                    visit([](auto&& resultado){
                        cout << resultado << " | ";
                    },item);
                }
                cout << endl;
                indice++;
            }
             cout << "----------------------------------------------------------------------" << endl;
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