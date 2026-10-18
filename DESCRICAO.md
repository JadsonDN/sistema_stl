# Descrição do sistema

Escreva este arquivo sem IA, antes de qualquer código. Apague as instruções
em itálico quando preencher.


## Nome e ideia

O meu projeto é baseano no inventario de rpg, contudo sera feito com a interação com um novo elemento, a loja.

## O que o sistema guarda

o sistema guardara:
itens: ele sera oq guarda os dados, como peso, preço e quantidade.
loja: o "catalogo" de todos os itens disponives e seus estoques/quantidades.
Personagem: o seu nome, sua quantidade de peso macima, e seu dinheiro.
Inventario: a lista de todos os itens que o personagem possue.

## O que dá para fazer

.Ver o catálogo da loja (lista os itens, preços e seus pesos).
.Comprar um item da loja (tira do estoque da loja e põe no inventário). 
.Ver a mochila (lista os itens guardados e o peso total atual).
.Usar/Descartar um item do inventário (diminui a quantidade na mochila).

## Regras
.A loja utiliza um map<string, Item> para armazenar os produtos, permitindo buscas pelo nome.
.O inventario utiliza uma list<Item> para gerenciar o que o personagem carrega.
.Itens iguais no inventário se acumulam.
.O sistema usa a função find() para verificar se o item já existe na lista.
.O personagem não pode comprar um item se não tiver dinheiro suficiente ou se o peso do item ultrapassar a sua capacidade de carga máxima.
.Quando a quantidade de um item na loja chega a zero, ele é removido do estoque.

## Quando algo dá errado

.Se digitar o nome de um item que não existe na loja: o sistema avisa que o item não foi encontrado.
.Se tentar comprar e o personagem não tiver dinheiro: o sistema exibe "Saldo insuficiente".
.Se tentar comprar e a mochila ficar pesada: o sistema exibe "Peso limite excedido".
.e Se pedir para ver a mochila e não houver itens: o sistema avisa que o inventário está vazio.   

## Classes que eu imagino

.Item: Guarda os dados básicos (nome, preço, peso, quantidade), e tera a sobrecarga do operator== para o find() funcionar.
.Inventario: Guarda a list de itens do personagem, verifica os limites de peso e agrupa itens iguais.
.Personagem: Guarda os dados do heroi, dinheiro, nome, e possui um Inventario.
.Loja: Guarda o map de itens que estao a venda.

## Exemplo de uso


Bem-vindo! Dinheiro: 200 | Peso: 0/50kg
Ver Loja
Comprar Item
Ver Mochila
Escolha: 2
Qual item deseja comprar? Espada
Sucesso! Espada comprada por 150 moedas.