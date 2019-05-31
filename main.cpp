#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include "casamento.h"	/* trata os algoritmos de casamento de cadeia */
#include "analise.h"	/* trata todos os métodos refentes à analise */

using namespace std;

/* tratamento de possiveis erros para entrada de argumentos via terminal */
int teste_arg(int argc, char* argv[]);

/* carrega o texto na variavel */
long carrega_texto(char* argv[], TipoTexto T);

/* carrega o padrao na variavel */
long carrega_padrao(char* padrao);

/* função principal */
int main(int argc, char* argv[])
{
	/* start em semente aleatória */
	srand(time(NULL));

	/*validando argumentos de entrada */
	if(!teste_arg(argc, argv))
		return 0;

	TipoTexto texto;
	TipoPadrao padrao;

 	/* estrutura que captura dados para análise posterior (criação por default zera todos os indices) */ 
	Analise* estatistica;
	estatistica = cria_analise();

	/* variaveis recebem o tamanho exato de texto e padrão respectivamente */
	long tamanho_do_texto = carrega_texto(argv, texto);
	long tamanho_do_padrao = carrega_padrao(argv[3]);

	/* erro na abertura do arquivo texto */
	if(tamanho_do_texto == 0)
	{
		cout <<"\n\nFALHA NA ABERTURA DO ARQUIVO\n";
		return 0;
	}

	/* menu de algoritmos */
	switch(atoi(argv[1]))
	{
		// força bruta
		case 1: { ForcaBruta(texto, tamanho_do_texto, argv[3], tamanho_do_padrao, estatistica); }	 break;

		// Boyer-Moore
		case 2: { BM(texto, tamanho_do_texto, argv[3], tamanho_do_padrao, estatistica); } 		 	 break;

		// Boyer-Moore-Horspool
		case 3: { BMH(texto, tamanho_do_texto, argv[3], tamanho_do_padrao, estatistica); } 		 	 break;

		// Boyer-Moore-Horspool-Sudnay
		case 4: { BMHS(texto, tamanho_do_texto, argv[3], tamanho_do_padrao, estatistica); } 		 break;

		// Shift-And-exato
		case 5: { ShiftAndExato(texto, tamanho_do_texto, argv[3], tamanho_do_padrao, estatistica); } break;
	}

	// argumento opcional que retorna estatisticas dos métodos 
	if((!strcmp(argv[4], "-p")) || (!strcmp(argv[4], "-P")))
		mostrar_est(estatistica);

	return 0;
}

/* menu teste de argumentos */
int teste_arg(int argc, char* argv[])
{	
	/* menu para leigos */
	if(argc == 1)
	{
		cout <<"\n\nBEM VINDO AO PROGRAMA - ANALISE ENTRE METODOS DE CASAMENTOD DE CADEIAS -\n"		
			 <<"\nLEIA E SIGA OS PASSOS ABAIXO PARA COMPREENSÃO DA EXECUÇÃO.";

		cout <<"\n\n\t******** MENU ********"
			 <<"\n\n-O EXECUTAVEL DEVE SER INICIALIZADO COM OS SEGUINTES PARAMENTROS: "
			 <<"\n\n./<EXECUTAVEL> <MÉTODO> <TEXTO> <PADRAO> [-P] "
			 <<"\n\nONDE: "
			 <<"\n\nMETODO: "
			 <<"\n[1] - ALGORITMO FORÇA BRUTA. "
			 <<"\n[2] - ALGORITMO BOYER-MOORE. "
			 <<"\n[3] - ALGORITMO BOYER-MOORE-HORSPOOL. "
			 <<"\n[4] - ALGORITMO BOYER-MOORE-HORSPOOL-SUNDAY. "
			 <<"\n[5] - ALGORITMO SHIFT-AND EXATO. "
			 <<"\n\nTEXTO: "
			 <<"\n-O NOME FISICO DO ARQUIVO TEXTO NO QUAL OCORRERÁ A EXECUCAO DO METODO. "
			 <<"\n\nPADRAO: "
		 	 <<"\nQUAL O PADRAO QUE SERA PESQUISADO NO TEXTO. "
			 <<"\n\n[-P]: "
			 <<"\n- É OPCIONAL, COM ELE SERA IMPRESSO NA TELA OS DADOS DA ANALISE FEITA. "
			 <<"\n- SEM ELE, APENAS AS OCORRENCIAS DO PADRAO SOLICITADO NO TEXTO SERAO IMPRESSAS NA TELA "
			 <<"\n\nEXEMPLO DE EXECUCAO: ./tp 3 biblia.txt amem -p\n\nBOA SORTE!" <<endl;

		return 0;
	}

	/* trata a opção opcional [-P]*/
	if(argv[4] == NULL)
		argv[4] = (char*)"flag";

	/* 5 sem o -p, 6 com o -p */
	if(argc != 4 && argc != 5)
	{
		cout <<"\nVOCE NAO DIGITOU O NUMERO CORRETO DE ARGUMENTOS NECESSARIOS PARA O CASAMENTO\n\n"
			 <<"TENTE NOVAMENTE\n" <<endl;
		return 0;
	}

	/* numero de registros fora dos limites*/
	int metodo = atoi(argv[1]);
	if(metodo > 5 || metodo <= 0)
	{
		cout <<"\nDESCULPE DISPONIBILIZAMOS DE 5 METODOS PARA CASAMENTO O NUMERO DIGITADO ESTA FORA DOS LIMITES\n\n"
			 <<"EXECUTE ./tp  PARA MAIS INFORMAÇÕES\n";
		return 0;
	}

	return 1;
}

// retorna tamanho do texto
long carrega_texto(char* argv[], TipoTexto T)
{
	long cont = 0;
	FILE* arqt;

	// abertura de arquivo com teste 
	if((arqt = fopen(argv[2], "r")) == NULL)
		return 0;

	// le o primeiro caractere do arquivo
	T[cont] = getc(arqt);

	// loop para leitura do arquivo até o fim contabilizando caract.
	while(T[cont] != EOF)
	{
		cont++;
		T[cont] = getc(arqt);
	}

	// fecha arquivo
	fclose(arqt);

	return cont; //retorna quantidade de caract. existentes no texto.
}

// retorna tamanho do padrão
long carrega_padrao(char* padrao)
{
	// atribui o argumento passado via terminal para a variavel
	char* ptr = padrao;

	// loop até encontrar um espaço
	while (*padrao != '\0')
		padrao++;

	// calculo retornando tamanho exato do padrao
	return (long)(padrao-ptr);
}