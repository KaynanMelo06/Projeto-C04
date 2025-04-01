#include <iostream>
#include <list> // Biblioteca utilizada para manipulação de listas
#include <cstdlib> // Biblioteca utilizada para limpar o terminal, com o comando system("CLS");

using namespace std;
	
struct dadoscidade // Estrutura para armazenar os dados das cidades
{
	int codigo;
	string nome;
	bool pc;
	
	int ncidades;
};

void cadastrarCidade()
{
	dadoscidade dados[50]; // Atribui a struct a variavel dados, com tamanho maximo de 50 cidades
	dadoscidade ncidade; // Atribui a struct a variavel ncidade, que armazena o numero de cidades
	char simnao; // Para armazenar a resposta S/N

	cout << "Digite o numero de cidades: " << endl;  
	cin >> ncidade.ncidades;

	while(ncidade.ncidades <= 0) // Verifica se o numero de cidades é valido
	{
		cout << "Numero de cidades invalido, digite novamente: " << endl;
		cin >> ncidade.ncidades;
	}
	
	for(int i = 0; i < ncidade.ncidades; i++)
	{
		cout << "Nome da cidade " << i+1 << ": ";
		getline(cin >> ws, dados[i].nome);  // Jeito de utilizar strings. WS = cin.ignore().
		
		cout << "O codigo da cidade " << i+1 << ": ";
		cin >> dados[i].codigo;	
		
		cout << "Essa cidade possui centro pokemon: S/N? " << endl;
		cin >> simnao;

		if(simnao == 'S' || simnao == 's')
		{
			dados[i].pc = true;
		}
		else
		{
			dados[i].pc = false;
		}
	
	}

	system("CLS");

	for(int i = 0; i < ncidade.ncidades; i++) // Teste
		{
			cout << "Cidade " << i+1 << ": " << dados[i].nome << endl;
			cout << "Codigo: " << dados[i].codigo << endl;
			cout << "Possui CP: " << dados[i].pc << endl;
		}
	

}

struct estrada {
	int cidade1;
	int cidade2;
	float distancia;
};

void cadastrarEstrada() 
{

	list<estrada> estradas; // Lista para armazenar as estradas

	int cidade1, cidade2;
	float distancia;
	char continuar;

	do {
		cout << "Digite o codigo da primeira cidade: ";
		cin >> cidade1;

		cout << "Digite o codigo da segunda cidade: ";
		cin >> cidade2;

		cout << "Digite a distancia entre as cidades: ";
		cin >> distancia;

		estrada novaEstrada = {cidade1, cidade2, distancia};
		estradas.push_back(novaEstrada);

		cout << "Deseja cadastrar outra estrada? (S/N): ";
		cin >> continuar;

	} while (continuar == 'S' || continuar == 's');

	system("CLS");

	cout << "Estradas cadastradas:" << endl;
	for (list<estrada>::const_iterator it = estradas.begin(); it != estradas.end(); ++it) {
		cout << "Cidade 1: " << it->cidade1 << ", Cidade 2: " << it->cidade2
			 << ", Distancia: " << it->distancia << " km" << endl;
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