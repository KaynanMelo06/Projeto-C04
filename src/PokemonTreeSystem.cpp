// Adi  es ao topo do arquivo (ap s os includes existentes)
#include <iostream>
#include <map>
#include <string>
using namespace std;

// Struct original j  existente: FEITO
struct Pokemon { // Struct para os dados dos pokemons
	string nome;
	string tipo;
	int num;
	int x, y; // Coordenadas do pokemon no mapa
};

// Nova struct para n  da  rvore FEITO
struct NodePokemon {
	Pokemon info;
	NodePokemon* esquerda;
	NodePokemon* direita;
};

// Ponteiro global para a raiz da  rvore de pok mons FEITO
NodePokemon* raizPokemon = nullptr;

// Inser  o por nome FEITO
void inserirPokemon(NodePokemon*& raiz, const Pokemon& p) {
	if (!raiz) {
		raiz = new NodePokemon{p, nullptr, nullptr};
	} else if (p.nome < raiz->info.nome) {
		inserirPokemon(raiz->esquerda, p);
	} else {
		inserirPokemon(raiz->direita, p);
	}
}
void listarEmOrdemtipo(NodePokemon* raiz, string tipo) {
	string type;
	if (raiz && type = tipo) {
		listarEmOrdem(raiz->esquerda);
		cout << "Nome: " << raiz->info.nome << ", Tipo: " << raiz->info.tipo
			 << ", N : " << raiz->info.num << ", Local: (" << raiz->info.x << "," << raiz->info.y << ")\n";
		listarEmOrdem(raiz->direita);
	}
}
// Impress o em ordem
void listarEmOrdem(NodePokemon* raiz) {
	if (raiz) {
		listarEmOrdem(raiz->esquerda);
		cout << "Nome: " << raiz->info.nome << ", Tipo: " << raiz->info.tipo
			 << ", N : " << raiz->info.num << ", Local: (" << raiz->info.x << "," << raiz->info.y << ")\n";
		listarEmOrdem(raiz->direita);
	}
}

// Remo  o por nome FEITO
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

// Contar pok mons de um tipo
int contarTipo(NodePokemon* raiz, const string& tipo) {
	if (!raiz) return 0;
	int cont = (raiz->info.tipo == tipo) ? 1 : 0;
	return cont + contarTipo(raiz->esquerda, tipo) + contarTipo(raiz->direita, tipo);
}

// Mapear e imprimir pok mons por tipo
void mapearPorTipo(NodePokemon* raiz, map<string, vector<Pokemon>>& mapaTipos) {
	if (!raiz) return;
	mapearPorTipo(raiz->esquerda, mapaTipos);
	mapaTipos[raiz->info.tipo].push_back(raiz->info);
	mapearPorTipo(raiz->direita, mapaTipos);
}

// Substituir cadastrarPokemon():  FEITO
void cadastrarPokemon() {
	Pokemon p;
	char continuar;
	cout << "Cadastrar Pok mon" << endl;
	do {
		cout << "Nome: ";
		cin.ignore();
		getline(cin, p.nome);
		cout << "Tipo: ";
		getline(cin, p.tipo);
		cout << "N mero: ";
		cin >> p.num;
		cout << "Coordenadas (x y): ";
		cin >> p.x >> p.y;
		mapa[p.x-1][p.y-1] = 1;
		inserirPokemon(raizPokemon, p);
		cout << "Cadastrar outro? (S/N): ";
		cin >> continuar;
	} while (continuar == 'S' || continuar == 's');
}

// Substituir removerPokemon(): feito
void removerPokemon() {
	string nome;
	cout << "Remover Pok mon - Digite o nome: ";
	cin.ignore();
	getline(cin, nome);
	if (removerPokemonPorNome(raizPokemon, nome))
		cout << nome << " removido com sucesso.\n";
	else
		cout << nome << " n o encontrado.\n";
}

// Substituir listarPokemonAlfabetico(): feito
void listarPokemonAlfabetico() {
	cout << "Pok mons em ordem alfab tica:\n";
	listarEmOrdem(raizPokemon);
}

// Substituir listarPokemonTipo():
void listarPokemonTipo() {
	map<string, vector<Pokemon>> mapaTipos;
	mapearPorTipo(raizPokemon, mapaTipos);
	for (auto& par : mapaTipos) {
		cout << "Tipo: " << par.first << endl;
		for (auto& p : par.second)
			cout << " - " << p.nome << " (N : " << p.num << ")\n";
	}
}

// Substituir contarPokemonTipo():
void contarPokemonTipo() {
	string tipo;
	cout << "Digite o tipo para contar: ";
	cin.ignore();
	getline(cin, tipo);
	int total = contarTipo(raizPokemon, tipo);
	cout << "Existem " << total << " pok mons do tipo " << tipo << ".\n";
}