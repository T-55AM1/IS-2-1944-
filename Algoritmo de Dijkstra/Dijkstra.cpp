#include <iostream>
#include <vector>
#include <climits>  // Para usar INT_MAX (Infinito)
#include <cstdlib>  // Para usar system("cls") o system("clear")

using namespace std;

// Definimos el número de nodos del grafo (fijo para facilitar el gráfico ASCII)
#define NODOS 5
#define INF INT_MAX

// Función auxiliar para imprimir el Grafo Visual en la consola (Puntos Extras)
void dibujarGrafoVisual(int nodoActual, int distancias[], bool visitados[]) {
    // Limpia la pantalla para crear efecto de animación en Dev-C++
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "---------------------------------------------------------" << endl;
    cout << "        SIMULADOR GRAFICO DEL ALGORITMO DE DIJKSTRA       " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << " Nodo Actual: ";
    if (nodoActual == -1) cout << "NINGUNO (Inicio)";
    else cout << (char)('A' + nodoActual);
    cout << endl << endl;

    // Dibujo del mapa de red (Arte ASCII dinámico)
    // Cambia de color conceptualmente o marca con '*' si el nodo ya fue visitado
    cout << "       ( B ) [Dist: "; 
    if(distancias[1] == INF) cout << "INF"; else cout << distancias[1];
    cout << "]" << (visitados[1] ? " *VISITADO*" : "") << endl;
    
    cout << "       /   \\ " << endl;
    cout << "  4   /     \\  2" << endl;
    cout << "     /       \\ " << endl;
    
    cout << " ( A ) ------- ( C ) [Dist: ";
    if(distancias[2] == INF) cout << "INF"; else cout << distancias[2];
    cout << "]" << (visitados[2] ? " *VISITADO*" : "") << endl;
    
    cout << "     \\   3   / \\ " << endl;
    cout << "  1   \\     /   \\  6" << endl;
    cout << "       \\   /     \\ " << endl;
    
    cout << "       ( D )     ( E ) [Dist: ";
    if(distancias[4] == INF) cout << "INF"; else cout << distancias[4];
    cout << "]" << (visitados[4] ? " *VISITADO*" : "") << endl;
    
    cout << "  [Dist: "; if(distancias[3] == INF) cout << "INF"; else cout << distancias[3];
    cout << "]" << (visitados[3] ? " *VISITADO*" : "") << endl;
    cout << "---------------------------------------------------------" << endl;
}

// Función para mostrar la tabla de estados paso a paso
void mostrarTablaPasos(int distancias[], bool visitados[]) {
    cout << "\nTabla de distancias acumuladas actuales:\n";
    cout << "Nodo:\t\tA\tB\tC\tD\tE\n";
    cout << "Distancia:\t";
    for (int i = 0; i < NODOS; i++) {
        if (distancias[i] == INF) cout << "INF\t";
        else cout << distancias[i] << "\t";
    }
    cout << "\nVisitado:\t";
    for (int i = 0; i < NODOS; i++) {
        cout << (visitados[i] ? "SI" : "NO") << "\t";
    }
    cout << "\n---------------------------------------------------------\n";
    cout << "Presione ENTER para continuar al siguiente paso...";
    cin.get(); // Pausa el flujo para observar la simulación paso a paso
}

// Encuentra el nodo con la distancia mínima que aún no ha sido visitado
int minDistancia(int distancias[], bool visitados[]) {
    int minimo = INF, indiceMinimo = -1;
    for (int v = 0; v < NODOS; v++) {
        if (!visitados[v] && distancias[v] <= minimo) {
            minimo = distancias[v];
            indiceMinimo = v;
        }
    }
    return indiceMinimo;
}

// Implementación del Algoritmo de Dijkstra con simulación integrada
void dijkstraSimulador(int grafo[NODOS][NODOS], int origen) {
    int distancias[NODOS];
    bool visitados[NODOS];

    // Inicialización clásica en C++98
    for (int i = 0; i < NODOS; i++) {
        distancias[i] = INF;
        visitados[i] = false;
    }

    // La distancia desde el origen a sí mismo siempre es 0
    distancias[origen] = 0;

    // Mostrar estado inicial de arranque
    dibujarGrafoVisual(-1, distancias, visitados);
    mostrarTablaPasos(distancias, visitados);

    // Ciclo principal del algoritmo para recorrer todos los vértices
    for (int count = 0; count < NODOS - 1; count++) {
        // Seleccionar el vértice de menor distancia
        int u = minDistancia(distancias, visitados);
        if (u == -1) break; // Si ya no hay nodos alcanzables, termina

        // Marcar el nodo seleccionado como procesado (visitado)
        visitados[u] = true;

        // Actualizar la vista del simulador gráfico
        dibujarGrafoVisual(u, distancias, visitados);
        cout << ">> Evaluando los vecinos del nodo " << (char)('A' + u) << "..." << endl;

        // Actualizar el valor de la distancia de los nodos vecinos del nodo seleccionado
        for (int v = 0; v < NODOS; v++) {
            // Si el nodo v no está visitado, hay una conexión real, y la ruta a través de u es más corta
            if (!visitados[v] && grafo[u][v] != 0 && distancias[u] != INF 
                && distancias[u] + grafo[u][v] < distancias[v]) {
                
                distancias[v] = distancias[u] + grafo[u][v];
                cout << "   * Camino optimizado hacia " << (char)('A' + v) 
                     << " con nueva distancia: " << distancias[v] << endl;
            }
        }
        
        // Pausar y mostrar los resultados consolidados de esta iteración
        mostrarTablaPasos(distancias, visitados);
    }

    // Dibujo estático final con los resultados consolidados definitivos
    dibujarGrafoVisual(-1, distancias, visitados);
    cout << "---------------------------------------------------------" << endl;
    cout << "           SIMULACION COMPLETA - RUTA OPTIMA             " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Rutas mas cortas definitivas desde el Nodo A:" << endl;
    for (int i = 0; i < NODOS; i++) {
        cout << "  Distancia hasta el Nodo " << (char)('A' + i) << " = " << distancias[i] << endl;
    }
    cout << "---------------------------------------------------------" << endl;
}

int main() {
    // Definimos la matriz de adyacencia del grafo para la simulación
    // Los números representan los pesos (costos/kilómetros) entre los nodos. 0 significa que no hay conexión directa.
    // Nodos mapeados: 0=A, 1=B, 2=C, 3=D, 4=E
    int grafo[NODOS][NODOS] = {
        {0, 4, 3, 1, 0},  // Conexiones desde A
        {4, 0, 2, 0, 0},  // Conexiones desde B
        {3, 2, 0, 0, 6},  // Conexiones desde C
        {1, 0, 0, 0, 0},  // Conexiones desde D
        {0, 0, 6, 0, 0}   // Conexiones desde E
    };

    // Lanzar el simulador tomando como punto de partida el Nodo A (0)
    dijkstraSimulador(grafo, 0);

    // Evita que la consola se cierre abruptamente en Dev-C++ al terminar
    cout << "\nPresione cualquier tecla para salir del simulador...";
    cin.get();
    
    return 0;
}

