#ifndef carrinho
#define carrinho
#include <iostream>
#include <vector>
#include <variant>
#include <string>
#include <iomanip>
using namespace std;

using dados = variant<int,double,string>;

class Carrinho {

private:
    vector<vector<dados>> carrinhoDeCompras;

public:
    
    void adicionarItemAoCarrinho( vector<dados>& compras){
        carrinhoDeCompras.push_back(compras);
    }

    void calcularPrecoTotalDoCarrinho() const {
    double valor = 0;
    double precoTotal = 0;
        for( const auto& produtos : carrinhoDeCompras){
            
            if (holds_alternative<double>(produtos[1]) && holds_alternative<int>(produtos[2])) {
                double preco = get<double>(produtos[1]);
                int quantidade = get<int>(produtos[2]);
                valor = preco * quantidade;
                precoTotal += valor;
            }
            valor = 0;
        }
        cout << "Seu preco total e de R$";
        cout << fixed << setprecision(2) << precoTotal;
    }

    

    void adicionarQuantidadeDoProdutoAoCarrinho(){
        int quantidade;
        int indiceDoProduto;

        cout << "Digite o numero do produto: ";
        cin >> indiceDoProduto;

        cout << "Digite a quantidade que deseja adicionar: ";
        cin >> quantidade;

        if(indiceDoProduto - 1 >= 0 && indiceDoProduto - 1 <= (int)carrinhoDeCompras.size()){
            auto& produto = carrinhoDeCompras[indiceDoProduto - 1];
            
            if(holds_alternative<int>(produto[2])){
                int quantidadeTotal = get<int>(produto[2]);
                if(quantidade >= 0){
                    quantidadeTotal += quantidade;
                    produto[2] = quantidadeTotal;
                    cout << "Lista Atualizada!\n";
                }
            }
        }
    }

    void retirarQuantidadeDoProdutoDoCarrinho(){
        int quantidade;
        int indiceDoProduto;

        cout << "Escolha qual produto deseja retirar a quantidade: ";
        cin >> indiceDoProduto;
        cout << "Digite quanto deseja retirar: ";
        cin >> quantidade;

        if(indiceDoProduto - 1 >= 0 && indiceDoProduto <= (int)(carrinhoDeCompras.size())){
            auto& produto = carrinhoDeCompras[indiceDoProduto - 1];
            if(holds_alternative<int>(produto[2])){
                int quantidadeTotal = get<int>(produto[2]);

                if(quantidade < quantidadeTotal){
                quantidadeTotal -= quantidade;
                produto[2] = quantidadeTotal;
                cout << "Lista Atualizada!\n";

                }

                if(quantidade == quantidadeTotal){
                    carrinhoDeCompras.erase(carrinhoDeCompras.begin() + indiceDoProduto - 1);
                    cout << "Lista Atualizada!\n";
                }
            }
        }
    }
    
    void imprimirLista() const {
        int numeroNaListaDeCompras = 1;
        cout << "-------------------------- Produtos no Carrinho --------------------------" << endl;
        cout << "| Produto | Preco | Quantidade | " << endl;
        if(carrinhoDeCompras.size() == 0){
            cout << "Seu carrinho está vazio!\n" << "Adicione alguns produtos.\n";
        }
        else{
            for(const auto& produto : carrinhoDeCompras){

                cout << numeroNaListaDeCompras << ". ";
                for(const auto& item : produto) {

                    visit([](auto&& resultado){
                        cout << resultado << " | ";
                    },item);
                }
                cout << endl;
                numeroNaListaDeCompras++;
            }
        }
             cout << "-------------------------------------------------------------------------" << endl;
    }

};

#endif