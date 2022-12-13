#include "BuscaLocal.h"
#include <algorithm>
#include <iostream>

BuscaLocal::BuscaLocal(const Grafo& pG, const Grafo& pT, vector<int> BV):
    G(pG), T(pT), NewT(pT), BT(BV)
{
    //constructor
    G.nome = "G";
    T.nome = "T";
    NewT.nome = "NewT";
}

BuscaLocal::~BuscaLocal()
{
    //destructor
}

void BuscaLocal::ConectaFolhas()
{
    //vector<pair<int,int>> Arvore = T.E;
    //vector<pair<int,int>> NovaArvore = NewT.E;
    vector<int> N(T.n);
    vector<int> Pai(T.n);
    vector<vector<int>> Cr;
    queue<int> Fila;
    int r = 0;
    int d = 0;
    for(int v : T.V)
    {
        if(T.Grau(v) > d)
        {
            d = T.Grau(v);
            r = v;
        }
        N[v] = -1;
    }
    Fila.push(r);
    N[r] = 0;
    Cr[r].push_back(r);

    while(Fila.empty() == false)
    {
        int v = Fila.front();
        Fila.pop();
        for(int u : T.Adjacentes(v))
        {
            if(u != Pai[v])
            {
                N[v] = N[v] + 1;
                Pai[u] = v;
                for(int i : Cr[v])
                {
                    Cr[u].push_back(i);
                }
                Cr[u].push_back(u);
                Fila.push(u);
            }
        }
    }
    vector<int> BV;// = BT - G.ArticulacoesW2;
}
