#include <stdio.h>
#include <limits.h>

#define V 4       // Número de roteadores (A, B, C, D)
#define E 10      // 5 conexões bidirecionais = 10 arestas direcionadas
#define INF 99999 // Representa o infinito (rota inalcançável)

// Estrutura para representar uma ligação (aresta) entre dois roteadores
struct Aresta {
    int origem, destino, custo;
};

// Função recursiva para imprimir o caminho traçado pelo vetor de 'anteriores'
void imprimirCaminho(int anteriores[], int destino) {
    if (anteriores[destino] == -1) return;
    imprimirCaminho(anteriores, anteriores[destino]);
    printf(" -> %c", destino + 'A'); // Converte o índice 0,1,2,3 para A,B,C,D
}

void bellman_ford(int custo_bd) {
    // Definição da rede (ida e volta para cada link)
    struct Aresta ligacoes[E] = {
        {0, 1, 4}, {1, 0, 4}, // A <-> B (Custo 4)
        {0, 2, 1}, {2, 0, 1}, // A <-> C (Custo 1)
        {1, 2, 2}, {2, 1, 2}, // B <-> C (Custo 2)
        {1, 3, custo_bd}, {3, 1, custo_bd}, // B <-> D (Custo Variável)
        {2, 3, 5}, {3, 2, 5}  // C <-> D (Custo 5)
    };

    int distancias[V];
    int anteriores[V];

    // Inicializa as distâncias como infinito e anteriores como nulos (-1)
    for (int i = 0; i < V; i++) {
        distancias[i] = INF;
        anteriores[i] = -1;
    }
    
    distancias[0] = 0; // O roteador A (índice 0) é a origem

    // Relaxamento: ocorre V - 1 vezes
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = ligacoes[j].origem;
            int v = ligacoes[j].destino;
            int peso = ligacoes[j].custo;

            if (distancias[u] != INF && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                anteriores[v] = u;
            }
        }
    }

    // Exibição dos resultados
    printf("Rotas a partir de A:\n");
    for (int i = 0; i < V; i++) {
        printf("A");
        imprimirCaminho(anteriores, i);
        printf(" | Custo: %d\n", distancias[i]);
    }
}

int main() {
    printf("REDE INICIAL: Link B-D custa 5\n");
    bellman_ford(5);
    
    printf("\nREDE FINAL: Link B-D custa 1 (Simulando melhoria na rota)\n");
    bellman_ford(1);
    
    return 0;
}