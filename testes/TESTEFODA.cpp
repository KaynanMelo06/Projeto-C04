#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstdlib> // Para system("CLS")

using namespace std;

// Estrutura para armazenar os dados das cidades
struct dadoscidade {
    int codigo;
    string nome;
    bool possuiCentroPokemon;
    vector<int> cidadesAdjacentes; // Lista de códigos das cidades adjacentes
};

// Variáveis globais
const int MAX_CIDADES = 50;
dadoscidade cidades[MAX_CIDADES];
int matrizAdjacencia[MAX_CIDADES][MAX_CIDADES];
int numCidades = 0;

// Função para inicializar a matriz de adjacência
void inicializarMatrizAdjacencia() {
    for (int i = 0; i < MAX_CIDADES; i++) {
        for (int j = 0; j < MAX_CIDADES; j++) {
            matrizAdjacencia[i][j] = -1; // -1 indica que não há conexão
        }
    }
}

// Função para cadastrar cidades
void cadastrarCidade() {
    cout << "Digite o número de cidades a cadastrar: ";
    int n;
    cin >> n;

    while (n <= 0 || numCidades + n > MAX_CIDADES) {
        cout << "Número inválido. Digite novamente: ";
        cin >> n;
    }

    for (int i = 0; i < n; i++) {
        cout << "Cidade " << (numCidades + 1) << ":" << endl;

        cout << "Digite o nome da cidade: ";
        cin.ignore();
        getline(cin, cidades[numCidades].nome);

        cout << "Digite o código da cidade: ";
        cin >> cidades[numCidades].codigo;

        char possuiCP;
        cout << "A cidade possui centro Pokémon? (S/N): ";
        cin >> possuiCP;

        cidades[numCidades].possuiCentroPokemon = (possuiCP == 'S' || possuiCP == 's');
        numCidades++;
    }

    cout << "Cidades cadastradas com sucesso!" << endl;
}

// Função para cadastrar estradas
void cadastrarEstrada() {
    cout << "Digite o código da cidade de origem: ";
    int origem, destino, distancia;
    cin >> origem;

    cout << "Digite o código da cidade de destino: ";
    cin >> destino;

    cout << "Digite a distância entre as cidades: ";
    cin >> distancia;

    // Encontrar índices das cidades
    int idxOrigem = -1, idxDestino = -1;
    for (int i = 0; i < numCidades; i++) {
        if (cidades[i].codigo == origem) idxOrigem = i;
        if (cidades[i].codigo == destino) idxDestino = i;
    }

    if (idxOrigem == -1 || idxDestino == -1) {
        cout << "Códigos de cidades inválidos!" << endl;
        return;
    }

    // Atualizar a matriz de adjacência
    matrizAdjacencia[idxOrigem][idxDestino] = distancia;
    matrizAdjacencia[idxDestino][idxOrigem] = distancia; // Grafo não direcionado

    cout << "Estrada cadastrada com sucesso!" << endl;
}

// Função para buscar o centro Pokémon mais próximo
void buscarCentroPokemonMaisProximo() {
    cout << "Digite o código da cidade atual: ";
    int codigoAtual;
    cin >> codigoAtual;

    // Encontrar o índice da cidade atual
    int idxAtual = -1;
    for (int i = 0; i < numCidades; i++) {
        if (cidades[i].codigo == codigoAtual) {
            idxAtual = i;
            break;
        }
    }

    if (idxAtual == -1) {
        cout << "Código de cidade inválido!" << endl;
        return;
    }

    // Algoritmo de Dijkstra para encontrar o centro Pokémon mais próximo
    vector<bool> visitado(numCidades, false);
    vector<int> distancia(numCidades, numeric_limits<int>::max());
    vector<int> anterior(numCidades, -1); // Para reconstruir o caminho
    distancia[idxAtual] = 0;

    for (int i = 0; i < numCidades; i++) {
        int menorDist = numeric_limits<int>::max();
        int cidadeAtual = -1;

        for (int j = 0; j < numCidades; j++) {
            if (!visitado[j] && distancia[j] < menorDist) {
                menorDist = distancia[j];
                cidadeAtual = j;
            }
        }

        if (cidadeAtual == -1) break;
        visitado[cidadeAtual] = true;

        for (int j = 0; j < numCidades; j++) {
            if (matrizAdjacencia[cidadeAtual][j] != -1 && !visitado[j]) {
                int novaDist = distancia[cidadeAtual] + matrizAdjacencia[cidadeAtual][j];
                if (novaDist < distancia[j]) {
                    distancia[j] = novaDist;
                    anterior[j] = cidadeAtual;
                }
            }
        }
    }

    // Encontrar o centro Pokémon mais próximo
    int menorDist = numeric_limits<int>::max();
    int idxCentro = -1;

    for (int i = 0; i < numCidades; i++) {
        if (cidades[i].possuiCentroPokemon && distancia[i] < menorDist) {
            menorDist = distancia[i];
            idxCentro = i;
        }
    }

    if (idxCentro == -1) {
        cout << "Nenhum centro Pokémon encontrado!" << endl;
    } else {
        cout << "Centro Pokémon mais próximo: " << cidades[idxCentro].nome
             << " (Distância: " << menorDist << ")" << endl;

        // Reconstruir o caminho
        cout << "Rota: ";
        vector<int> rota;
        for (int at = idxCentro; at != -1; at = anterior[at]) {
            rota.push_back(at);
        }
        for (auto it = rota.rbegin(); it != rota.rend(); ++it) {
            cout << cidades[*it].nome << " ";
        }
        cout << endl;
    }
}

// Função principal
int main() {
    inicializarMatrizAdjacencia();

    bool acabar = false;

    do {
        cout << "Menu:" << endl;
        cout << "1. Cadastrar cidade" << endl;
        cout << "2. Cadastrar estrada" << endl;
        cout << "3. Buscar centro Pokémon mais próximo" << endl;
        cout << "4. Sair" << endl;

        int opcao;
        cin >> opcao;

        switch (opcao) {
        case 1:
            system("CLS");
            cadastrarCidade();
            break;
        case 2:
            system("CLS");
            cadastrarEstrada();
            break;
        case 3:
            system("CLS");
            buscarCentroPokemonMaisProximo();
            break;
        case 4:
            system("CLS");
            cout << "Encerrando o programa..." << endl;
            acabar = true;
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
    } while (!acabar);

    return 0;
}