#include "Loja.hpp"

Loja::Loja() {
    adicionarItem(Item("Espada", 150, 3.5, 2));
    adicionarItem(Item("Pocao", 20, 0.5, 5));
    adicionarItem(Item("Escudo", 80, 5.0, 3));
    adicionarItem(Item("Elmo", 60, 2.0, 4));
    adicionarItem(Item("Arco", 100, 1.5, 2));
    adicionarItem(Item("Armadura Pesada", 200, 60.0, 1));
}

bool Loja::existe(const std::string& nome) const {
    return estoque.find(nome) != estoque.end();
}

bool Loja::buscar(const std::string& nome, Item& saida) const {
    std::map<std::string, Item>::const_iterator it = estoque.find(nome);
    if (it == estoque.end()) {
        return false;
    }
    saida = it->second;
    return true;
}

int Loja::quantidadeDe(const std::string& nome) const {
    std::map<std::string, Item>::const_iterator it = estoque.find(nome);
    if (it == estoque.end()) {
        return 0;
    }
    return it->second.getQuantidade();
}

bool Loja::baixarEstoque(const std::string& nome) {
    std::map<std::string, Item>::iterator it = estoque.find(nome);
    if (it == estoque.end()) {
        return false;
    }
    int nova = it->second.getQuantidade() - 1;
    if (nova <= 0) {
        estoque.erase(it);
        return true;
    }
    it->second.setQuantidade(nova);
    return true;
}

void Loja::removerItem(const std::string& nome) {
    estoque.erase(nome);
}

void Loja::aumentarEstoque(const std::string& nome, int quantidade) {
    std::map<std::string, Item>::iterator it = estoque.find(nome);
    if (it != estoque.end() && quantidade > 0) {
        it->second.setQuantidade(it->second.getQuantidade() + quantidade);
    }
}

void Loja::adicionarItem(const Item& novo) {
    estoque[novo.getNome()] = novo;
}

const std::map<std::string, Item>& Loja::itens() const {
    return estoque;
}

void Loja::limpar() {
    estoque.clear();
}
