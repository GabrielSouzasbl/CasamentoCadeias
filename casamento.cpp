#include <iostream>
#include <cstring>

#include "casamento.h"	/* incluindo cabecalhos e constantes */

using namespace std;


/* implementação do algoritmo */
void ForcaBruta(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica)
{
	cout <<"\nALGORITMO DE FORCA BRUTA\n\n";

	//starta calculo do tempo de execução 
	start_time(estatistica);

		long i, j, k;

		//loop exaustivo até o tamanho final do texto menos o tamanho do padrão
		for(i = 1; i< (tam_t-tam_p +1); i++)
		{

			k = i;
			j = 1;
			
			//primeira comparação antes de entrar no laço
			c_hit(estatistica); 
			while(T[k-1] == P[j-1] && j <= tam_p)
			{
				j++;
				k++;
				
				//proximas comparações do laço
				c_hit(estatistica);

			}

			// Se j > tamanho do padrão quer dizer que houve um casamento 
			if(j > tam_p)
				cout <<"Casamento na posicao: " <<i <<endl; //i = ao inicio do casamento

			d_hit(estatistica);
		}

	//para e calcula tempo final de execução
	stop_time(estatistica);
}

/* implementação do algoritmo */
void BM(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica)
{
	cout <<"\nALGORITMO DE BOYLE-MOORE\n\n";

	//starta calculo do tempo de execução 
	start_time(estatistica);

		long i, j, k, cont = 0;

		i = tam_p;

		/* pesquisa do padrão no texto */
		while(i < tam_t)
		{
			k = i;
			j = tam_p;

			// primeira comparação do laço
			c_hit(estatistica);
			while((T[k-1] == P[j-1]) && (j > 0))
			{
				k--;
				j--;
				// proximas comparações do laço
				c_hit(estatistica);
			}

			// se j == 0 indica que houve casamento
			if(j == 0)
			{
				cout <<"Casamento na posicao: " <<(k+1) <<endl;
				i++;
			}

			i++;
			j--;

			/* houve uma colisão inicio da heuristica ocorrencia */

			//procurando no padrão um caract. que case com o do texto.
			c_hit(estatistica);
			while(T[k-1] != P[j-1] && j > 0)
			{
				j--;
				i++;
				c_hit(estatistica);
			}
			d_hit(estatistica);
		}

	//para e calcula tempo final de execução
	stop_time(estatistica);
}

/* implementação do algoritmo */
void BMH(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica)
{
	cout <<"\nALGORITMO DE BOYLE-MOORE-HORSPOOL\n\n";

	//starta calculo do tempo de execução
	start_time(estatistica);

		long i, j, k;
		long d[MAXCHAR + 1];

		/* pré processamento para se obter a tabela de deslocamentos */
		for(j = 0; j < MAXCHAR; j++)
			d[j] = tam_p; //todos exceto o último recebem o tamanho do padrao incialmente 

		for(j = 1; j < tam_p; j++)
			d[P[j-1]] = tam_p-j; //calculo em cima dos caract. do padrão

		i = tam_p;

		/* pesquisa do padrão no texto */
		while(i <= tam_t)
		{
			k = i;
			j = tam_p;

			// primeira comparação do laço
			c_hit(estatistica);
			while((T[k-1] == P[j-1]) && (j > 0))
			{
				k--;
				j--;
				// proximas comparações do laço
				c_hit(estatistica);
			}

			// se j = 0 significa que houve casamento.
			if(j == 0)
				cout <<"Casamento na posicao: " <<(k+1) <<endl;



			d_hit(estatistica);
			i += d[T[i-1]]; //deslocamento da janela de acordo com tabela.
		}

	//para e calcula tempo final de execução
	stop_time(estatistica);
}

/* implementação do algoritmo */
void BMHS(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica)
{
	cout <<"\nALGORITMO DE BOYLE-MOORE-HORSPOOL-SUNDAY\n\n";

	//starta calculo do tempo de execução
	start_time(estatistica);

		long i, j, k;
		long d[MAXCHAR + 1];

		/* pré processamento para se obter a tabela de deslocamentos */
		for(j = 0; j <= MAXCHAR; j++)
			d[j] = tam_p;  //todos recebem o tamanho do padrao incialmente 

		for(j = 1; j <= tam_p; j++)
			d[P[j-1]] = tam_p-j+1; //calculo em cima dos caract. do padrão +1

		i = tam_p;

		/* pesquisa do padrão no texto */
		while(i <=tam_t)
		{
			k = i;
			j = tam_p;

			// primeira comparação do laço
			c_hit(estatistica);
			while((T[k-1] == P[j-1]) && (j > 0))
			{
				k--;
				j--;

				// proximas comparações do laço
				c_hit(estatistica);
			}

			// se j = 0 significa que houve casamento
			if(j == 0)
				cout <<"Casamento na posicao: " <<(k+1) <<endl;

			d_hit(estatistica);
			i += d[T[i]]; //deslocamento da janela de acordo com tabela.
		}

	//para e calcula tempo final de execução
	stop_time(estatistica);
}

/* implementação do algoritmo */
void ShiftAndExato(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica)
{
	cout <<"\nALGORITMO SHIFT-AND EXATO\n\n";

	//starta calculo do tempo de execução
	start_time(estatistica);

		long masc[MAXCHAR], i, j, Ri, R;

		// inicializando todas as posições da mascara com 0s
		for(i = 0; i < MAXCHAR; i++)
			masc[i] = 0;

		// alterando para os caracteres do padrão o valor da mascara 
		for(i = 1; i <= tam_p; i++)
		{
			// atualiza valor da mascara.
			masc[P[i-1]] |= 1 << (tam_p-i);
		}

		R = 0; 
		Ri = 1 << (tam_p-1);

		// deslocamento 1 a 1 que transforma a mascara e verifica se a prox posição do automato esta ativa
		for(i = 0; i < tam_t; i++)
		{
			// calculo de R que procura casamento entre caracteres
			R = ((((unsigned long)R) >> 1) | Ri) & masc[T[i]];
			d_hit(estatistica);

			// se a ultima posição do automato estiver ativa houve casamento exato
			if((R & 1) != 0)
			{
				cout <<"Casamento na posicao: " <<(i-tam_p+2) <<endl;
			}
		}

	//para e calcula tempo final de execução
	stop_time(estatistica);
}