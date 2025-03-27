#include <iostream>
#include <cstring> // Biblioteca utilizada para manipulação de strings
#include <list> // Biblioteca utilizada para manipulação de listas
#include <cstdlib> // Biblioteca utilizada para limpar o terminal, com o comando system("CLS");

using namespace std;

struct DadosCidade
{
	char nomecidades[50];
};


void cadastrarCidade()
{
	int ncidades;
	DadosCidade cidades[50];

	cout << "Digite o numero de cidades: " << endl;
	cin >> ncidades;
	cin.ignore(); // Evita problemas com o cin.getline 

	while(ncidades <= 0)
	{
		cout << "Numero de cidades invalido, digite novamente: " << endl;
		cin >> ncidades;
	}

	cout << "Digite o nome das cidades: " << endl;
	
	for(int i = 0; i < ncidades; i++)
	{
		cout << "Cidade " << i+1 << ": ";
		cin.getline(cidades[i].nomecidades, 50);
	}

	for(int i = 0; i < ncidades; i++)
	{
		cout << cidades[i].nomecidades << endl;
	}
	
	

}

void cadastrarEstrada()
{
	cout << "cadastrar estrada" << endl;
	cout << "------------------------------" << endl;
	cout << "*Funcionalidade em construcao*  RETORNANDO PARA O MENU" << endl;
	cout << "------------------------------" << endl;
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