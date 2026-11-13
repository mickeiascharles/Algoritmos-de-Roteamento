# Algoritmos de Roteamento: Bellman-Ford e Dijkstra em C

**Disciplina:** Laboratório de Redes de Computadores  
**Curso:** Ciência da Computação  
**Instituição:** Universidade Católica de Brasília (UCB)  
**Autor:** Mickeias Charles de Oliveira Paiva  

##  Sobre o Projeto

Este repositório contém as implementações na linguagem C de dois dos principais algoritmos de roteamento dinâmico utilizados em redes de computadores: **Bellman-Ford** (base para o protocolo RIP) e **Dijkstra** (base para o protocolo OSPF). 

O objetivo do projeto é demonstrar o funcionamento prático da descoberta de caminhos mínimos em uma rede, simulando como os roteadores calculam e atualizam suas tabelas de roteamento com base nos custos dos enlaces (links).

##  Topologia da Rede

A simulação utiliza uma topologia composta por **4 roteadores** (`A`, `B`, `C` e `D`), garantindo o requisito de no mínimo duas rotas de entrada/saída para cada nó. 

As conexões e custos iniciais são:
* **A** <-> **B** (Custo 4)
* **A** <-> **C** (Custo 1)
* **B** <-> **C** (Custo 2)
* **B** <-> **D** (Custo variável: inicia em 5, atualiza para 1)
* **C** <-> **D** (Custo 5)

##  Cenários de Simulação

Para demonstrar a capacidade de adaptação dos algoritmos a mudanças na infraestrutura, os códigos executam dois cenários sequenciais:

1. **Rede Inicial (Congestionada):** O link entre `B` e `D` tem um custo alto (`5`). O tráfego de `A` para `D` contorna esse gargalo passando por `A -> C -> B -> D` (Custo total: 8).
2. **Rede Final (Otimizada):** O link entre `B` e `D` sofre uma melhoria (ex: troca de cabeamento ou fim de congestionamento) e seu custo cai para `1`. Os algoritmos detectam a mudança e recalculam a rota, que passa a ser muito mais rápida (Custo total cai para 4).

##  Detalhes das Implementações

* **`bellman_ford.c`**: Utiliza uma lista estática de arestas e realiza o processo de "relaxamento" iterativo. Em redes reais, lida bem com mudanças topológicas distribuídas, embora sofra com o problema de "contagem ao infinito".
* **`dijkstra.c`**: Baseado em uma Matriz de Adjacência. O algoritmo expande gulodamente o vizinho com o menor custo acumulado, processando a topologia de forma mais eficiente para encontrar o caminho mais curto a partir do Roteador A.

##  Como Compilar e Executar

Certifique-se de ter o compilador GCC instalado no seu ambiente de desenvolvimento. Clone este repositório e execute os comandos abaixo no terminal:

**Para rodar o algoritmo de Bellman-Ford:**
```bash
gcc bellman_ford.c -o bellman
./bellman
