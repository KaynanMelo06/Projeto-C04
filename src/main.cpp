#include <iostream>
#include <list>	   // Biblioteca utilizada para manipulação de listas
#include <cstdlib> // Biblioteca utilizada para limpar o terminal, com o comando system("CLS");
#include <cstring> // Biblioteca utilizada para Strings
#include <climits> // Biblioteca para definir um valor maximo muito alto (ex. INT_MAX)

#define INF 999999

using namespace std;

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
int grafo[50][50]; // Criar e inicializar a matriz de adjacencia

void cadastrarCidade()
{
	char simnao; // Para armazenar a resposta S/N
	int temp;

	cout << "Digite o numero de cidades: " << endl;
	cin >> temp;

	ncidades = ncidades + temp;

	while (ncidades <= 0) // Verifica se o numero de cidades é valido1
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
		*/

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
	{ // Verifica se há cidades cadastradas
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

	char continuar;
	do
	{
		int cidade1, cidade2, distancia;

		cout << "Digite o codigo da primeira cidade: ";
		cin >> cidade1;
		cout << "Digite o codigo da segunda cidade: ";
		cin >> cidade2;
		cout << "Digite a distancia entre as cidades: ";
		cin >> distancia;
		cout << endl;

		if (cidade1 >= 0 && cidade1 <= ncidades && cidade2 >= 0 && cidade2 <= ncidades)
		{
			grafo[cidade1 - 1][cidade2 - 1] = distancia; //-1 Por conta da matriz começar em 0 (ISSO QUE EU TAVA FALANDO KAYNAN, CARAIO)
			grafo[cidade2 - 1][cidade1 - 1] = distancia; // Grafo não direcionado
		}
		else
		{
			cout << "Codigos de cidades invalidos. Tente novamente." << endl;
			cout << endl;
		}

		cout << "Deseja cadastrar outra estrada? (S/N): ";
		cin >> continuar;

	} while (continuar == 'S' || continuar == 's');

	// Exibir a matriz de adjacência
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

// Função que procura um termo dentro de um vetor dividindo ele ao meio quantas vezes necessário.
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

// Fun��o para converter a matriz de adjac�ncia para uma lista de adjac�ncia
void converterParaListaAdjacencia(list<Aresta> grafoLista[], int grafoMatriz[50][50], int ncidades)
{
	for (int i = 0; i < ncidades; i++)
	{
		for (int j = 0; j < ncidades; j++)
		{
			if (grafoMatriz[i][j] != -1)
			{ // Apenas adiciona arestas v�lidas
				grafoLista[i].push_back({i, j, grafoMatriz[i][j]});
			}
		}
	}
}

// Algoritmo de Prim adaptado para encontrar o Centro Pok�mon mais pr�ximo
int primCentroPokemonMaisProximo(list<Aresta> grafo[], int vertices, int origem, dadoscidade dados[])
{
	// Vetor para marcar os v�rtices visitados
	bool visitado[vertices];
	// Vetor para armazenar as menores dist�ncias de cada v�rtice
	int distancia[vertices], atual;

	// Inicializa os vetores de visitados e dist�ncias
	for (int i = 0; i < vertices; i++)
	{
		visitado[i] = false; // Nenhum v�rtice foi visitado ainda
		distancia[i] = INF;	 // Define todas as dist�ncias como "infinito"
	}

	// Define o v�rtice de origem e sua dist�npcia inicial como 0
	atual = origem;
	distancia[atual] = 0;

	// Enquanto houver v�rtices n�o visitados
	while (!visitado[atual])
	{
		visitado[atual] = true; // Marca o v�rtice atual como visitado

		// Verifica se a cidade atual possui um Centro Pok�mon
		if (dados[atual].pc)
		{
			// Se encontrar um Centro Pok�mon, exibe a cidade e a dist�ncia
			cout << "O Centro Pokemon mais proximo est� na cidade: " << dados[atual].nome << endl;
			cout << "Distancia: " << distancia[atual] << endl;
			return distancia[atual]; // Retorna a dist�ncia encontrada
		}

		// Atualiza as dist�ncias para as cidades vizinhas
		list<Aresta>::iterator it;
		for (it = grafo[atual].begin(); it != grafo[atual].end(); it++)
		{
			int d = it->destino, p = it->peso;
			// Se o vizinho n�o foi visitado e a nova dist�ncia � menor, atualiza
			if (!visitado[d] && p < distancia[d])
			{
				distancia[d] = p;
			}
		}

		// Encontra o pr�ximo v�rtice com a menor dist�ncia
		int menor_distancia = INF;
		for (int i = 0; i < vertices; i++)
		{
			if (!visitado[i] && distancia[i] < menor_distancia)
			{
				menor_distancia = distancia[i];
				atual = i; // Atualiza o pr�ximo v�rtice a ser visitado
			}
		}
	}

	// Se nenhum Centro Pok�mon for encontrado, exibe mensagem
	cout << "Nenhum Centro Pokemon encontrado acessivel a partir da cidade atual." << endl;
	return -1; // Retorna -1 para indicar falha
}

// Fun��o para buscar o Centro Pok�mon mais pr�ximo
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

	cidadeAtual--; // Ajustar para �ndice da matriz (0-based)

	// Converter a matriz de adjac�ncia para uma lista de adjac�ncia
	list<Aresta> grafoLista[50];
	converterParaListaAdjacencia(grafoLista, grafo, ncidades);

	// Chamar o algoritmo de Prim adaptado
	primCentroPokemonMaisProximo(grafoLista, ncidades, cidadeAtual, dados);
}

void cadastrarPokemon()
{
	cout << "cadastrar pokemon" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
}

void removerPokemon()
{
	cout << "remover pokemon" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
}

void listarPokemonAlfabetico()
{
	cout << "listar pokemon alfabetico" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
}

void listarPokemonTipo()
{
	cout << "listar pokemon tipo" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
}

void contarPokemonTipo()
{
	cout << "contar pokemon tipo" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
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
			grafo[i][j] = -1; // Inicializa todas as conexões como -1
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