#include <iostream>
#include <list>	   // Biblioteca utilizada para manipulação de listas
#include <cstdlib> // Biblioteca utilizada para limpar o terminal, com o comando system("CLS");
#include <cstring> // Biblioteca utilizada para Strings
#include <climits> // Biblioteca para definir um valor maximo muito alto (ex. INT_MAX)

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

		/*
		dados[i].codigo = i + 1;
		cout << "O codigo da cidade " << i + 1 << ": " << dados[i].codigo << endl;
		*/
		
		cout << "O codigo da cidade " << i + 1 << " entre 1 e " << ncidades << ": ";
		cin >> dados[i].codigo;
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

		if (cidade1 >= 0 && cidade1 <= ncidades && cidade2 >= 0 && cidade2 <= ncidades)
		{
			grafo[cidade1 - 1][cidade2 - 1] = distancia; //-1 Por conta da matriz começar em 0 (ISSO QUE EU TAVA FALANDO KAYNAN, CARAIO)
			grafo[cidade2 - 1][cidade1 - 1] = distancia; // Grafo não direcionado
		}
		else
		{
			cout << "Codigos de cidades invalidos. Tente novamente." << endl;
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



void buscarCentroPokemonMaisProximo()
{
	int ID, indice;

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

	cout << "Digite o ID/codigo da sua cidade:" << endl;
	cin >> ID;

	indice = binaria_recursiva(dados, ID, 0, ncidades - 1);

	if (achou == false)
	{
		cout << "Cidade nao cadastrada." << endl;
		cout << "__________________________________________________" << endl;
		return;
	}
	else
	{
		if (dados[indice].pc == true)
		{
			char simnao;
			cout << dados[indice].nome << " ja possui um centro pokemon!" << endl;
			cout << "Deseja encontrar outro? (S/N)" << endl;
			cin >> simnao;

			if (simnao == 'S' || simnao == 's')
			{
				cout << "puxar funcao" << endl;
			}
			else
			{
				cout << "__________________________________________________" << endl;
				return;
			}
		}
		else
		{
			cout << "Cidades proximas: " << endl;
			achou = false;
		}
	}

	/*
	se ja estiver na cidade com CP, perguntar se deseja encontrar outra*/
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