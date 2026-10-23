#ifndef LOJA_HPP
#define LOJA_HPP

#include <map>
#include <string>
#include "Item.hpp"

class Loja {
public:
    Loja();

    bool existe(const std::string& nome) const;
    bool buscar(const std::string& nome, Item& saida) const;
    int quantidadeDe(const std::string& nome) const;
    bool baixarEstoque(const std::string& nome);
    void removerItem(const std::string& nome);
    void aumentarEstoque(const std::string& nome, int quantidade);
    void adicionarItem(const Item& novo);

    const std::map<std::string, Item>& itens() const;
    void limpar();

private:
    std::map<std::string, Item> estoque;
};

#endif
