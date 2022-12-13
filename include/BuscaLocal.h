#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"


class BuscaLocal
{
    protected:
        Grafo G;
        Grafo T;
        Grafo NewT;

        vector<int> BT;
        void AtualizarCConexas(int v, int u);

    private:

    public:
        BuscaLocal(const Grafo& pG, const Grafo& pT, vector<int> BV);
        virtual ~BuscaLocal();

        void ConectaFolhas();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;

};

#endif // BUSCALOCAL_H
