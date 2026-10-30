# Nome do sistema

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Uma frase dizendo o que o sistema faz. A descrição completa está em
`DESCRICAO.md`.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```
para compilar os testes, so trocar o numero do cerario:
```bash
./sistema < exemplos/cenario1.txt
```
Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

## Onde uso a STL

Escreva esta seção sem IA. Para cada container ou algoritmo da STL que o
sistema usa: em que classe ele está, o que guarda, e por que você escolheu
ele e não outro.

| Onde | O quê | Por quê |
| loja | map<string, Item> |para facilitar a busca diretamente pelo nome do item|
|Inventario |list<Item>|para ser mais facil tirar e colocar os itens sem peocupar em os itens seren copiados e andarem |
|Inventario com o adicionar e remover1|std::find|verifica se o item ja existe na lista para entao adicionar ou remover |
|Item|operator==|ajuda o std::find a funcionar|
## Como usei a IA

Escreva com as suas palavras:

- Modelo usado: opencode big pickle
- Um pedido que deu certo, e por que você acha que deu certo: a implementaçao do dados.txt para salvar os arquivos acredito que tenha sido muito bem aplicada funcionando muito bem logo de cara.
- Um pedido que deu errado, o que veio errado e como você mudou o pedido: toda a parte da interface, mesmo eu pedindo de um geito que eu achava que estava bem explicado, ela foi gerada com diversos erros de qualidade de vida
- Uma coisa que a IA sugeriu e você recusou, e por quê: 
