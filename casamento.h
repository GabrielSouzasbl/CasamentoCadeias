#ifndef CASAMENTO_H_
#define CASAMENTO_H_

#include "analise.h"


#define MAXTAMTEXTO	 2000000	/* tamanho máx de caract. que um texto pode ter */
#define MAXTAMPADRAO 30			/* tamanho máx de caract. que um padrão pode ter */
#define MAXCHAR		 256		/* tamanho do alfabeto analisado */


	typedef char TipoTexto[MAXTAMTEXTO]; 	/* Tipo que armazena todo o texto */

	typedef char TipoPadrao[MAXTAMPADRAO];	/* Tipo que armazena todo o padrão */

/* algoritmo de Força Bruta recebe texto, tamanho do texto, padrão, tamanho do padrão */
void ForcaBruta(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica);

/* algoritmo Boyer-Moore recebe texto, tamanho do texto, padrão, tamanho do padrão */
void BM(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica);

/* algoritmo Boyer-Moore-Horspool recebe texto, tamanho do texto, padrão, tamanho do padrão */
void BMH(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica);

/* algoritmo Boyer-Moore-Horspool-Sunday recebe texto, tamanho do texto, padrão, tamanho do padrão */
void BMHS(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica);

/* algoritmo shift-and-exato recebe texto, tamanho do texto, padrão, tamanho do padrão */
void ShiftAndExato(TipoTexto T, long tam_t, TipoPadrao P, long tam_p, Analise* estatistica);


#endif //CASAMENTO_H_