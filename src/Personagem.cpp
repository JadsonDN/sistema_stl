#include "Personagem.hpp"

Personagem::Personagem(std::string nome, int dinheiro, double pesoMax)
    : nome(nome), dinheiroAtual(dinheiro), pesoMaximo(pesoMax) {
}

std::string Personagem::getNome() const {
    return nome;
}

int Personagem::dinheiro() const {
    return dinheiroAtual;
}

double Personagem::pesoMax() const {
    return pesoMaximo;
}

double Personagem::pesoAtual() const {
    return inventario.pesoTotal();
}

ResultadoCompra Personagem::comprar(Loja& loja, const std::string& nome) {
    Item item;
    if (!loja.buscar(nome, item)) {
        return ITEM_NAO_ENCONTRADO;
    }
    if (item.getPreco() > dinheiroAtual) {
        return SALDO_INSUFICIENTE;
    }
    if (pesoAtual() + item.getPeso() > pesoMaximo) {
        return PESO_EXCEDIDO;
    }

    dinheiroAtual -= item.getPreco();
    loja.baixarEstoque(nome);
    Item comprado(item.getNome(), item.getPreco(), item.getPeso(), 1);
    inventario.adicionar(comprado);
    return COMPRA_OK;
}

bool Personagem::descartar(const std::string& nome) {
    return inventario.remover1(nome);
}

const Inventario& Personagem::mochila() const {
    return inventario;
}
