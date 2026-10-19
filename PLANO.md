# Plano de implementação

Base: `DESCRICAO.md` + as decisões combinadas na conversa (compra de 1 em 1,
descarte de 1 em 1, peso por unidade, estoque inicial fixo alterável pelo
`Adm`, senha `123456`).

## Classes

Uma classe por par de arquivos: `include/Nome.hpp` e `src/Nome.cpp`.
Nenhuma classe usa `cin`/`cout`: elas recebem dados por parâmetro e devolvem
resultado. Toda a leitura e escrita na tela fica em `src/main.cpp`.

| Classe | Arquivos | O que guarda |
| --- | --- | --- |
| `Item` | `include/Item.hpp`, `src/Item.cpp` | nome (`string`), preço (`int`), peso (`double`), quantidade (`int`) |
| `Loja` | `include/Loja.hpp`, `src/Loja.cpp` | o catálogo e o estoque |
| `Inventario` | `include/Inventario.hpp`, `src/Inventario.cpp` | os itens da mochila |
| `Personagem` | `include/Personagem.hpp`, `src/Personagem.cpp` | nome, dinheiro, peso máximo e um `Inventario` |
| `Adm` | `include/Adm.hpp`, `src/Adm.cpp` | a senha; mexe só na `Loja` |
| interface | `src/main.cpp` | menu, senhas, mensagens |

## Containers da STL e o porquê

### `map<string, Item>` na `Loja`

- A chave é o nome do item: `loja.find("Espada")` acha direto, sem percorrer
  tudo.
- O `map` já entrega as chaves em ordem alfabética, então o catálogo sai
  ordenado sem precisar de `sort`.
- Quando a quantidade chega a zero, `erase(nome)` remove o item do estoque
  em uma linha.

```cpp
map<string, Item>::iterator it = estoque.find("Espada");
if (it != estoque.end()) { /* achou */ }
```

### `list<Item>` no `Inventario`

- Inserir e remover no meio da lista não recopia os outros elementos. Num
  `vector`, tirar um item do meio faria todos os de depois andarem de lugar.
- O `find` com o `operator==` do `Item` é o que a regra do sistema pede:
  verificar se o item já existe antes de acumular.

```cpp
list<Item>::iterator it = find(mochila.begin(), mochila.end(), Item("Espada", 0, 0, 0));
// operator== compara só o nome
```

### Nada de `new`/`delete`

Os objetos ficam dentro dos containers (`map` e `list` guardam `Item` por
valor). A memória é toda da própria STL.

## Métodos de cada classe

### `Item`

```cpp
Item();                                                // construtor padrão: nome "", preço 0, peso 0, quantidade 0
Item(string nome, int preco, double peso, int quantidade);
string getNome() const;
int    getPreco() const;
double getPeso() const;
int    getQuantidade() const;
void   setQuantidade(int quantidade);
bool   operator==(const Item& outro) const;   // compara SÓ o nome
```

O construtor padrão (sem parâmetros) existe porque o checklist da aula pede
e porque o `map` pode precisar dele. Se alguém escrever
`estoque[nome] = item;`, o `operator[]` do `map` exige que a `Item` exista
sem parâmetros. O plano usa `find`/`insert`, que não pedem isso, mas ter o
`Item()` pronto evita o erro de compilação.

**Regra estrita do `operator==`:** ele deve olhar **unicamente para a
`string` nome**. Nada de comparar preço ou peso.

```cpp
bool Item::operator==(const Item& outro) const {
    return nome == outro.nome;
}
```

O motivo é o `find` do inventário: para procurar, criamos um "item
fantasma" com preço/peso/quantidade zerados
(`Item("Espada", 0, 0, 0)`). Se o `operator==` olhasse o preço, ele nunca
encontraria a Espada verdadeira (que custa 150). O `operator==` existe
justamente para o `std::find` funcionar.

### `Loja`

```cpp
Loja();                                   // monta o estoque inicial fixo
bool existe(const string& nome) const;
bool buscar(const string& nome, Item& saida) const;   // false se não achar
int  quantidadeDe(const string& nome) const;
bool baixarEstoque(const string& nome);    // tira 1; apaga do map se zerar
void removerItem(const string& nome);      // apaga o item inteiro
void aumentarEstoque(const string& nome, int quantidade);
void adicionarItem(const Item& novo);      // item novo no catálogo
const map<string, Item>& itens() const;    // leitura só para a interface
```

Estoque inicial fixo (no construtor): espada, poção, escudo, elmo, arco —
com nome, preço, peso e quantidade. Lista simples, sem leitura de arquivo.

Incluir `<map>`, `<string>` e `<Item.hpp>` no topo de `Loja.hpp`.

### `Inventario`

```cpp
void adicionar(const Item& item);   // acumula se find achar, senão insere no fim da list
bool remover1(const string& nome);  // tira 1; apaga da list se zerar
double pesoTotal() const;           // soma de peso * quantidade de cada item
bool vazio() const;
const list<Item>& lista() const;
```

O `Inventario` **não** decide sobre peso: ele não conhece `pesoMax`. O
`adicionar` só faz o `find` para acumular (ou dá `push_back` se for novo).

Quem barra o peso é a `Personagem`, que é dona do `pesoMax`. Ela faz a conta
`inventario.pesoTotal() + pesoDoItem <= pesoMax` dentro de `comprar` e
retorna `PESO_EXCEDIDO` **antes** de chamar `inventario.adicionar`. Assim o
`Inventario` não precisa saber quem carrega ele.

**Incluir `#include <algorithm>` no topo de `Inventario.cpp`**, senão o
compilador não conhece o `std::find`. O `Inventario.hpp` inclui `<list>` e
`<string>`.

### `Personagem`

```cpp
Personagem(string nome, int dinheiro, double pesoMax);
string getNome() const;
int    dinheiro() const;
double pesoMax() const;
double pesoAtual() const;                          // inventario.pesoTotal()
int    comprar(Loja& loja, const string& nome);    // devolve um código
bool   descartar(const string& nome);              // tira 1 da mochila
const Inventario& mochila() const;
```

`comprar` devolve um `enum` (é só um número com nome legível):

```cpp
enum ResultadoCompra { COMPRA_OK, ITEM_NAO_ENCONTRADO, SALDO_INSUFICIENTE, PESO_EXCEDIDO };
```

A interface traduz o código na mensagem exata (`"Saldo insuficiente"`,
`"Peso limite excedido"`, aviso de item não encontrado).

Fluxo de `comprar`: procura na loja → se não achar, `ITEM_NAO_ENCONTRADO` →
compara preço com dinheiro → `SALDO_INSUFICIENTE` → compara peso
(`mochila.pesoTotal() + pesoDoItem` contra `pesoMax`) → `PESO_EXCEDIDO` →
só então desconta o dinheiro, baixa o estoque da loja e chama
`mochila.adicionar(item)`. Compra é sempre de 1 unidade. A barreira do peso
fica **só** aqui, nunca no `Inventario`.

### `Adm`

```cpp
bool autenticar(const string& senhaDigitada) const;  // true se for "123456"
bool adicionar(Loja& loja, const Item& novo);        // cria ou aumenta quantidade
bool tirar1(Loja& loja, const string& nome);         // baixa 1 unidade
bool removerTudo(Loja& loja, const string& nome);    // apaga o item inteiro
```

- A senha fica guardada numa `string` dentro da classe.
- O `Adm` **nunca** mexe no inventário nem no dinheiro do personagem: ele
  recebe a `Loja&` por parâmetro e só mexe no `map` dela.
- Para adicionar um item novo, a interface pede **nome, preço, peso e
  quantidade inicial**. Se o nome já existe, ele só aumenta a quantidade
  (preço e peso não mudam).

## Menu (só na interface)

```text
Bem-vindo! Dinheiro: 200 | Peso: 0/50kg
1 - Ver Loja
2 - Comprar Item
3 - Ver Mochila
4 - Usar/Descartar item
5 - Área do administrador
6 - Sair
```

Na opção 5 a interface pede a senha. Errar a senha → `"Senha incorreta"` e
volta ao menu principal. Acertar → sub-menu:

```text
1 - Adicionar item
2 - Tirar 1 unidade
3 - Remover item inteiro
4 - Voltar
```

## Etapas

Cada etapa termina com o programa compilando pelo comando do `README.md` e
com algo que dá para testar na tela.

### Etapa 1 — `Item` e o `main` mínimo

- Criar `include/Item.hpp`, `src/Item.cpp` e `src/main.cpp`.
- O `main` cria um `Item` de exemplo e imprime nome, preço, peso e
  quantidade.
- **Teste:** compilar e rodar; na etapa seguinte o `main` vira menu.

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema && ./sistema
```

### Etapa 2 — `Loja` e a opção "Ver Loja"

- Criar `include/Loja.hpp`, `src/Loja.cpp`.
- Estoque inicial fixo no construtor.
- `main` ganha o menu e a opção `1 - Ver Loja`, que percorre o `map` e
  imprime nome, preço, peso e quantidade de cada item.
- O menu já nasce tratando entrada inválida: se digitarem uma letra onde o
  `cin` espera número, a leitura falha e a letra fica presa no buffer. Sem
  tratar, o menu entra em laço infinito. A correção:

```cpp
int opcao;
if (!(cin >> opcao)) {       // digitou texto: a leitura falha
    cin.clear();             // limpa o estado de erro do cin
    cin.ignore(1000, '\n');  // descarta o resto da linha presa
    cout << "Opcao invalida" << endl;  // e volta a mostrar o menu
}
```

- **Teste:** escolher 1 e ver o catálogo em ordem alfabética; digitar uma
  letra no menu e conferir que ele pede de novo, sem travar.

### Etapa 3 — `Inventario` e a opção "Ver Mochila"

- Criar `include/Inventario.hpp`, `src/Inventario.cpp` com `adicionar`,
  `remover1`, `pesoTotal`, `vazio`, `lista` (o `find` e o `operator==`
  entram aqui). Incluir `<algorithm>` no `.cpp` e `<list>`/`<string>` no
  `.hpp`.
- Para você conseguir testar antes de existir a compra, o `main` cria um
  inventário de teste com 2 itens e imprime o peso total. **Esse trecho
  temporário sai na etapa 4.**
- **Teste:** ver a mochila com os 2 itens e o peso somado. Testar também o
  acúmulo: chamar `adicionar` com o mesmo nome de um item já existente e
  conferir que a quantidade soma na mesma entrada da `list` (é a prova de
  que o `operator==` está comparando só o nome).

### Etapa 4 — `Personagem` e a compra

- Criar `include/Personagem.hpp`, `src/Personagem.cpp` com o `enum` e
  `comprar`.
- `main` ganha a opção `2 - Comprar Item` e sai do inventário de teste.
- **Teste:** comprar, ver a mochila, comprar o mesmo item de novo (tem que
  acumular na mesma entrada da `list`), tentar comprar sem dinheiro e com
  peso acima do limite, comprar o último item de uma loja (tem que sumir do
  catálogo).

### Etapa 5 — Usar/Descartar

- `main` ganha a opção `4 - Usar/Descartar item`: tira 1 unidade; quando a
  quantidade chega a 0, o item sai da `list`.
- **Teste:** descartar 1 de 3, depois os outros 2, e ver a mochila vazia.

### Etapa 6 — `Adm`

- Criar `include/Adm.hpp`, `src/Adm.cpp`.
- `main` ganha a opção `5 - Área do administrador` + senha `123456` +
  sub-menu com as 3 operações. Senha errada volta ao menu principal.
- **Teste:** errar a senha, entrar, adicionar item novo (pedindo nome,
  preço, peso e quantidade), aumentar a quantidade de um item que já
  existe, tirar 1 unidade até sumir, remover um item inteiro e conferir o
  catálogo.

### Etapa 7 — Robustez e `exemplos/`

- Entrada inválida em **todos** os pontos de leitura numérica (menu, senha,
  preço, peso, quantidade): usar `cin.clear()` + `cin.ignore()` como na
  Etapa 2. O menu não pode travar nem entrar em laço infinito.
- Conferir todas as mensagens do `DESCRICAO.md`, inclusive
  `"inventário está vazio"`.
- Criar os arquivos de teste em `exemplos/`:
  - `cenario1.txt` — compra feliz e ver a mochila;
  - `cenario2.txt` — erros: item inexistente, saldo insuficiente, peso
    limite excedido;
  - `cenario3.txt` — descartar até a mochila ficar vazia;
  - `cenario4.txt` — área do administrador (senha certa e errada).
- **Teste:** rodar todos com `./sistema < exemplos/cenario1.txt` e comparar
  a tela com o esperado.

## Fora do escopo

- Não mexer em `DESCRICAO.md`, `AGENTS.md` nem nas seções próprias do
  `README.md`.
- O comando de compilação do `README.md` já cobre os arquivos novos
  (`src/*.cpp`), então ele não muda.
- Sem `new`/`delete`, sem lambda, sem `unordered_map`, sem biblioteca fora
  da padrão. C++11.
- Salvar em arquivo, interface gráfica e banco de dados são desafios
  opcionais do enunciado, não entram neste plano.
