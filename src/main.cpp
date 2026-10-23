#include <iostream>
#include <map>
#include <list>
#include <string>
#include "Item.hpp"
#include "Loja.hpp"
#include "Inventario.hpp"
#include "Personagem.hpp"
#include "Adm.hpp"

using namespace std;

int lerOpcao() {
    int opcao;
    if (!(cin >> opcao)) {
        bool eraEof = cin.eof();
        cin.clear();
        cin.ignore(1000, '\n');
        return eraEof ? -2 : -1;
    }
    cin.ignore(1000, '\n');
    return opcao;
}

bool fimDeEntrada(int resultado) {
    return resultado == -2;
}

string lerNome() {
    string nome;
    getline(cin, nome);
    return nome;
}

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

void mostrarMochila(const Inventario& mochila, int dinheiro) {
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
    cout << "Dinheiro: " << dinheiro << endl;
}

void comprarItem(Personagem& personagem, Loja& loja) {
    cout << "Qual item deseja comprar? (Dinheiro: " << personagem.dinheiro() << ")" << endl;
    string nome = lerNome();

    ResultadoCompra resultado = personagem.comprar(loja, nome);
    if (resultado == COMPRA_OK) {
        cout << "Sucesso! " << nome << " comprada." << endl;
    } else if (resultado == ITEM_NAO_ENCONTRADO) {
        cout << "Item nao encontrado." << endl;
        cout << "Voce voltou ao menu principal" << endl;
    } else if (resultado == SALDO_INSUFICIENTE) {
        cout << "Saldo insuficiente." << endl;
        cout << "Voce voltou ao menu principal" << endl;
    } else if (resultado == PESO_EXCEDIDO) {
        cout << "Peso limite excedido." << endl;
        cout << "Voce voltou ao menu principal" << endl;
    }
}

void usarDescartar(Personagem& personagem) {
    cout << "Qual item deseja usar/descartar? ";
    string nome = lerNome();

    if (personagem.descartar(nome)) {
        cout << "1 unidade de " << nome << " descartada." << endl;
    } else {
        cout << "Item nao encontrado na mochila." << endl;
        cout << "Voce voltou ao menu principal" << endl;
    }
}

void areaAdm(Adm& adm, Loja& loja) {
    cout << "Senha: ";
    string senha = lerNome();

    if (!adm.autenticar(senha)) {
        cout << "Senha incorreta." << endl;
        cout << "Voce voltou ao menu principal" << endl;
        return;
    }

    bool voltar = false;
    while (!voltar) {
        cout << "--- Area do Administrador ---" << endl;
        cout << "1 - Adicionar item" << endl;
        cout << "2 - Tirar 1 unidade" << endl;
        cout << "3 - Remover item inteiro" << endl;
        cout << "4 - Voltar" << endl;
        cout << "Escolha: ";
        int opcao = lerOpcao();

        if (opcao == 1) {
            string nome;
            int preco, quantidade;
            double peso;
            cout << "Nome: ";
            nome = lerNome();
            cout << "Preco: ";
            if (!(cin >> preco)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
            cout << "Peso: ";
            if (!(cin >> peso)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
            cout << "Quantidade inicial: ";
            if (!(cin >> quantidade)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
            cin.ignore(1000, '\n');

            if (adm.adicionar(loja, Item(nome, preco, peso, quantidade))) {
                cout << "Item " << nome << " adicionado/atualizado." << endl;
            } else {
                cout << "Quantidade invalida." << endl;
            }
        } else if (opcao == 2) {
            string nome;
            cout << "Nome do item: ";
            nome = lerNome();
            if (adm.tirar1(loja, nome)) {
                cout << "1 unidade de " << nome << " retirada." << endl;
            } else {
                cout << "Item nao encontrado na loja." << endl;
            }
        } else if (opcao == 3) {
            string nome;
            cout << "Nome do item: ";
            nome = lerNome();
            if (adm.removerTudo(loja, nome)) {
                cout << "Item " << nome << " removido do estoque." << endl;
            } else {
                cout << "Item nao encontrado na loja." << endl;
            }
        } else if (opcao == 4) {
            voltar = true;
        } else {
            cout << "Opcao invalida" << endl;
            cout << "Voce voltou ao menu" << endl;
        }
    }
}

void mostrarMenu() {
    cout << "############ Menu Principal ############" << endl;
    cout << "1 - Ver Loja" << endl;
    cout << "2 - Comprar Item" << endl;
    cout << "3 - Ver Mochila" << endl;
    cout << "4 - Usar/Descartar item" << endl;
    cout << "5 - Area do administrador" << endl;
    cout << "6 - Sair" << endl;
}

int main() {
    Loja loja;
    Personagem personagem("Heroi", 200, 50);
    Adm adm;

    cout << "Bem-vindo! Dinheiro: " << personagem.dinheiro()
         << " | Peso: " << personagem.pesoAtual() << "/"
         << personagem.pesoMax() << "kg" << endl;

    bool sair = false;
    while (!sair) {
        mostrarMenu();
        cout << "Escolha: ";
        int opcao = lerOpcao();
        if (fimDeEntrada(opcao)) {
            sair = true;
        } else if (opcao == 1) {
            mostrarLoja(loja);
        } else if (opcao == 2) {
            comprarItem(personagem, loja);
        } else if (opcao == 3) {
            mostrarMochila(personagem.mochila(), personagem.dinheiro());
        } else if (opcao == 4) {
            usarDescartar(personagem);
        } else if (opcao == 5) {
            areaAdm(adm, loja);
        } else if (opcao == 6) {
            sair = true;
        } else {
            cout << "Opcao invalida" << endl;
            cout << "Voce voltou ao menu principal" << endl;
        }
    }

    return 0;
}
