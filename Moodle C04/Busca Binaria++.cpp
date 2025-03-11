#include<iostream>
using namespace std;

int binaria (int vetor[], int tamanho, int x)
{
	bool achou;
	int baixo, meio, alto;
	
	baixo = 0;
	alto = tamanho -1;
	achou = false;
	
	while((baixo <= alto) && (achou == false))
	{
	
		meio = (baixo + alto) / 2;
		if(x <vetor[meio])
		{
			alto = meio -1;
		}
		else 
		{
			if(x > vetor[meio])
			{
				baixo = meio + 1;
			}
			else
			{
				achou = true;
			}
		}
	}
	
	if(achou == true)
	{
		return meio;
	}
	else
	{
		return -1;
	}
}

int main()
{
	int vetor[10], n, pos;

	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		cin >> vetor[i];
	}
	
	cin >> pos;

	cout << binaria(vetor, n, pos) << endl;
	return 0;
}