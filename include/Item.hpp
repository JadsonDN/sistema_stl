#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
public:
    Item();
    Item(std::string nome, int preco, double peso, int quantidade);

    std::string getNome() const;
    int getPreco() const;
    double getPeso() const;
    int getQuantidade() const;
    void setQuantidade(int quantidade);

    bool operator==(const Item& outro) const;

private:
    std::string nome;
    int preco;
    double peso;
    int quantidade;
};

#endif
