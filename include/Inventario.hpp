#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include <list>
#include <string>
#include "Item.hpp"

class Inventario {
public:
    void adicionar(const Item& item);
    bool remover1(const std::string& nome);
    double pesoTotal() const;
    bool vazio() const;

    const std::list<Item>& lista() const;

private:
    std::list<Item> mochila;
};

#endif
