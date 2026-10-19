#include "Adm.hpp"

Adm::Adm()
    : senha("123456") {
}

bool Adm::autenticar(const std::string& senhaDigitada) const {
    return senhaDigitada == senha;
}

bool Adm::adicionar(Loja& loja, const Item& novo) {
    if (novo.getQuantidade() <= 0) {
        return false;
    }
    if (loja.existe(novo.getNome())) {
        loja.aumentarEstoque(novo.getNome(), novo.getQuantidade());
        return true;
    }
    loja.adicionarItem(novo);
    return true;
}

bool Adm::tirar1(Loja& loja, const std::string& nome) {
    return loja.baixarEstoque(nome);
}

bool Adm::removerTudo(Loja& loja, const std::string& nome) {
    if (!loja.existe(nome)) {
        return false;
    }
    loja.removerItem(nome);
    return true;
}
