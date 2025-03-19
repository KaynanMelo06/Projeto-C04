#include <iostream>
#include <string>

using namespace std;

// Função de busca binária recursiva
int buscaPoneglyph(string ilhas[], int esquerda, int direita, string pista)
{
    if (esquerda <= direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        // Se a pista for encontrada, retorna o índice
        if (ilhas[meio] == pista)
        {
            return meio;
        }
       
        // Se a pista for menor, busca na metade esquerda
        if (ilhas[meio] > pista)
        {
            return buscaPoneglyph(ilhas, esquerda, meio - 1, pista);
        }

        // Se a pista for maior, busca na metade direita
        else
        {
            return buscaPoneglyph(ilhas, meio + 1, direita, pista);
        }
    }
    return -1; // Pista não encontrada
}

int main()
{
    const int tam_max = 100;
    string ilhas[tam_max];
    int n = 0;
    string nome;

    while (true){

        getline(cin, nome);
        bool repetido = false;
        for (int i = 0; i < n; i++)
        {
            if (ilhas[i] == nome)
            {
                repetido = true;
                break;
            }
        }
        if (repetido)
        {
            break;
        }
        ilhas[n++] = nome;

    }
    

    // Última ilha digitada é a pista a ser buscada
    string pista = nome;

    // Chama a função de busca binária 0 = inicio do vetor, n - 2 = final do vetor
    int indice = buscaPoneglyph(ilhas, 0, n - 2, pista);

    // Exibe o resultado
    if (indice != -1)
    {
        cout << "Índice da pista encontrada: " << indice << endl;
    }
    else
    {
        cout << "Poneglyph não encontrada." << endl;
    }

    return 0;
}
