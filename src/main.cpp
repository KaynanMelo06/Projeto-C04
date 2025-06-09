#include <iostream>
#include <list>     // Biblioteca para manipulação de listas (lista de adjacência)
#include <cstdlib>  // Biblioteca para system("CLS")
#include <climits>  // Para definir valores máximos (ex. INT_MAX)
#include <string>   // Biblioteca para manipulação de strings
#include <cmath>	// Biblioteca para manipulações manematicas

#define INF 999999

using namespace std;

// Dados básicos de cada Pokémon
struct Pokemon {
    string nome;
    string tipo;
    int num;
    int x, y; // Coordenadas no mapa
};

// Nó de árvore binária para armazenar Pokémons
struct NodePokemon {
    Pokemon info;
    NodePokemon* esquerda;
    NodePokemon* direita;
};

// Raízes das duas BSTs:
//  - raizPorNome: ordenada pelo campo .nome
//  - raizPorTipo: ordenada pelo campo .tipo (desempate por nome quando tipos iguais)
NodePokemon* raizPorNome = nullptr;
NodePokemon* raizPorTipo = nullptr;
// Função auxiliar para buscar um Pokémon por nome na árvore de tipo
NodePokemon* buscarNodePorNome(NodePokemon* raiz, const string& nome);
bool removerPokemonPorTipo(NodePokemon*&, const string&, const string&);

// Dados de cada cidade
struct dadoscidade {
    int codigo;
    string nome;
    bool pc; // Indica se há Centro Pokémon naquela cidade
};

// -------------------------
// Variáveis globais
// -------------------------
int ncidades = 0;                   // Quantidade de cidades cadastradas
dadoscidade dados[50];              // Vetor de cidades (no máximo 50)
int mapa[10][10];                   // "Mapa" 10x10 de Pokémons (0 = vazio, 1 = ocupado)
int grafo[50][50];                  // Matriz de adjacência (no máximo 50 cidades)

// =========================
// Funções de cadastro de Cidades e Estradas
// =========================
void cadastrarCidade() {
    int temp;
    char simnao;

    cout << "Digite o numero de cidades: ";
    cin >> temp;
    cin.ignore(100000, '\n'); // limpar buffer

    // Validação mínima
    while (temp <= 0) {
        cout << "Numero de cidades invalido, digite novamente: ";
        cin >> temp;
        cin.ignore(100000, '\n');
    }
    ncidades = temp;

    for (int i = 0; i < ncidades; i++) {
        cout << "Nome da cidade " << i + 1 << ": ";
        getline(cin, dados[i].nome);

        dados[i].codigo = i + 1;
        cout << "O codigo da cidade " << i + 1 << " sera: " << dados[i].codigo << endl;

        cout << "Essa cidade possui centro pokemon? (S/N): ";
        cin >> simnao;
        cin.ignore(100000, '\n');

        dados[i].pc = (simnao == 'S' || simnao == 's');
    }

    system("clear");

    // Exibir para conferência
    for (int i = 0; i < ncidades; i++) {
        cout << "Cidade " << i + 1 << ": " << dados[i].nome << endl;
        cout << "  Codigo: " << dados[i].codigo << endl;
        cout << "  Possui CP: " << (dados[i].pc ? "Sim" : "Nao") << endl << endl;
    }
}

void cadastrarEstrada() {
    if (ncidades <= 0) {
        cout << "Nenhuma cidade cadastrada. Cadastre cidades primeiro!\n";
        return;
    }

    cout << "Cidades cadastradas:\n";
    for (int i = 0; i < ncidades; i++) {
        cout << "  " << dados[i].codigo << " - " << dados[i].nome << endl;
    }
    cout << endl;

    int cidade1, cidade2, distancia;
    char continuar;

    do {
        cout << "Digite o codigo da primeira cidade: ";
        cin >> cidade1;
        cout << "Digite o codigo da segunda cidade: ";
        cin >> cidade2;
        cout << "Digite a distancia entre as cidades: ";
        cin >> distancia;
        cin.ignore(100000, '\n');

        // Validação de índice
        if (cidade1 >= 1 && cidade1 <= ncidades && cidade2 >= 1 && cidade2 <= ncidades) {
            grafo[cidade1 - 1][cidade2 - 1] = distancia;
            grafo[cidade2 - 1][cidade1 - 1] = distancia;
        } else {
            cout << "Codigos de cidades invalidos. Tente novamente.\n\n";
        }

        cout << "Deseja cadastrar outra estrada? (S/N): ";
        cin >> continuar;
        cin.ignore(100000, '\n');
        cout << endl;
    } while (continuar == 'S' || continuar == 's');

    // Exibir a matriz de adjacência
    cout << "Matriz de Adjacencia:\n";
    for (int i = 0; i < ncidades; i++) {
        for (int j = 0; j < ncidades; j++) {
            cout << grafo[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

// =========================
// Conversão Matriz ? Lista de Adjacência
// =========================
struct Aresta {
    int origem, destino, peso;
};

void converterParaListaAdjacencia(list<Aresta> grafoLista[], int grafoMatriz[50][50], int ncidades) {
    for (int i = 0; i < ncidades; i++) {
        for (int j = 0; j < ncidades; j++) {
            if (grafoMatriz[i][j] != -1) {
                // Adiciona aresta (i ? j) com peso
                grafoLista[i].push_back({i, j, grafoMatriz[i][j]});
            }
        }
    }
}

// =========================
// Dijkstra (usando lista de adjacência)
// =========================
int dijkstra_lista(list<Aresta> grafoLista[], int vertices, int origem, int destino) {
    // Como "vertices <= 50", podemos usar arrays fixos de tamanho 50
    bool visitado[50];
    int pais[50];
    int distanciaArr[50];
    int atual;

    // Inicialização
    for (int i = 0; i < vertices; i++) {
        visitado[i] = false;
        pais[i] = -1;
        distanciaArr[i] = INF;
    }
    distanciaArr[origem] = 0;
    atual = origem;

    while (!visitado[atual]) {
        visitado[atual] = true;

        // Atualiza distâncias dos vizinhos
        for (auto& aresta : grafoLista[atual]) {
            int d = aresta.destino;
            int p = aresta.peso;
            if (!visitado[d] && distanciaArr[atual] + p < distanciaArr[d]) {
                distanciaArr[d] = distanciaArr[atual] + p;
                pais[d] = atual;
            }
        }

        // Achar próximo vértice não visitado com menor distância
        int menor_peso = INF;
        for (int i = 0; i < vertices; i++) {
            if (!visitado[i] && distanciaArr[i] < menor_peso) {
                menor_peso = distanciaArr[i];
                atual = i;
            }
        }
    }

    return distanciaArr[destino];
}

// =========================
// Prim para achar o Centro Pokémon mais próximo
// =========================
int primCentroPokemonMaisProximo(list<Aresta> grafoLista[], int vertices, int origem, dadoscidade dadosVetor[]) {
    // Como "vertices <= 50", usamos arrays fixos de tamanho 50
    bool visitado[50];
    int distanciaArr[50];
    int atual;

    // Inicializa vetores
    for (int i = 0; i < vertices; i++) {
        visitado[i] = false;
        distanciaArr[i] = INF;
    }

    // Começa em 'origem'
    atual = origem;
    distanciaArr[atual] = 0;

    while (!visitado[atual]) {
        visitado[atual] = true;

        // Verifica se esta cidade possui CP
        if (dadosVetor[atual].pc) {
            cout << "O Centro Pokemon mais proximo esta na cidade: " << dadosVetor[atual].nome << endl;
            cout << "Distancia (Dijkstra): "
                 << dijkstra_lista(grafoLista, vertices, origem, atual)
                 << endl;
            return distanciaArr[atual];
        }

        // Atualiza distâncias de arestas mínimas incidentes
        for (auto& aresta : grafoLista[atual]) {
            int d = aresta.destino;
            int p = aresta.peso;
            if (!visitado[d] && p < distanciaArr[d]) {
                distanciaArr[d] = p;
            }
        }

        // Escolhe próximo não visitado com menor distância
        int menor_distancia = INF;
        for (int i = 0; i < vertices; i++) {
            if (!visitado[i] && distanciaArr[i] < menor_distancia) {
                menor_distancia = distanciaArr[i];
                atual = i;
            }
        }
    }

    cout << "Nenhum Centro Pokemon encontrado acessivel a partir da cidade atual." << endl;
    return -1;
}

void buscarCentroPokemonMaisProximo() {
    if (ncidades <= 0) {
        cout << "Nenhuma cidade cadastrada. Cadastre cidades primeiro!\n";
        return;
    }

    int cidadeAtual;
    cout << "Digite o codigo da sua cidade atual: ";
    cin >> cidadeAtual;
    cin.ignore(100000, '\n');

    if (cidadeAtual < 1 || cidadeAtual > ncidades) {
        cout << "Codigo de cidade invalido!\n";
        return;
    }
    cidadeAtual--; // Ajusta para índice 0-based

    // Converte a matriz para lista de adjacência
    static list<Aresta> grafoLista[50];
    for (int i = 0; i < ncidades; i++) {
        grafoLista[i].clear();
    }
    converterParaListaAdjacencia(grafoLista, grafo, ncidades);

    // Executa Prim adaptado
    primCentroPokemonMaisProximo(grafoLista, ncidades, cidadeAtual, dados);
}

// =========================
// Funções de Árvore de Pokémons
// =========================

// Inserção em árvore ordenada por nome
void inserirPokemon(NodePokemon*& raiz, const Pokemon& p) {
    if (!raiz) {
        raiz = new NodePokemon;
        raiz->info = p;
        raiz->esquerda = nullptr;
        raiz->direita = nullptr;
    }
    else if (p.nome < raiz->info.nome) {
        inserirPokemon(raiz->esquerda, p);
    }
    else {
        inserirPokemon(raiz->direita, p);
    }
}

// Inserção em árvore ordenada por tipo
void inserirPorTipo(NodePokemon*& raiz, const Pokemon& p) {
    if (!raiz) {
        raiz = new NodePokemon;
        raiz->info = p;
        raiz->esquerda = nullptr;
        raiz->direita = nullptr;
    }
    else if (p.tipo < raiz->info.tipo) {
        inserirPorTipo(raiz->esquerda, p);
    }
    else if (p.tipo > raiz->info.tipo) {
        inserirPorTipo(raiz->direita, p);
    }
    else {
        // Se tipos iguais, desempata pelo nome
        if (p.nome < raiz->info.nome) {
            inserirPorTipo(raiz->esquerda, p);
        } else {
            inserirPorTipo(raiz->direita, p);
        }
    }
}

NodePokemon* buscarNodePorNome(NodePokemon* raiz, const string& nome) {
    if (!raiz) return nullptr;

    if (nome < raiz->info.nome) {
        return buscarNodePorNome(raiz->esquerda, nome);
    }
    else if (nome > raiz->info.nome) {
        return buscarNodePorNome(raiz->direita, nome);
    }
    else {
        // Encontrou o nó cujo info.nome == nome
        return raiz;
    }
}

bool removerPokemonPorTipo(NodePokemon*& raiz, const string& tipo, const string& nome) {
    if (!raiz) return false;

    // Caso o tipo procurado seja "menor" do que o tipo do nó atual
    if (tipo < raiz->info.tipo) {
        return removerPokemonPorTipo(raiz->esquerda, tipo, nome);
    }
    // Caso contrário, se tipo for “maior”
    else if (tipo > raiz->info.tipo) {
        return removerPokemonPorTipo(raiz->direita, tipo, nome);
    }
    else {
        // tipos são iguais; agora desempatar pelo nome
        if (nome < raiz->info.nome) {
            return removerPokemonPorTipo(raiz->esquerda, tipo, nome);
        }
        else if (nome > raiz->info.nome) {
            return removerPokemonPorTipo(raiz->direita, tipo, nome);
        }
        else {
            // Encontrou exatamente o nó (tipo e nome iguais)
            NodePokemon* temp = raiz;
            // Caso 1: não tem subárvore esquerda
            if (!raiz->esquerda) {
                raiz = raiz->direita;
            }
            // Caso 2: não tem subárvore direita
            else if (!raiz->direita) {
                raiz = raiz->esquerda;
            }
            // Caso 3: tem duas subárvores
            else {
                // Encontrar o sucessor inorder (menor nó na subárvore direita)
                NodePokemon* suces = raiz->direita;
                while (suces->esquerda) {
                    suces = suces->esquerda;
                }
                // Copiar dados do sucessor para o nó atual
                raiz->info = suces->info;
                // Remover recursivamente o sucessor (faz desempate só por tipo/nome, mas como já mudou info, ele vai bater no else abaixo)
                return removerPokemonPorTipo(raiz->direita, suces->info.tipo, suces->info.nome);
            }
            delete temp;
            return true;
        }
    }
}

// Remoção de um Pokémon da árvore POR NOME (raizPorNome)
bool removerPokemonPorNome(NodePokemon*& raiz, const string& nome) {
    if (!raiz) return false;

    if (nome < raiz->info.nome) {
        return removerPokemonPorNome(raiz->esquerda, nome);
    }
    else if (nome > raiz->info.nome) {
        return removerPokemonPorNome(raiz->direita, nome);
    }
    else {
        // Nó encontrado: três casos possíveis
        NodePokemon* temp = raiz;
        if (!raiz->esquerda) {
            raiz = raiz->direita;
        }
        else if (!raiz->direita) {
            raiz = raiz->esquerda;
        }
        else {
            // Dois filhos: achar predecessor (maior elemento à esquerda)
            NodePokemon** pred = &raiz->esquerda;
            while ((*pred)->direita) {
                pred = &((*pred)->direita);
            }
            // Substitui info pelo predecessor
            raiz->info = (*pred)->info;
            temp = *pred;
            *pred = (*pred)->esquerda;
        }
        delete temp;
        return true;
    }
}

// Função de remoção chamada diretamente no menu
void removerPokemon() {
    string nome;
    cout << "Remover Pokemon - Digite o nome: ";
    cin.ignore(100000, '\n');
    getline(cin, nome);

    // 1) Procurar na árvore por NOME para obter o tipo antes de apagar
    NodePokemon* noEncontrado = buscarNodePorNome(raizPorNome, nome);
    if (!noEncontrado) {
        cout << nome << " nao encontrado.\n";
        return;
    }
    string tipoEncontrado = noEncontrado->info.tipo;

    // 2) Remover da árvore por NOME
    bool removedNome = removerPokemonPorNome(raizPorNome, nome);
    if (removedNome) {
        cout << nome << " removido com sucesso da arvore por NOME.\n";
    } else {
        // (Na prática não deve acontecer, pois já checamos acima com buscarNodePorNome)
        cout << "Falha ao remover " << nome << " da arvore por NOME.\n";
    }

    // 3) Remover da árvore por TIPO (desempate por nome)
    bool removedTipo = removerPokemonPorTipo(raizPorTipo, tipoEncontrado, nome);
    if (removedTipo) {
        cout << nome << " removido com sucesso da arvore por TIPO.\n";
    } else {
        // Caso improvável: não achou na árvore por tipo
        cout << "Falha ao remover " << nome << " da arvore por TIPO.\n";
    }
}

// Listagem in-order por nome
void listarPokemonsPorNome(NodePokemon* raiz) {
    if (!raiz) return;
    listarPokemonsPorNome(raiz->esquerda);
    cout << "- " << raiz->info.nome 
         << " (Tipo: " << raiz->info.tipo 
         << ", Codigo: " << raiz->info.num 
         << ", Coords: " << raiz->info.x << "," << raiz->info.y << ")\n";
    listarPokemonsPorNome(raiz->direita);
}

// Listagem in-order por tipo
void listarPokemonsPorTipo(NodePokemon* raiz) {
    if (!raiz) return;
    listarPokemonsPorTipo(raiz->esquerda);
    cout << "- " << raiz->info.tipo 
         << " -> " << raiz->info.nome 
         << " (Codigo: " << raiz->info.num 
         << ", Coords: " << raiz->info.x << "," << raiz->info.y << ")\n";
    listarPokemonsPorTipo(raiz->direita);
}

// Conta quantos Pokémons de um dado tipo há na árvore
void contarPorTipo(NodePokemon* raiz, const string& tipo, int& cont) {
    if (!raiz) return;
    if (raiz->info.tipo == tipo) {
        cont++;
    }
    contarPorTipo(raiz->esquerda, tipo, cont);
    contarPorTipo(raiz->direita, tipo, cont);
}

// =========================
// Interfaces de Cadastro/Listagem de Pokémons
// =========================

void cadastrarPokemon() {
    Pokemon p;
    char continuar;

    cout << ">> Cadastrar Pokemon <<\n";
    do {
        cout << "Nome: ";
        cin.ignore(100000, '\n');
        getline(cin, p.nome);

        cout << "Tipo: ";
        getline(cin, p.tipo);

        cout << "Numero: ";
        cin >> p.num;

        cout << "Coordenadas (x y): ";
        cin >> p.x >> p.y;
        cin.ignore(100000, '\n');

        // Ajusta para índice 0-based no mapa 10x10
        if (p.x >= 1 && p.x <= 10 && p.y >= 1 && p.y <= 10) {
            mapa[p.x - 1][p.y - 1] = 1;
        }

        // Insere nas duas árvores
        inserirPokemon(raizPorNome, p);
        inserirPorTipo(raizPorTipo, p);

        cout << "Cadastrar outro? (S/N): ";
        cin >> continuar;
        cin.ignore(100000, '\n');
        cout << endl;
    } while (continuar == 'S' || continuar == 's');
}

// Mostra TODOS os Pokémons ordenados por tipo (sem filtro explícito)
void listarPokemonTipo() {
    if (!raizPorTipo) {
        cout << "Nenhum Pokemon cadastrado.\n";
        return;
    }
    cout << ">> Pokemons (ordenados por TIPO) <<\n\n";
    listarPokemonsPorTipo(raizPorTipo);
    cout << "\n";
}

// Apenas conta quantos Pokémons de um tipo específico existem
void contarPokemonTipo() {
    if (!raizPorTipo) {
        cout << "Nenhum Pokemon cadastrado.\n";
        return;
    }
    string tipoBusca;
    cout << "Digite o tipo do Pokemon: ";
    cin.ignore(100000, '\n');
    getline(cin, tipoBusca);

    int cont = 0;
    contarPorTipo(raizPorTipo, tipoBusca, cont);
    cout << "\nTotal de Pokemon(s) do tipo '" 
         << tipoBusca << "': " << cont << "\n\n";
}

// =========================
// Função para pokemons proximos
// =========================

void encontrarPokemonProximosUtil(NodePokemon* node, int xref, int yref, double& minDist, list<Pokemon>& proximos)
{
    if (!node) return;

    // calcula distância entre o ponto de referencia e o dos pokemons (Euclidiana)
    int dx = node->info.x - xref;
    int dy = node->info.y - yref;
    double dist = sqrt(double(dx*dx + dy*dy));

    if (dist < minDist) {
        minDist = dist;
        proximos.clear();
        proximos.push_back(node->info);
    }
    else if (fabs(dist - minDist) < 1e-9) {
        // se for exatamente igual (usando tolerância), adiciona empate
        proximos.push_back(node->info);
    }

    // continua recursão nas subárvores
    encontrarPokemonProximosUtil(node->esquerda, xref, yref, minDist, proximos);
    encontrarPokemonProximosUtil(node->direita,  xref, yref, minDist, proximos);
}

void encontrarPokemonProximos() {
    if (!raizPorNome) {
        cout << "Nenhum Pokemon cadastrado.\n\n";
        return;
    }

    int xref, yref;
    cout << ">> Encontrar Pokemon proximos <<\n";
    cout << "Informe as suas coordenadas (X e Y entre 1 e 10): ";
    cin >> xref >> yref;

    if (xref < 1 || xref > 10 || yref < 1 || yref > 10) {
        cout << "Coordenadas invalidas. Use valores entre 1 e 10.\n\n";
        return;
    }

    double minDist = 1e9; 
    list<Pokemon> proximos;

    encontrarPokemonProximosUtil(raizPorNome, xref, yref, minDist, proximos);

    if (proximos.empty()) {
        cout << "Nenhum Pokemon encontrado nas coordenadas fornecidas.\n\n";
        return;
    }

    cout << "\nPokemons mais proximos de (" << xref << "," << yref << "):\n";
    for (const auto& p : proximos) {
        cout << "- " << p.nome
                  << " (Tipo: " << p.tipo
                  << ", Codigo: " << p.num
                  << ", Coords: " << p.x << "," << p.y 
                  << ", Dist: " << minDist << ")\n";
    }
    cout << "\n";
}

// =========================
// Função principal (Menu)
// =========================
int main() {
    // Inicializa grafo e mapa
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            grafo[i][j] = -1;
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mapa[i][j] = 0;
        }
    }

    bool acabar = false;
    do {
        cout << "======= Pokedex =======\n\n"
             << "1. Cadastrar cidade\n"
             << "2. Cadastrar estrada\n"
             << "3. Buscar centro Pokemon mais proximo\n"
             << "4. Cadastrar Pokemon\n"
             << "5. Remover Pokemon\n"
             << "6. Listar Pokemon (Alfabetico)\n"
             << "7. Listar Pokemon (Por Tipo)\n"
             << "8. Contar Pokemon de um Tipo\n"
             << "9. Encontrar Pokemon proximos\n"
             << "10. Fechar Menu\n\n"
             << "Escolha uma opcao: ";
        int opcao;
        cin >> opcao;

        switch (opcao) {
            case 1:
                system("clear");
                cadastrarCidade();
                break;
            case 2:
                system("clear");
                cadastrarEstrada();
                break;
            case 3:
                system("clear");
                buscarCentroPokemonMaisProximo();
                break;
            case 4:
                system("clear");
                cadastrarPokemon();
                break;
            case 5:
                system("clear");
                removerPokemon();
                break;
            case 6:
                system("clear");
                cout << ">> Lista de Pokemons (ordenado por NOME) <<\n\n";
                listarPokemonsPorNome(raizPorNome);
                cout << "\n";
                break;
            case 7:
                system("clear");
                listarPokemonTipo();
                break;
            case 8:
                system("clear");
                contarPokemonTipo();
                break;
            case 9:
                system("clear");
                encontrarPokemonProximos();
                break;
            case 10:
                system("clear");
                cout << "Menu fechando...\n";
                acabar = true;
                break;
            default:
                cout << "Opcao invalida, escolha novamente.\n\n";
                break;
        }
    } while (!acabar);

    return 0;
}
