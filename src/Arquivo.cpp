#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Arquivo.hpp"

Arquivo::Arquivo()
    : nomeArquivo("dados.txt") {
}

bool Arquivo::salvar(const Loja& loja, const Personagem& personagem) const {
    std::ofstream out(nomeArquivo.c_str());
    if (!out.is_open()) {
        return false;
    }

    out << "[LOJA]" << std::endl;
    const std::map<std::string, Item>& itensLoja = loja.itens();
    std::map<std::string, Item>::const_iterator itL;
    for (itL = itensLoja.begin(); itL != itensLoja.end(); ++itL) {
        const Item& item = itL->second;
        out << item.getNome() << "|"
            << item.getPreco() << "|"
            << item.getPeso() << "|"
            << item.getQuantidade() << std::endl;
    }

    out << "[PERSONAGEM]" << std::endl;
    out << personagem.getNome() << "|"
        << personagem.dinheiro() << "|"
        << personagem.pesoMax() << std::endl;

    out << "[MOCHILA]" << std::endl;
    const Inventario& mochila = personagem.mochila();
    if (!mochila.vazio()) {
        const std::list<Item>& listaM = mochila.lista();
        std::list<Item>::const_iterator itM;
        for (itM = listaM.begin(); itM != listaM.end(); ++itM) {
            const Item& item = *itM;
            out << item.getNome() << "|"
                << item.getPreco() << "|"
                << item.getPeso() << "|"
                << item.getQuantidade() << std::endl;
        }
    }

    out.close();
    return true;
}

bool Arquivo::carregar(Loja& loja, Personagem& personagem) {
    std::ifstream in(nomeArquivo.c_str());
    if (!in.is_open()) {
        return false;
    }

    loja.limpar();

    std::string linha;
    std::string secao = "";

    while (std::getline(in, linha)) {
        if (linha == "[LOJA]") {
            secao = "LOJA";
            continue;
        }
        if (linha == "[PERSONAGEM]") {
            secao = "PERSONAGEM";
            continue;
        }
        if (linha == "[MOCHILA]") {
            secao = "MOCHILA";
            continue;
        }
        if (linha.empty()) {
            continue;
        }

        if (secao == "LOJA") {
            std::stringstream ss(linha);
            std::string nome, precoStr, pesoStr, qtdStr;
            std::getline(ss, nome, '|');
            std::getline(ss, precoStr, '|');
            std::getline(ss, pesoStr, '|');
            std::getline(ss, qtdStr, '|');

            int preco = atoi(precoStr.c_str());
            double peso = atof(pesoStr.c_str());
            int qtd = atoi(qtdStr.c_str());

            loja.adicionarItem(Item(nome, preco, peso, qtd));
            continue;
        }

        if (secao == "PERSONAGEM") {
            std::stringstream ss(linha);
            std::string nome, dinheiroStr, pesoMaxStr;
            std::getline(ss, nome, '|');
            std::getline(ss, dinheiroStr, '|');
            std::getline(ss, pesoMaxStr, '|');

            int dinheiro = atoi(dinheiroStr.c_str());
            double pesoMax = atof(pesoMaxStr.c_str());
            personagem.setDinheiro(dinheiro);
            personagem.setPesoMax(pesoMax);
            (void)nome;
            continue;
        }

        if (secao == "MOCHILA") {
            std::stringstream ss(linha);
            std::string nome, precoStr, pesoStr, qtdStr;
            std::getline(ss, nome, '|');
            std::getline(ss, precoStr, '|');
            std::getline(ss, pesoStr, '|');
            std::getline(ss, qtdStr, '|');

            int preco = atoi(precoStr.c_str());
            double peso = atof(pesoStr.c_str());
            int qtd = atoi(qtdStr.c_str());

            if (qtd > 0) {
                Inventario temp;
                for (int i = 0; i < qtd; ++i) {
                    temp.adicionar(Item(nome, preco, peso, 1));
                }
                const std::list<Item>& listaTemp = temp.lista();
                std::list<Item>::const_iterator itT;
                for (itT = listaTemp.begin(); itT != listaTemp.end(); ++itT) {
                    personagem.mochila().adicionar(*itT);
                }
            }
            continue;
        }
    }

    in.close();
    return true;
}
