#include <iostream>
#include <list>

using namespace std;

struct Pokemon
{
    string nome;
    float peso;
    string tipo;

    void exibir()
    {
        cout << "Nome: " << nome << "\nPeso: " << peso << "kg\nTipo: " << tipo << endl;
    }
};

int main()
{
    list<Pokemon> pokemons; // Criando uma lista de Pokémon

    // Adicionando Pokémon à lista
    pokemons.push_back({"Pikachu", 6.0, "Elétrico"});
    pokemons.push_back({"Magikarp", 3.0, "Água"});
    pokemons.push_back({"Charizard", 90.5, "Fogo"});
    pokemons.push_back({"Bulbasaur", 6.9, "Planta/Veneno"});

    // Exibindo todos os Pokémon da lista
    cout << "Lista de Pokémon:\n";

    // Pokemon& p, declara uma referencia (&) para um elemento da lista pokemons
    // : pokemons, significa que p irá percorrer todos os elementos da lista pokemons
    for (Pokemon &p : pokemons)
    {
        p.exibir();
        cout << "-----------------\n";
    }

    return 0;
}
