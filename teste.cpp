#include <iostream>
#include <vector>
#include <variant>
#include <string>
using namespace std;

int main() {
    // Vector que pode ter int, double ou string
    vector<variant<int, double,string>> dados;

    dados.push_back("Olá C++");             // int
    dados.push_back(3.14);           // double
    dados.push_back(42);      // string

    // Acessando com std::visit
    for (auto& item : dados) {
        visit([](auto&& legal) {
            cout << legal << endl;
        }, item);
    }

    return 0;
}