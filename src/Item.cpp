#include "Item.hpp"

Item::Item()
    : nome(""), preco(0), peso(0.0), quantidade(0) {
}

Item::Item(std::string nome, int preco, double peso, int quantidade)
    : nome(nome), preco(preco), peso(peso), quantidade(quantidade) {
}

std::string Item::getNome() const {
    return nome;
}

int Item::getPreco() const {
    return preco;
}

double Item::getPeso() const {
    return peso;
}

int Item::getQuantidade() const {
    return quantidade;
}

void Item::setQuantidade(int quantidade) {
    this->quantidade = quantidade;
}

bool Item::operator==(const Item& outro) const {
    return nome == outro.nome;
}
