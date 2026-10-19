#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>
#include "Inventario.hpp"
#include "Loja.hpp"

enum ResultadoCompra {
    COMPRA_OK,
    ITEM_NAO_ENCONTRADO,
    SALDO_INSUFICIENTE,
    PESO_EXCEDIDO
};

class Personagem {
public:
    Personagem(std::string nome, int dinheiro, double pesoMax);

    std::string getNome() const;
    int dinheiro() const;
    double pesoMax() const;
    double pesoAtual() const;

    ResultadoCompra comprar(Loja& loja, const std::string& nome);
    bool descartar(const std::string& nome);

    const Inventario& mochila() const;

private:
    std::string nome;
    int dinheiroAtual;
    double pesoMaximo;
    Inventario inventario;
};

#endif
