#include <iostream>
#include <list>

using namespace std;

int main()
{
    //Iniciando a lista
    list<int> aula;
    int tam;
    tam = 10;

    //Inserindo elementos na lista
    for (int i = 0; i < tam; i++)
    {
        aula.push_front(i);
    }
    //Mostrando o tamanho da lista
    cout << "Tamanho da lista: " << aula.size() << "\n\n";

    //Mostrando os elementos da lista
    tam = aula.size();
    for (int i = 0; i < tam; i++)
    {
        cout << aula.back() << "\n";
        aula.pop_back();
    }

    return 0;
}