#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <string>
#include "Loja.hpp"
#include "Personagem.hpp"

class Arquivo {
public:
    Arquivo();

    bool salvar(const Loja& loja, const Personagem& personagem) const;
    bool carregar(Loja& loja, Personagem& personagem);

private:
    std::string nomeArquivo;
};

#endif
