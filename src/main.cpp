#include <iostream>
#include <list>	   // Biblioteca utilizada para manipulaa§a£o de listas
#include <cstdlib> // Biblioteca utilizada para limpar o terminal, com o comando system("CLS");
#include <cstring> // Biblioteca utilizada para Strings
#include <climits> // Biblioteca para definir um valor maximo muito alto (ex. INT_MAX)
#include <map>	   // Biblioteca para mapear os tipos de pokemons
#include <string> // Biblioteca para manipulaa§a£o de strings


#define INF 999999

using namespace std;

struct Pokemon { // Struct para os dados dos pokemons
	string nome;
	string tipo;
	int num;
	int x, y; // Coordenadas do pokemon no mapa
};

// Nova struct para no da arvore
struct NodePokemon {
	Pokemon info;
	NodePokemon* esquerda;
	NodePokemon* direita;
};

// Ponteiro global para a raiz da arvore de pokemons
NodePokemon* raizPokemon = NULL;




struct dadoscidade // Estrutura para armazenar os dados das cidades
{
	int codigo;
	string nome;
	bool pc;
};


// Variaveis globais
int ncidades = 0;	   // Quantidade de cidades cadastradas.
dadoscidade dados[50]; // Atribui a struct a variavel dados, com tamanho maximo de 50 cidades.
bool achou = false;
int mapa[10][10];
int grafo[50][50]; // Criar e inicializar a matriz de adjacencia

void cadastrarCidade()
{
	char simnao; // Para armazenar a resposta S/N
	int temp;

	cout << "Digite o numero de cidades: " << endl;
	cin >> temp;

	ncidades = ncidades + temp;

	while (ncidades <= 0) // Verifica se o numero de cidades e valido1
	{
		cout << "Numero de cidades invalido, digite novamente: " << endl;
		cin >> ncidades;
	}

	for (int i = 0; i < ncidades; i++)
	{
		cout << "Nome da cidade " << i + 1 << ": ";
		getline(cin.ignore(), dados[i].nome);

		dados[i].codigo = i + 1;
		cout << "O codigo da cidade " << i + 1 << ": " << dados[i].codigo << endl;

		/*
		cout << "O codigo da cidade " << i + 1 << " entre 1 e " << ncidades << ": ";
		cin >> dados[i].codigo;
<<<<<<< HEAD
		//checar se codigo ja foi utilizado
		for (int j = 0; j < i; j++)
		{
			if (dados[i].codigo == dados[j].codigo)
			{
				cout << "Codigo ja utilizado. digite novamente: " << endl;
				cin >> dados[i].codigo;
				j = -1;
			}
		}
=======
		*/
>>>>>>> 9935f5799fcdb99bf33e70d4ccfc939ae90ef179

		while (dados[i].codigo < 1 || dados[i].codigo > ncidades)
		{
			cout << "Codigo invalido. Digite novamente (entre 1 e " << ncidades << "): ";
			cin >> dados[i].codigo;
		}

		cout << "Essa cidade possui centro pokemon: S/N? " << endl;
		cin >> simnao;

		if (simnao == 'S' || simnao == 's')
		{
			dados[i].pc = true;
		}
		else
		{
			dados[i].pc = false;
		}
	}

	system("CLS");

	for (int i = 0; i < ncidades; i++) // Teste
	{
		cout << "Cidade " << i + 1 << ": " << dados[i].nome << endl;
		cout << "Codigo: " << dados[i].codigo << endl;
		cout << "Possui CP: " << dados[i].pc << endl;
	}
}

void cadastrarEstrada()
{

	if (ncidades <= 0)
	{ // Verifica se ha cidades cadastradas
		cout << "Nenhuma cidade cadastrada. Cadastre cidades primeiro!" << endl;
		return;
	}
	cout << "Cidades cadastradas: " << endl;
	for (int i = 0; i < ncidades; i++) // Para ver as cidades cadastradas
	{
		cout << "Cidade " << i + 1 << ": " << dados[i].nome << endl;
		cout << "Codigo: " << dados[i].codigo << endl;
		cout << " " << endl;
	}
	int cidade1, cidade2, distancia;

	char continuar;
	do
	{

		cout << "Digite o codigo da primeira cidade: ";
		cin >> cidade1;
		cout << "Digite o codigo da segunda cidade: ";
		cin >> cidade2;
		cout << "Digite a distancia entre as cidades: ";
		cin >> distancia;
		cout << endl;

		if (cidade1 >= 0 && cidade1 <= ncidades && cidade2 >= 0 && cidade2 <= ncidades)
		{
			grafo[cidade1 - 1][cidade2 - 1] = distancia; //-1 Por conta da matriz comecar em 0
			grafo[cidade2 - 1][cidade1 - 1] = distancia; // Grafo nao direcionado
		}
		else
		{
			cout << "Codigos de cidades invalidos. Tente novamente." << endl;
			cout << endl;
		}

		cout << "Deseja cadastrar outra estrada? (S/N): ";
		cin >> continuar;

	} while (continuar == 'S' || continuar == 's');

	// Exibir a matriz de adjacencia
	cout << "Matriz de Adjacencia:" << endl;
	for (int i = 0; i < ncidades; i++)
	{
		for (int j = 0; j < ncidades; j++)
		{
			cout << grafo[i][j] << " ";
		}
		cout << endl;
	}
}

// Funcao que procura um termo dentro de um vetor dividindo ele ao meio quantas vezes necessario.
// nao ta sendo usado, mas e bom saber que existe.

int binaria_recursiva(dadoscidade dados[], int x, int baixo, int alto)
{
	if (baixo <= alto && achou == false)
	{
		int meio = (baixo + alto) / 2;

		if (x == dados[meio].codigo)
		{
			achou = true;
			return meio;
		}
		else if (x < dados[meio].codigo)
		{
			return binaria_recursiva(dados, x, baixo, meio - 1); // Recursividade, dividindo o vetor da metade pra baixo.
		}
		else if (x > dados[meio].codigo)
		{
			return binaria_recursiva(dados, x, meio + 1, alto); // Dividindo o vetor da metade pra cima.
		}
	}
}

struct Aresta
{
	int origem, destino, peso;
};

// Funcao para converter a matriz de adjacencia para uma lista de adjacencia
void converterParaListaAdjacencia(list<Aresta> grafoLista[], int grafoMatriz[50][50], int ncidades)
{
	for (int i = 0; i < ncidades; i++)
	{
		for (int j = 0; j < ncidades; j++)
		{
			if (grafoMatriz[i][j] != -1)
			{ // Apenas adiciona arestas validas
				grafoLista[i].push_back({i, j, grafoMatriz[i][j]});
			}
		}
	}
}

/*
funcao dikstra para encontrar a distancia mais curta entre dois pontos
onde o prim ja nos deu o ponto de destino mais proximo
e o dijkstra vai nos dar a distancia entre o ponto de origem e o ponto de destino mais proximo
Basicamente se usar apenas o prim, em alguns casos ele nos da a distancia errada, porem o destino que ele retorna esta sempre correto
Por isso o uso do dijkstra
*/
int dijkstra_lista(list<Aresta>grafo[], int vertices, int origem, int destino)
{
    bool visitado[vertices];
    int pais [vertices], distancia[vertices], atual;

    for(int i = 0; i < vertices; i++)
    {
        visitado[i] = false;
        pais[i] = -1;
        distancia[i] = INF;
    }
    distancia[origem] = 0;
    atual = origem;

    while(!visitado[atual])
    {
        visitado[atual] = true;
        
        list<Aresta>::iterator it; 
        
        for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)
        {
            int d = it->destino, p = it->peso;
            
            if(!visitado[d] && distancia[atual] + p < distancia[d])
            {
                distancia[d] = distancia[atual] + p;
                pais[d] = atual;
            }
        
        }
        int menor_peso = INF;
        for(int i = 0; i< vertices; i++)
        {
            if(!visitado[i] && distancia[i] < menor_peso)
            {
                menor_peso = distancia[i];
                atual = i;
            }
        }
    }
    atual = destino;
    
    return distancia[destino];
}

// Algoritmo de Prim adaptado para encontrar o Centro Pokemon mais proximo
int primCentroPokemonMaisProximo(list<Aresta> grafo[], int vertices, int origem, dadoscidade dados[])
{	
	// Vetor para marcar os vertices visitados
	bool visitado[vertices];
	// Vetor para armazenar as menores distancias de cada vertice
	int distancia[vertices], atual;

	// Inicializa os vetores de visitados e distancias
	for (int i = 0; i < vertices; i++)
	{
		visitado[i] = false; // Nenhum vertice foi visitado ainda
		distancia[i] = INF;	 // Define todas as distancias como "infinito"
	}

	// Define o vertice de origem e sua distancia inicial como 0
	atual = origem;
	distancia[atual] = 0;

	// Enquanto houver vertices nao visitados
	while (!visitado[atual])
	{
		visitado[atual] = true; // Marca o vertice atual como visitado

		// Verifica se a cidade atual possui um Centro Pokemon
		if (dados[atual].pc)
		{
			// Se encontrar um Centro Pokemon, exibe a cidade e a distancia
			cout << "O Centro Pokemon mais proximo esta na cidade: " << dados[atual].nome << endl;
			cout << "distancia: " << dijkstra_lista(grafo, vertices, origem, atual) << endl; // Chama o dijkstra para obter a menor dintancia
			return distancia[atual]; // Retorna a distancia encontrada
		}

		// Atualiza as distancias para as cidades vizinhas
		list<Aresta>::iterator it;
		for (it = grafo[atual].begin(); it != grafo[atual].end(); it++)
		{
			int d = it->destino, p = it->peso;
			// Se o vizinho nao foi visitado e a nova distancia e menor, atualiza
			if (!visitado[d] && p < distancia[d])
			{
				distancia[d] = p;
			}
		}

		// Encontra o proximo vertice com a menor distancia
		int menor_distancia = INF;
		for (int i = 0; i < vertices; i++)
		{
			if (!visitado[i] && distancia[i] < menor_distancia)
			{
				menor_distancia = distancia[i];
				atual = i; // Atualiza o proximo vertice a ser visitado
			}	
		}
	}

	// Se nenhum Centro Pokemon for encontrado, exibe mensagem
	cout << "Nenhum Centro Pokemon encontrado acessivel a partir da cidade atual." << endl;
	return -1; // Retorna -1 para indicar falha
}

// Funcao para buscar o Centro Pokemon mais proximo
void buscarCentroPokemonMaisProximo()
{
	if (ncidades <= 0)
	{
		cout << "Nenhuma cidade cadastrada. Cadastre cidades primeiro!" << endl;
		return;
	}

	int cidadeAtual;
	cout << "Digite o codigo da sua cidade atual: ";
	cin >> cidadeAtual;

	if (cidadeAtual < 1 || cidadeAtual > ncidades)
	{
		cout << "Codigo de cidade invalido!" << endl;
		return;
	}

	cidadeAtual--; // Ajustar para indice da matriz (0-based)

	// Converter a matriz de adjacencia para uma lista de adjacencia
	list<Aresta> grafoLista[50];
	converterParaListaAdjacencia(grafoLista, grafo, ncidades);

	// Chamar o algoritmo de Prim adaptado
	primCentroPokemonMaisProximo(grafoLista, ncidades, cidadeAtual, dados);
}

void inserirPokemon(NodePokemon*& raiz, const Pokemon& p) {
	if (!raiz) {
		raiz = new NodePokemon;
		raiz->info = p;
		raiz->esquerda = NULL;
		raiz->direita = NULL;
	} else if (p.nome < raiz->info.nome) {
		inserirPokemon(raiz->esquerda, p);
	} else {
		inserirPokemon(raiz->direita, p);
	}
}


void cadastrarPokemon()
{
	Pokemon p;
	char continuar;
	cout << "Cadastrar Pokemon" << endl;
	do {
		cout << "Nome: ";
		cin.ignore();
		getline(cin, p.nome);
		cout << "Tipo: ";
		getline(cin, p.tipo);
		cout << "Numero: ";
		cin >> p.num;
		cout << "Coordenadas (x y): ";
		cin >> p.x >> p.y;
		mapa[p.x-1][p.y-1] = 1;
		inserirPokemon(raizPokemon, p);
		cout << "Cadastrar outro? (S/N): ";
		cin >> continuar;
	} while (continuar == 'S' || continuar == 's');
}

// Remocao por nome que e chamado em removerPokemon()
// A funcao percorre a arvore e remove o no correspondente ao nome do Pokemon
bool removerPokemonPorNome(NodePokemon*& raiz, const string& nome) {
	if (!raiz) return false;
	if (nome < raiz->info.nome) return removerPokemonPorNome(raiz->esquerda, nome);
	if (nome > raiz->info.nome) return removerPokemonPorNome(raiz->direita, nome);

	NodePokemon* temp = raiz;
	if (!raiz->esquerda) raiz = raiz->direita;
	else if (!raiz->direita) raiz = raiz->esquerda;
	else {
		NodePokemon** pred = &raiz->esquerda;
		while ((*pred)->direita) pred = &(*pred)->direita;
		raiz->info = (*pred)->info;
		temp = *pred;
		*pred = (*pred)->esquerda;
	}
	delete temp;
	return true;
}

void removerPokemon() {
	string nome;
	cout << "Remover Pokemon - Digite o nome: ";
	cin.ignore();
	getline(cin, nome);
	if (removerPokemonPorNome(raizPokemon, nome))
		cout << nome << " removido com sucesso.\n";
	else
		cout << nome << " nao encontrado.\n";
}

// Impressao em ordem
void listarEmOrdem(NodePokemon* raiz) {
	if (raiz) {
		listarEmOrdem(raiz->esquerda);
		cout << "Nome: " << raiz->info.nome << ", Tipo: " << raiz->info.tipo
			 << ", Num: " << raiz->info.num << ", Local: (" << raiz->info.x << "," << raiz->info.y << ")\n";
		listarEmOrdem(raiz->direita);
	}
}

void listarPokemonAlfabetico() {
	cout << "Pokemons em ordem alfabetica:\n";
	listarEmOrdem(raizPokemon);
}

// Funcoes auxiliares:
void listarPorTipo(NodePokemon* raiz, const string& tipo, int& cont) {
    if (!raiz) return;
    listarPorTipo(raiz->esquerda, tipo, cont);
    if (raiz->info.tipo == tipo) {
        cout << "- " << raiz->info.nome
             << " (Numero: " << raiz->info.num 
             << ", Coords: " << raiz->info.x << "," << raiz->info.y << ")\n";
        cont++;
    }
    listarPorTipo(raiz->direita, tipo, cont);
}

void contarPorTipo(NodePokemon* raiz, const string& tipo, int& cont) {
    if (!raiz) return;
    if (raiz->info.tipo == tipo) cont++;
    contarPorTipo(raiz->esquerda, tipo, cont);
    contarPorTipo(raiz->direita, tipo, cont);
}

// Implementacao de listarPokemonTipo():
void listarPokemonTipo() {
    if (!raizPokemon) {
        cout << "Nenhum Pokemon cadastrado.\n";
        return;
    }
    string tipoBusca;
    cout << "Digite o tipo do Pokemon: ";
    cin.ignore(100000, '\n');
    getline(cin, tipoBusca);

    cout << "\nPokemons do tipo '" << tipoBusca << "':\n";
    cout << "------------------------------\n";
    int cont = 0;
    listarPorTipo(raizPokemon, tipoBusca, cont);
    if (cont == 0) {
        cout << "  * Nenhum Pokemon do tipo '" << tipoBusca << "' encontrado.\n";
    }
    cout << "------------------------------\n\n";
}

// Implementacao de contarPokemonTipo():
void contarPokemonTipo() {
    if (!raizPokemon) {
        cout << "Nenhum Pokemon cadastrado.\n";
        return;
    }
    string tipoBusca;
    cout << "Digite o tipo do Pokemon: ";
    cin.ignore(100000, '\n');
    getline(cin, tipoBusca);

    int cont = 0;
    contarPorTipo(raizPokemon, tipoBusca, cont);
    cout << "\nTotal de Pokemon(s) do tipo '" 
         << tipoBusca << "': " << cont << "\n\n";
}

void encontrarPokemonProximos()
{
	cout << "encontrar pokemon proximos" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
}

int main()
{
	bool acabar = false;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			grafo[i][j] = -1; // Inicializa todas as conexoes como -1
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mapa[i][j] = 0; // Inicializa todo mapa como 0
		}
	}


	do
	{

		cout << "Pokedex:" << endl
			 << endl
			 << "1. Cadastrar cidade" << endl
			 << "2. Cadastrar estrada" << endl
			 << "3. Buscar centro Pokemon mais proximo" << endl
			 << "4. Cadastrar Pokemon" << endl
			 << "5. Remover Pokemon" << endl
			 << "6. Listar Pokemon (Alfabetico)" << endl
			 << "7. Listar Pokemon (Tipo)" << endl
			 << "8. Contar Pokemon de cada tipo" << endl
			 << "9. Encontrar Pokemon proximos" << endl
			 << "10. Fechar Menu" << endl;

		int opcao;

		cin >> opcao;

		switch (opcao)
		{
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
			cadastrarPokemon();
			break;
		case 5:
			system("CLS");
			removerPokemon();
			break;
		case 6:
			system("CLS");
			listarPokemonAlfabetico();
			break;
		case 7:
			system("CLS");
			listarPokemonTipo();
			break;
		case 8:
			system("CLS");
			contarPokemonTipo();
			break;
		case 9:
			system("CLS");
			encontrarPokemonProximos();
			break;
		case 10:
			system("CLS");
			cout << "Menu fechando...";
			acabar = true;
			break;
		default:
			cout << "Opcao invalida, escolha novamente a opcao" << endl;
			break;
		}

	} while (acabar == false);

	return 0;
}