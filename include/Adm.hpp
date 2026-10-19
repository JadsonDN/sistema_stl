#ifndef ADM_HPP
#define ADM_HPP

#include <string>
#include "Item.hpp"
#include "Loja.hpp"

class Adm {
public:
    Adm();

    bool autenticar(const std::string& senhaDigitada) const;
    bool adicionar(Loja& loja, const Item& novo);
    bool tirar1(Loja& loja, const std::string& nome);
    bool removerTudo(Loja& loja, const std::string& nome);

private:
    std::string senha;
};

#endif
