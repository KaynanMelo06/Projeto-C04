#include <iostream>

using namespace std;

void cadastrarCidade()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void cadastrarEstrada()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void buscarCentroPokemonMaisProximo()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void cadastrarPokemon()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void removerPokemon()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void listarPokemonAlfabetico()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void listarPokemonTipo()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void contarPokemonTipo()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

void encontrarPokemonProximos()
{
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*" << endl;
	cout << "------------------------------" << endl;
}

int main()
{
	bool acabar = false;

	do
	{
		cout << endl;
		cout << "Para teste, coloquei um loop infinito" << endl << endl;
		cout << "Pokedex" << endl
			 << endl
			 << "1. Cadastrar cidade" << endl
			 << "2. Cadastrar estrada" << endl
			 << "3. Buscar centro Pokemon mais proximo" << endl
			 << "4. Cadastrar Pokemon" << endl
			 << "5. Remover Pokemon" << endl
			 << "6. Listar Pokemon (Alfabetico)" << endl
			 << "7. Listar Pokemon (Tipo)" << endl
			 << "8. Contar Pokemon de cada tipo" << endl
			 << "9. Encontrar Pokemon proximos" << endl;

		int opcao;

		cin >> opcao;

		switch (opcao)
		{
		case 1:
			cadastrarCidade();
			break;
		case 2:
			cadastrarEstrada();
			break;
		case 3:
			buscarCentroPokemonMaisProximo();
			break;
		case 4:
			cadastrarPokemon();
			break;
		case 5:
			removerPokemon();
			break;
		case 6:
			listarPokemonAlfabetico();
			break;
		case 7:
			listarPokemonTipo();
			break;
		case 8:
			contarPokemonTipo();
			break;
		case 9:
			encontrarPokemonProximos();
			break;
		default:
			cout << "Opcao invalida" << endl;
			acabar = true;
			break;
		}

		
	} while (acabar == false);

	return 0;
}