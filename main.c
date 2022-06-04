#include <stdio.h>
#include <stdlib.h>

#include "ArvoreBinaria.h"
#include "Int.h"

int main()
{
    Arvore arv, *ptrArv;
    int *ptrDado, pai;

    ptrArv = CriaArvore2(ComparaInt, CopiaInt, EscreveInt);
    ptrArv = (Arvore *) malloc(sizeof(Arvore));
    CriaArvore(ptrArv, ComparaInt, CopiaInt, EscreveInt);


    CriaArvore(&arv, ComparaInt, CopiaInt, EscreveInt);

    ptrDado  = (int *) malloc(sizeof(int));
    pai      = 0;
    *ptrDado = 1;
    InserePai(&arv, &pai, 'e', ptrDado);

    ptrDado  = (int *) malloc(sizeof(int));
    pai      = 1;
    *ptrDado = 2;
    InserePai(&arv, &pai, 'e', ptrDado);

    ptrDado  = (int *) malloc(sizeof(int));
    pai      = 1;
    *ptrDado = 3;
    InserePai(&arv, &pai, 'd', ptrDado);

    ptrDado  = (int *) malloc(sizeof(int));
    pai      = 2;
    *ptrDado = 4;
    InserePai(&arv, &pai, 'e', ptrDado);

    ptrDado  = (int *) malloc(sizeof(int));
    pai      = 2;
    *ptrDado = 5;
    InserePai(&arv, &pai, 'd', ptrDado);

    ptrDado  = (int *) malloc(sizeof(int));
    pai      = 3;
    *ptrDado = 6;
    InserePai(&arv, &pai, 'e', ptrDado);

    ptrDado  = (int *) malloc(sizeof(int));
    pai      = 3;
    *ptrDado = 7;
    InserePai(&arv, &pai, 'd', ptrDado);

    printf("\n\nPrefixado: ");
    CaminhaPreFixado( & arv );

    printf("\n\nInfixado: ");
    CaminhaInFixado ( & arv );

    printf("\n\nPosfixado: ");
    CaminhaPosFixado( & arv );

    return 0;
}
