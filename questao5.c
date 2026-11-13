#include <stdio.h>
#include <limits.h>

#define V 4
#define INF 99999

// Encontra o vértice não visitado com a menor distância atual
int distanciaMinima(int dist[], int visitados[]) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++) {
        if (visitados[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Imprime o caminho recursivamente
void imprimirCaminho(int anteriores[], int destino) {
    if (anteriores[destino] == -1) return;
    imprimirCaminho(anteriores, anteriores[destino]);
    printf(" -> %c", destino + 'A');
}

void dijkstra(int custo_bd) {
    // Representação da topologia usando Matriz de Adjacência
    // 0 indica que não há conexão direta com aquele nó
    int rede[V][V] = {
      /* A, B, C, D */
/* A */ {0, 4, 1, 0},
/* B */ {4, 0, 2, custo_bd},
/* C */ {1, 2, 0, 5},
/* D */ {0, custo_bd, 5, 0}
    };

    int distancias[V];
    int visitados[V];
    int anteriores[V];

    // Configuração inicial
    for (int i = 0; i < V; i++) {
        distancias[i] = INF;
        visitados[i] = 0; // 0 = Falso, 1 = Verdadeiro
        anteriores[i] = -1;
    }

    distancias[0] = 0; // A origem (Roteador A) tem custo 0 para si mesma

    for (int count = 0; count < V - 1; count++) {
        // Escolhe o roteador mais próximo que ainda não foi processado
        int u = distanciaMinima(distancias, visitados);
        visitados[u] = 1;

        // Atualiza o custo dos vizinhos do roteador escolhido
        for (int v = 0; v < V; v++) {
            if (!visitados[v] && rede[u][v] && distancias[u] != INF && 
                distancias[u] + rede[u][v] < distancias[v]) {
                
                distancias[v] = distancias[u] + rede[u][v];
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
    dijkstra(5);
    
    printf("\nREDE FINAL: Link B-D custa 1 (Simulando melhoria na rota)\n");
    dijkstra(1);
    
    return 0;
}