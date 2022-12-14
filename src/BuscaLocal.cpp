#include "BuscaLocal.h"
#include <algorithm>
#include <iostream>

BuscaLocal::BuscaLocal(const Grafo& pG, const Grafo& pT, vector<int> B):
    G(pG), T(pT), BT(B), InFolhas(G.n, 0), InBV(G.n, 0), NewT(pT)
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
    vector<int> N(T.n);
    vector<int> Pai(T.n);
    vector<vector<int>> Cr(T.n);
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
    bool obrigatorio;
    for(int i : BT)
    {
        obrigatorio = false;
        for(int j : G.ArticulacoesW2)
        {
            if(i == j)
            {
                obrigatorio = true;
            }
        }
        if(obrigatorio == false)
        {
            BV.push_back(i);
            InBV[i] = 1;
        }
    }

    set<int> Folhas;
    for(int v : T.V)
    {
        if(T.Grau(v) == 1 and G.Grau(v) > 1)
        {
            Folhas.insert(v);
            InFolhas[v] = 1;
        }
    }

    while(BV.empty() == false and Folhas.empty() == false)
    {
        int v;
        for(int i : Folhas)
        {
            v = i;
            break;
        }
        Folhas.erase(v);
        InFolhas[v] = 0;
        for(int u : G.Adjacentes(v))
        {
            if(T.Grau(u) == 1)
            {
                if(InFolhas[u] == 1)
                {
                    Folhas.erase(u);
                    InFolhas[u] = 0;
                }
                int w;
                int maiorN = 0;
                vector<int> Intersecao;
                for(int i : Cr[v])
                {
                    for(int j : Cr[u])
                    {
                        if(i == j)
                        {
                            Intersecao.push_back(i);
                        }
                    }
                }
                for(int i : Intersecao)
                {
                    if(N[i] > maiorN)
                    {
                        w = i;
                    }
                }
                vector<int> Cwv;
                vector<int> Cwu;
                vector<int> C;
                for(int i : Cr[v])
                {
                    if(i != w)
                    {
                        Cwv.push_back(i);
                        C.push_back(i);
                    }
                    else
                    {
                        Cwv.push_back(i);
                        C.push_back(i);
                        break;
                    }
                }
                for(int i : Cr[u])
                {
                    if(i != w)
                    {
                        Cwu.push_back(i);
                    }
                    else
                    {
                        Cwu.push_back(i);
                        break;
                    }
                }
                for(int i = Cwu.size() - 2; i > -1; i--)
                {
                    C.push_back(Cwu[i]);
                }
                int x;
                int menorC = G.n;
                int posicao = -1;
                int a;
                int b;
                for(int i : C)
                {
                    posicao += 1;
                    if(T.Grau(i) < menorC)
                    {
                        menorC = T.Grau(i);
                        x = i
                        if(i != x and i != u)
                        {
                            a = C[posicao - 1];
                            b = C[posicao + 1]
                        }
                    }
                    if(T.Grau(i) == menorC)
                    {
                        if(N[i] > N[x])
                        {
                            menorC = T.Grau(i);
                            x = i
                            if(i != x and i != u)
                            {
                                a = C[posicao - 1];
                                b = C[posicao + 1]
                            }
                        }
                    }
                }

            }
        }
    }

}
