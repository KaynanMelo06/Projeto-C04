// Adições ao topo do arquivo (após os includes existentes)
#include <map>

// Struct original já existente: FEITO
struct Pokemon {
	string nome;
	string tipo;
	int num;
	int x, y;
};

// Nova struct para nó da árvore FEITO
struct NodePokemon {
	Pokemon info;
	NodePokemon* esquerda;
	NodePokemon* direita;
};

// Ponteiro global para a raiz da árvore de pokémons FEITO
NodePokemon* raizPokemon = nullptr;

// Inserção por nome FEITO
void inserirPokemon(NodePokemon*& raiz, const Pokemon& p) {
	if (!raiz) {
		raiz = new NodePokemon{p, nullptr, nullptr};
	} else if (p.nome < raiz->info.nome) {
		inserirPokemon(raiz->esquerda, p);
	} else {
		inserirPokemon(raiz->direita, p);
	}
}

// Impressão em ordem
void listarEmOrdem(NodePokemon* raiz) {
	if (raiz) {
		listarEmOrdem(raiz->esquerda);
		cout << "Nome: " << raiz->info.nome << ", Tipo: " << raiz->info.tipo
			 << ", Nº: " << raiz->info.num << ", Local: (" << raiz->info.x << "," << raiz->info.y << ")\n";
		listarEmOrdem(raiz->direita);
	}
}

// Remoção por nome FEITO
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

// Contar pokémons de um tipo
int contarTipo(NodePokemon* raiz, const string& tipo) {
	if (!raiz) return 0;
	int cont = (raiz->info.tipo == tipo) ? 1 : 0;
	return cont + contarTipo(raiz->esquerda, tipo) + contarTipo(raiz->direita, tipo);
}

// Mapear e imprimir pokémons por tipo
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
	cout << "Cadastrar Pokémon" << endl;
	do {
		cout << "Nome: ";
		cin.ignore();
		getline(cin, p.nome);
		cout << "Tipo: ";
		getline(cin, p.tipo);
		cout << "Número: ";
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
	cout << "Remover Pokémon - Digite o nome: ";
	cin.ignore();
	getline(cin, nome);
	if (removerPokemonPorNome(raizPokemon, nome))
		cout << nome << " removido com sucesso.\n";
	else
		cout << nome << " não encontrado.\n";
}

// Substituir listarPokemonAlfabetico(): feito
void listarPokemonAlfabetico() {
	cout << "Pokémons em ordem alfabética:\n";
	listarEmOrdem(raizPokemon);
}

// Substituir listarPokemonTipo():
void listarPokemonTipo() {
	map<string, vector<Pokemon>> mapaTipos;
	mapearPorTipo(raizPokemon, mapaTipos);
	for (auto& par : mapaTipos) {
		cout << "Tipo: " << par.first << endl;
		for (auto& p : par.second)
			cout << " - " << p.nome << " (Nº: " << p.num << ")\n";
	}
}

// Substituir contarPokemonTipo():
void contarPokemonTipo() {
	string tipo;
	cout << "Digite o tipo para contar: ";
	cin.ignore();
	getline(cin, tipo);
	int total = contarTipo(raizPokemon, tipo);
	cout << "Existem " << total << " pokémons do tipo " << tipo << ".\n";
}
