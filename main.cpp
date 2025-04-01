#include <iostream>
#include <list>	   // Biblioteca utilizada para manipulação de listas
#include <cstdlib> // Biblioteca utilizada para limpar o terminal, com o comando system("CLS");

using namespace std;

struct dadoscidade // Estrutura para armazenar os dados das cidades
{
	int codigo;
	string nome;
	bool pc;
};

// Variaveis globais
int ncidades = 0;
dadoscidade dados[50]; // Atribui a struct a variavel dados, com tamanho maximo de 50 cidades

void cadastrarCidade()
{
	char simnao; // Para armazenar a resposta S/N

	cout << "Digite o numero de cidades: " << endl;
	cin >> ncidades;

	while (ncidades <= 0) // Verifica se o numero de cidades é valido
	{
		cout << "Numero de cidades invalido, digite novamente: " << endl;
		cin >> ncidades;
	}

	for (int i = 0; i < ncidades; i++)
	{
		cout << "Nome da cidade " << i + 1 << ": ";
		getline(cin.ignore(), dados[i].nome);

		cout << "O codigo da cidade " << i + 1 << ": ";
		cin >> dados[i].codigo;

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
	// Criar e inicializar a matriz de adjacência com -1
	int grafo[ncidades][ncidades];

	for (int i = 0; i < ncidades; i++)
	{
		for (int j = 0; j < ncidades; j++)
		{
			grafo[i][j] = -1; // Inicializa todas as conexões como -1
		}
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

		if (cidade1 >= 0 && cidade1 < ncidades && cidade2 >= 0 && cidade2 < ncidades)
		{
			grafo[cidade1][cidade2] = distancia;
			grafo[cidade2][cidade1] = distancia; // Para grafos não direcionados
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

void buscarCentroPokemonMaisProximo()
{
	cout << "buscar centro pokemon mais proximo" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
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