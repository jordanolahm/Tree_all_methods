#ifndef ARVOREBINARIA_H_INCLUDED
#define ARVOREBINARIA_H_INCLUDED

typedef struct No
{
    void *ptrDado;
    struct No   *ptrEsq;
    struct No   *ptrDir;
//    No   *vetorSubArvores[50]; arvore/no com 50 subArvores
} No;

typedef struct
{
    No *ptrRaiz;
    int  (*ptrFncCompara)(void *ptrElemento, void *ptrChave);
    int  (*ptrFncCopia)  (void *ptrDestino , void *ptrOrigem);
    void (*ptrFncEscreve)(void *ptrElemento);
} Arvore;

void CriaArvore(Arvore *ptrArvore,
                int  (*ptrFncCompara)(void *ptrElemento, void *ptrChave),
                int  (*ptrFncCopia)  (void *ptrDestino , void *ptrOrigem),
                void (*ptrFncEscreve)(void *ptrElemento));
Arvore* CriaArvore2(int  (*ptrFncCompara)(void *ptrElemento, void *ptrChave),
                    int  (*ptrFncCopia)  (void *ptrDestino , void *ptrOrigem),
                    void (*ptrFncEscreve)(void *ptrElemento));

int InserePai(Arvore *ptrArvore, void *ptrChavePai, char lado, void *ptrElemento);
int Consulta(Arvore *ptrArvore, void *ptrChave, void *ptrElementoSaida);
int Altera(Arvore *ptrArvore, void *ptrChave, void *ptrNovo);
void* Exclui(Arvore *ptrArvore, void *ptrChave);
void Destroi(Arvore *ptrArvore);

void CaminhaPreFixado(Arvore *ptrArvore);
void CaminhaInFixado (Arvore *ptrArvore);
void CaminhaPosFixado(Arvore *ptrArvore);

#endif // ARVOREBINARIA_H_INCLUDED
