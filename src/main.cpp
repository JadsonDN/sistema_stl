#include <iostream>
#include "Item.hpp"

using namespace std;

int main() {
    Item exemplo("Espada", 150, 3.5, 1);

    cout << "Nome: " << exemplo.getNome() << endl;
    cout << "Preco: " << exemplo.getPreco() << endl;
    cout << "Peso: " << exemplo.getPeso() << endl;
    cout << "Quantidade: " << exemplo.getQuantidade() << endl;

    return 0;
}
