#include <iostream>
#include <map>
#include <string>
#include "Item.hpp"
#include "Loja.hpp"

using namespace std;

void mostrarLoja(const Loja& loja) {
    const map<string, Item>& itens = loja.itens();
    if (itens.empty()) {
        cout << "A loja esta vazia." << endl;
        return;
    }
    cout << "--- Catalogo da Loja ---" << endl;
    map<string, Item>::const_iterator it;
    for (it = itens.begin(); it != itens.end(); ++it) {
        const Item& item = it->second;
        cout << item.getNome()
             << " | Preco: " << item.getPreco()
             << " | Peso: " << item.getPeso()
             << " | Estoque: " << item.getQuantidade() << endl;
    }
}

void mostrarMenu() {
    cout << "1 - Ver Loja" << endl;
    cout << "6 - Sair" << endl;
}

int lerOpcao() {
    int opcao;
    if (!(cin >> opcao)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    return opcao;
}

int main() {
    Loja loja;

    cout << "Bem-vindo! Dinheiro: 200 | Peso: 0/50kg" << endl;

    bool sair = false;
    while (!sair) {
        mostrarMenu();
        cout << "Escolha: ";
        int opcao = lerOpcao();

        if (opcao == 1) {
            mostrarLoja(loja);
        } else if (opcao == 6) {
            sair = true;
        } else {
            cout << "Opcao invalida" << endl;
        }
    }

    return 0;
}
