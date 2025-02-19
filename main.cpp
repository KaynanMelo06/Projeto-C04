#include <iostream>

using namespace std;

void cadastrarCidade()
{
	cout << "Funcionalidade em construcao" << endl;
}

void cadastrarEstrada()
{
	cout << "Funcionalidade em construcao" << endl;
}

void buscarCentroPokemonMaisProximo()
{
	cout << "Funcionalidade em construcao" << endl;
}

void cadastrarPokemon()
{
	cout << "Funcionalidade em construcao" << endl;
}

void removerPokemon()
{
	cout << "Funcionalidade em construcao" << endl;
}

void listarPokemonAlfabetico()
{
	cout << "Funcionalidade em construcao" << endl;
}

void listarPokemonTipo()
{
	cout << "Funcionalidade em construcao" << endl;
}

void contarPokemonTipo()
{
	cout << "Funcionalidade em construcao" << endl;
}

void encontrarPokemonProximos()
{
	cout << "Funcionalidade em construcao" << endl;
}


// Comentario de teste foda-se





int main()

{
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
		break;
	}

	return 0;
}