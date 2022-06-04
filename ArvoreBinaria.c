#include <stdlib.h>

#include "ArvoreBinaria.h"

void CriaArvore(Arvore *ptrArvore,
                int  (*ptrFncCompara)(void *ptrElemento, void *ptrChave),
                int  (*ptrFncCopia)  (void *ptrDestino , void *ptrOrigem),
                void (*ptrFncEscreve)(void *ptrElemento))
{
    ptrArvore->ptrRaiz       = NULL;
    ptrArvore->ptrFncCompara = ptrFncCompara;
    ptrArvore->ptrFncCopia   = ptrFncCopia;
    ptrArvore->ptrFncEscreve = ptrFncEscreve;
}
Arvore* CriaArvore2(int  (*ptrFncCompara)(void *ptrElemento, void *ptrChave),
                    int  (*ptrFncCopia)  (void *ptrDestino , void *ptrOrigem),
                    void (*ptrFncEscreve)(void *ptrElemento))
{
    Arvore *ptrArvore = (Arvore *) malloc(sizeof(Arvore));

    if ( !ptrArvore )
        return NULL;

    ptrArvore->ptrRaiz       = NULL;
    ptrArvore->ptrFncCompara = ptrFncCompara;
    ptrArvore->ptrFncCopia   = ptrFncCopia;
    ptrArvore->ptrFncEscreve = ptrFncEscreve;

    return ptrArvore;
}
No* CriaNo(void *ptrDado)
{
    No *ptrNo = (No *) malloc(sizeof(No));

    if ( ptrNo )
    {
        ptrNo->ptrDado = ptrDado;
        ptrNo->ptrEsq  = NULL;
        ptrNo->ptrDir  = NULL;
    }

    return ptrNo;
}
No* ConsultaLocal(No *ptrRaiz, void *ptrChave, int (*ptrFncCompara)(void *ptrElemento, void *ptrChave))
{
    if ( !ptrRaiz )
        return NULL;

    if (ptrFncCompara(ptrRaiz->ptrDado, ptrChave) == 0)
        return ptrRaiz;

    No *ptrNo = ConsultaLocal(ptrRaiz->ptrEsq, ptrChave, ptrFncCompara);
    if ( ptrNo )
        return ptrNo;

    return ConsultaLocal(ptrRaiz->ptrDir, ptrChave, ptrFncCompara);
}
int Consulta(Arvore *ptrArvore, void *ptrChave, void *ptrElementoSaida)
{
    No *ptrNo = ConsultaLocal(ptrArvore->ptrRaiz, ptrChave, ptrArvore->ptrFncCompara);

    if ( !ptrNo )
        return 0;

    ptrArvore->ptrFncCopia(ptrElementoSaida, ptrNo->ptrDado);
    return 1;
}
int Altera(Arvore *ptrArvore, void *ptrChave, void *ptrNovo)
{
    No *ptrNo = ConsultaLocal(ptrArvore->ptrRaiz, ptrChave, ptrArvore->ptrFncCompara);

    if ( !ptrNo )
        return 0;

    ptrArvore->ptrFncCopia(ptrNo->ptrDado, ptrNovo);
    return 1;
}
int InserePai(Arvore *ptrArvore, void *ptrChavePai, char lado, void *ptrElemento)
{
    // localiza pai do novo no/elemento
    No *ptrPai = ConsultaLocal(ptrArvore->ptrRaiz, ptrChavePai, ptrArvore->ptrFncCompara);

    No *ptrNo = CriaNo( ptrElemento );
    if ( !ptrNo )
        return -1;

    if ( !ptrArvore->ptrRaiz )  // se a arvore esta vazia, insere na raiz
    {
        ptrArvore->ptrRaiz = ptrNo;
        return 1;
    }

    if ( !ptrPai )  // elemento pai nao encontrado
    {
        free( ptrNo );
        return -2;
    }

    if (lado == 'e')
    {
        ptrNo->ptrEsq  = ptrPai->ptrEsq;
        ptrPai->ptrEsq = ptrNo;
    }
    else
    {
        ptrNo->ptrDir  = ptrPai->ptrDir;
        ptrPai->ptrDir = ptrNo;
    }

    return 1;
}

void CaminhaPreFixadoLocal(No *ptrRaiz, void (*ptrFncEscreve)(void *ptrElemento))
{
    if ( !ptrRaiz )
        return;

    ptrFncEscreve( ptrRaiz->ptrDado );  // visita nó
    CaminhaPreFixadoLocal(ptrRaiz->ptrEsq, ptrFncEscreve);
    CaminhaPreFixadoLocal(ptrRaiz->ptrDir, ptrFncEscreve);
}
void CaminhaPreFixado(Arvore *ptrArvore)
{
    CaminhaPreFixadoLocal(ptrArvore->ptrRaiz, ptrArvore->ptrFncEscreve);
}

void CaminhaInFixadoLocal(No *ptrRaiz, void (*ptrFncEscreve)(void *ptrElemento))
{
    if ( !ptrRaiz )
        return;

    CaminhaInFixadoLocal(ptrRaiz->ptrEsq, ptrFncEscreve);
    ptrFncEscreve( ptrRaiz->ptrDado );  // visita nó
    CaminhaInFixadoLocal(ptrRaiz->ptrDir, ptrFncEscreve);
}
void CaminhaInFixado(Arvore *ptrArvore)
{
    CaminhaInFixadoLocal(ptrArvore->ptrRaiz, ptrArvore->ptrFncEscreve);
}

void CaminhaPosFixadoLocal(No *ptrRaiz, void (*ptrFncEscreve)(void *ptrElemento))
{
    if ( !ptrRaiz )
        return;

    CaminhaPosFixadoLocal(ptrRaiz->ptrEsq, ptrFncEscreve);
    CaminhaPosFixadoLocal(ptrRaiz->ptrDir, ptrFncEscreve);
    ptrFncEscreve( ptrRaiz->ptrDado );  // visita nó
}
void CaminhaPosFixado(Arvore *ptrArvore)
{
    CaminhaPosFixadoLocal(ptrArvore->ptrRaiz, ptrArvore->ptrFncEscreve);
}
void* BuscaSucessor(No *ptrRaiz, No **ptrSucessor)
{
    if ((*ptrSucessor)->ptrEsq != NULL) // caminha recursivamente ate a extrema esquerda
        return BuscaSucessor(ptrRaiz, &(*ptrSucessor)->ptrEsq);

    No *ptrNo = *ptrSucessor;   // salva referencia para no sucessor
    *ptrSucessor = (*ptrSucessor)->ptrDir;

    void *ptrElemento = ptrRaiz->ptrDado;   // salva dado do ptrRaiz a ser excluido
    ptrRaiz->ptrDado  = ptrNo->ptrDado;     // dados do ptrSuscessor tomam lugar no ptrRaiz

    free( ptrNo );
    return ptrElemento;
}
void* ExcluiLocal(No **ptrRaiz, void *ptrChave, int (*ptrFncCompara)(void *ptrElemento, void *ptrChave))
{
    void *ptrElemento = NULL;

    if (*ptrRaiz == NULL)
        return NULL;

    if (ptrFncCompara((*ptrRaiz)->ptrDado, ptrChave) == 0)
    {
        ptrElemento = (*ptrRaiz)->ptrDado;

        // verifica se ha filhos
        if ((*ptrRaiz)->ptrEsq == NULL) // se nao tem subArvore esquerda
            *ptrRaiz = (*ptrRaiz)->ptrDir;
        else
        if ((*ptrRaiz)->ptrDir == NULL) // se nao tem subArvore direira
            *ptrRaiz = (*ptrRaiz)->ptrEsq;
        else // ha filhos (aa esquerda e aa direta)
            return BuscaSucessor(*ptrRaiz, &(*ptrRaiz)->ptrDir);

        // libera memoria da estrutura No
        free( *ptrRaiz );
        *ptrRaiz = NULL;

        // retorna dado excluido
        return ptrElemento;
    }

    ptrElemento = ExcluiLocal(&(*ptrRaiz)->ptrEsq, ptrChave, ptrFncCompara);
    // retorna/repassa dado excluido
    if ( ptrElemento )
        return ptrElemento;
    return ExcluiLocal(&(*ptrRaiz)->ptrDir, ptrChave, ptrFncCompara);
}
void* Exclui(Arvore *ptrArvore, void *ptrChave)
{
    return ExcluiLocal(&ptrArvore->ptrRaiz, ptrChave, ptrArvore->ptrFncCompara);
}
void DestroiLocal(No **ptrRaiz)
{
    if (*ptrRaiz == NULL)
        return;

    DestroiLocal( &(*ptrRaiz)->ptrEsq );
    DestroiLocal( &(*ptrRaiz)->ptrDir );

    free( (*ptrRaiz)->ptrDado );
    free( *ptrRaiz );
    *ptrRaiz = NULL;
}
void Destroi(Arvore *ptrArvore)
{
    DestroiLocal( &ptrArvore->ptrRaiz );
}
void DestroiLocal2(No *ptrRaiz)
{
    if (ptrRaiz == NULL)
        return;

    DestroiLocal2( ptrRaiz->ptrEsq );
    DestroiLocal2( ptrRaiz->ptrDir );

    free( ptrRaiz->ptrDado );
    free( ptrRaiz );
}
void Destroi2(Arvore *ptrArvore)
{
    DestroiLocal2( ptrArvore->ptrRaiz );
    ptrArvore->ptrRaiz = NULL;
}

