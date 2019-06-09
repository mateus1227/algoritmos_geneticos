//maximizar o número de variáveis com o valor 1
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

// parametros do algoritmo genetico
int tam_genes = 100; // quantidade de genes
int tam_populacao = 50; // quantidade de individuos da populacao
int tam_torneio = 20; // tamanho do torneio
int geracoes = 100; // quantidade de geracoes
double prob_mut = 0.3; // probabilidade de mutacao
double prob_cruz = 0.5; // probabilidade de cruzamento

// populacao
vector<vector<int> > populacao;

void inicializaPopulacao()
{
	for(int i = 0; i < tam_populacao; i++)
	{
		vector<int> individuo;

		for(int j = 0; j < tam_genes; j++)
		{
			int num = rand() % 2; // escolhe um numero no intervalo [0,1]
			individuo.push_back(num); // insere no vetor do individuo
		}

		populacao.push_back(individuo); // insere no vetor da populacao
	}
}

void mostrarPopulacao()
{
	for(int i = 0; i < tam_populacao; i++)
	{
		for(int j = 0; j < tam_genes; j++)
			cout << populacao[i][j] << " ";
		cout << endl;
	}
}

// retorna o score do individuo
int obterPontuacao(vector<int> individuo)
{
	// o score sao a soma dos valores dos genes
	int soma = 0;

	for(int i = 0; i < tam_genes; i++)
		soma += individuo[i];
	return soma;
}

// realiza a mutacao
void mutacao(vector<int>& individuo)
{
	// escolhe um gene aleatoriamente no intervalo [0, tam_genes - 1]
	int gene = rand() % tam_genes;

	// modifica o valor do gene escolhido
	if(individuo[gene] == 0)
		individuo[gene] = 1;
	else
		individuo[gene] = 0;
}

// realiza o cruzamento
void cruzamento(int indice_pai1, int indice_pai2, vector<int>& filho)
{
	// escolhe um ponto aleatoriamente no intervalo [0, tam_genes - 1]
	int ponto = rand() % tam_genes;

	for(int i = 0; i <= ponto; i++)
		filho.push_back(populacao[indice_pai1][i]);
	for(int i = ponto + 1; i < tam_genes; i++)
		filho.push_back(populacao[indice_pai2][i]);
}

// retorna o indice do melhor individuo da populacao
int obterMelhor()
{
	int indice_melhor = 0;
	int score_melhor = obterPontuacao(populacao[0]);

	for(int i = 1; i < tam_populacao; i++)
	{
		int score = obterPontuacao(populacao[i]);
		if(score > score_melhor)
		{
			indice_melhor = i;
			score_melhor = score;
		}
	}

	return indice_melhor;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	inicializaPopulacao();
	//mostrarPopulacao();

	for(int i = 0; i < geracoes; i++)
	{
		for(int j = 0; j < tam_torneio; j++)
		{

			// calcula a probabilidade de cruzamento
			double prob = ((double) rand() / ((double)RAND_MAX + 1));

			if(prob < prob_cruz)
			{
				// escolhe dois pais
				int indice_pai1 = rand() % tam_populacao;
				int indice_pai2;

				// garante que os indices dos pais nao sao iguais
				do
				{
					indice_pai2 = rand() % tam_populacao;
				}
				while(indice_pai1 == indice_pai2);

				vector<int> filho;

				// aplica o cruzamento de 1 ponto
				cruzamento(indice_pai1, indice_pai2, filho);

				// calcula a probabilidade de mutacao
				prob = ((double) rand() / ((double)RAND_MAX + 1));

				if(prob < prob_mut)
					mutacao(filho);

				int score_pai = obterPontuacao(populacao[indice_pai1]);
				int score_filho = obterPontuacao(filho);

				/*
					se a pontuacao (score) do filho for melhor do
					que o pai1, entao substitui o pai 1 pelo filho
				*/
				if(score_filho > score_pai)
				{
					// faz a copia dos genes do filho para o pai
					for(int k = 0; k < tam_genes; k++)
						populacao[indice_pai1][k] = filho[k];
				}
			}
		}
		cout << "\t\t\t\t\t\tPROBLEMA DO ONE MAX: DETALHES\t\t\t\t\t\n\n";
		cout << "Geracao: " << i + 1 << endl;
		cout << "Melhor: ";
		
		int indice_melhor = obterMelhor();
		int score_melhor = obterPontuacao(populacao[indice_melhor]);
		
		for(int j = 0; j < tam_genes; j++)
			cout << populacao[indice_melhor][j] << " ";
		
		cout << "\nPontuacao: " << score_melhor << "\n\n";
		
		// verifica se encontrou a solucao otima global e se encontrou o algoritmo para.
		if(score_melhor == tam_genes)
			break;
	}

	return 0;
}
