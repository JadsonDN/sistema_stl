#include <iostream>
#include <map>
#include <list>
#include <string>
#include "Item.hpp"
#include "Loja.hpp"
#include "Inventario.hpp"
#include "Personagem.hpp"

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

void mostrarMochila(const Inventario& mochila) {
    if (mochila.vazio()) {
        cout << "O inventario esta vazio." << endl;
        return;
    }
    cout << "--- Mochila ---" << endl;
    const list<Item>& itens = mochila.lista();
    list<Item>::const_iterator it;
    for (it = itens.begin(); it != itens.end(); ++it) {
        cout << it->getNome()
             << " | Quantidade: " << it->getQuantidade()
             << " | Peso: " << it->getPeso() << endl;
    }
    cout << "Peso total: " << mochila.pesoTotal() << " kg" << endl;
}

void comprarItem(Personagem& personagem, Loja& loja) {
    cout << "Qual item deseja comprar? ";
    string nome;
    cin >> nome;

    ResultadoCompra resultado = personagem.comprar(loja, nome);
    if (resultado == COMPRA_OK) {
        cout << "Sucesso! " << nome << " comprada." << endl;
    } else if (resultado == ITEM_NAO_ENCONTRADO) {
        cout << "Item nao encontrado." << endl;
    } else if (resultado == SALDO_INSUFICIENTE) {
        cout << "Saldo insuficiente." << endl;
    } else if (resultado == PESO_EXCEDIDO) {
        cout << "Peso limite excedido." << endl;
    }
}

void mostrarMenu() {
    cout << "1 - Ver Loja" << endl;
    cout << "2 - Comprar Item" << endl;
    cout << "3 - Ver Mochila" << endl;
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
    Personagem personagem("Heroi", 200, 50);

    cout << "Bem-vindo! Dinheiro: " << personagem.dinheiro()
         << " | Peso: " << personagem.pesoAtual() << "/"
         << personagem.pesoMax() << "kg" << endl;

    bool sair = false;
    while (!sair) {
        mostrarMenu();
        cout << "Escolha: ";
        int opcao = lerOpcao();

        if (opcao == 1) {
            mostrarLoja(loja);
        } else if (opcao == 2) {
            comprarItem(personagem, loja);
        } else if (opcao == 3) {
            mostrarMochila(personagem.mochila());
        } else if (opcao == 6) {
            sair = true;
        } else {
            cout << "Opcao invalida" << endl;
        }
    }

    return 0;
}
