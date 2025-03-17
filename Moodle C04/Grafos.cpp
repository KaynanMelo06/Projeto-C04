#include <iostream>
using namespace std;

int main()
{

    int vertices, arestas, origem, destino;
    cin >> vertices;
    bool grafo[vertices][vertices];

    

    for (int i = 0; i < vertices; i++) // Preenchimento da matriz com valores nulos
    {
        for (int j = 0; j < vertices; j++)
        {
            grafo[i][j] = false;
        }
    }

    cin >> arestas;

    for (int i = 0; i < arestas; i++)
    {
        cin >> origem >> destino;
        origem--;
        destino--;
        grafo[origem][destino] = true;
        grafo[destino][origem] = true;
    }
    for(int i = 0; i < vertices; i++)
    {
        for(int j = 0; j < vertices; j++)
        {
            cout << grafo[i][j] << "\t";
        }

        cout << endl;
    }

    return 0;
}