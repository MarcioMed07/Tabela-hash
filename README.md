# Tabela hash com endereçamento aberto


> Implementação em c++ de tabelas hash com endereçamento aberto compostas por tuplas <chave(int), valor(int)> utilizando 3 métodos para tratamento de colisões. (Repositório criado com o intuito de desenvolver um projeto da faculdade da disciplina de Estrutura de Dados 2)

### Ajustes e melhorias

O projeto ainda está em desenvolvimento e as próximas atualizações serão voltadas nas seguintes tarefas:
- Algorítimos:
    - [x] Tentativa Linear
    - [x] Tentativa Quadrática
    - [x] Dispersão Dupla
- Métricas:
    - [x] Número de Colisões
    - [ ] Tempo para encontrar determinada chave
- Cenários de Teste:
    - [ ] Tabelas hash de tamanho diferente
    - [ ] Inserção e exclusão de chaves de forma aleatória

##  Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:
<!---Estes são apenas requisitos de exemplo. Adicionar, duplicar ou remover conforme necessário--->
* Você tem uma máquina que possua uma versão do compilador g++ capaz de compilar códigos em C++ na versão C++11 standard (ISO/IEC 14882:2011).
* Você instalou a versão mais recente do compilador g++ e adicionou o mesmo ao PATH do seu sistema operacional.
* Você leu a documentação abaixo.

##  Instalação

Para instalar o projeto, siga estas etapas:

```
g++ -g aberto.cpp -o aberto 
```

##  Utilização

```
.\aberto(.exe caso esteja no windows) <tamanho_da_tabela> [args]
```
Os seguintes argumentos opcionais estão disponiveis:

Argumento| Descrição
:-----:|:-----:
-v | Exibe a tabela ao fim da execução do programa
-c | Exibe a quantidade de colisões causadas em uma cada busca
-q | Utiliza o algoritimo de Tentativa Quadrática
-d | Utiliza o algoritimo de Dispersão Dupla
-f \<double> | Adiciona nós na tabela até que o fator de carga double 
-b \<int> | Busca uma chave no tabela


O algorítimo padrão utilizado é a Tentativa Linear, para utilizar outro passe um dos argumentos descritos acima

As chaves e valores dos nós possuem o mesmo valor inteiro de chave e valor e a função hash base do endereçamento é 
``` c++
int hash(chave) return chave % tamanho_tabela; 
```
