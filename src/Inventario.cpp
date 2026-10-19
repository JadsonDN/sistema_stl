#include <algorithm>
#include "Inventario.hpp"

void Inventario::adicionar(const Item& item) {
    std::list<Item>::iterator it = std::find(mochila.begin(), mochila.end(), item);
    if (it != mochila.end()) {
        it->setQuantidade(it->getQuantidade() + item.getQuantidade());
        return;
    }
    mochila.push_back(item);
}

bool Inventario::remover1(const std::string& nome) {
    Item fantasma(nome, 0, 0.0, 0);
    std::list<Item>::iterator it = std::find(mochila.begin(), mochila.end(), fantasma);
    if (it == mochila.end()) {
        return false;
    }
    int nova = it->getQuantidade() - 1;
    if (nova <= 0) {
        mochila.erase(it);
        return true;
    }
    it->setQuantidade(nova);
    return true;
}

double Inventario::pesoTotal() const {
    double total = 0.0;
    std::list<Item>::const_iterator it;
    for (it = mochila.begin(); it != mochila.end(); ++it) {
        total += it->getPeso() * it->getQuantidade();
    }
    return total;
}

bool Inventario::vazio() const {
    return mochila.empty();
}

const std::list<Item>& Inventario::lista() const {
    return mochila;
}
