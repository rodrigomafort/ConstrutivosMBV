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

Grafo BuscaLocal::ObterArvore() const
{
    return NewT;
}

set<int> BuscaLocal::ObterBranches() const
{
    return BV;
}

vector<int> BuscaLocal::ObterGrauBV() const
{
    vector<int> GrauBV;
    for (int v : BV)
    {
        GrauBV.push_back(NewT.Grau(v));
    }
    return GrauBV;
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
            vector<int> auxiliar;
            if(u != Pai[v])
            {
                N[u] = N[v] + 1;
                Pai[u] = v;
                for(int i : Cr[v])
                {
                    //Cr[u].push_back(i);
                    auxiliar.push_back(i);
                }
                Cr[u] = auxiliar;
                Cr[u].push_back(u);
                Fila.push(u);
            }
        }
    }

    //int BV = BT - G.ArticulacoesW2;
    bool obrigatorio;
    G.DetectarArticulacoesEPontes();
    for(int i : BT)
    {
        obrigatorio = false;
        for(int j : G.ArticulacoesW2)
        {
            if(i == j)
            {
                obrigatorio = true;
                break;
            }
        }
        if(obrigatorio == false)
        {
            BV.insert(i);
            InBV[i] = 1;
        }
    }

    set<int> Folhas;
    for(int v : T.V)
    {
        if(T.Grau(v) == 1 && G.Grau(v) > 1)
        {
            Folhas.insert(v);
            InFolhas[v] = 1;
        }
    }

    while(BV.empty() == false && Folhas.empty() == false)
    {
        int v = *Folhas.begin();
        Folhas.erase(Folhas.begin());
        InFolhas[v] = 0;
        int w;
        for(int u : G.Adjacentes(v))
        {
            if(NewT.Grau(u) == 1)
            {
                if(InFolhas[u] == 1)
                {
                    Folhas.erase(u);
                    InFolhas[u] = 0;
                }

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
                        maiorN = N[i];
                    }
                }
                vector<int> Cwv;
                vector<int> Cwu;
                vector<int> C;
                for(int i = Cr[v].size() - 1; i > -1; i--)
                {
                    if(Cr[v][i] != w)
                    {
                        Cwv.push_back(Cr[v][i]);
                        C.push_back(Cr[v][i]);
                    }
                    else
                    {
                        Cwv.push_back(Cr[v][i]);
                        C.push_back(Cr[v][i]);
                        break;
                    }
                }
                for(int i = Cr[u].size() - 1; i > -1; i--)
                {
                    if(Cr[u][i] != w)
                    {
                        Cwu.push_back(Cr[u][i]);
                    }
                    else
                    {
                        Cwu.push_back(Cr[u][i]);
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
                    if(NewT.Grau(i) < menorC && InBV[i] == 1)
                    {
                        menorC = NewT.Grau(i);
                        x = i;
                        if(i != v and i != u)
                        {
                            a = C[posicao - 1];
                            b = C[posicao + 1];
                        }
                    }
                    if(NewT.Grau(i) == menorC && InBV[i] == 1)
                    {
                        if(N[i] > N[x])
                        {
                            menorC = NewT.Grau(i);
                            x = i;
                            if(i != v and i != u)
                            {
                                a = C[posicao - 1];
                                b = C[posicao + 1];
                            }
                        }
                    }
                }
                if(InBV[a] == 1 && InBV[b] == 1)
                {
                    if(NewT.Grau(a) <= NewT.Grau(b))
                    {
                        NewT.RemoverAresta(a, x);
                    }
                    else
                    {
                        NewT.RemoverAresta(b, x);
                    }
                }
                else
                {
                    if(InBV[a] == 1)
                    {
                        NewT.RemoverAresta(a, x);
                    }
                    else
                    {
                        if(InBV[b] == 1)
                        {
                            NewT.RemoverAresta(b, x);
                        }
                        else
                        {
                            if(G.Grau(a) >= G.Grau(b))
                            {
                                NewT.RemoverAresta(a, x);
                                Folhas.insert(a);
                                InFolhas[a] = 1;
                            }
                            else
                            {
                                NewT.RemoverAresta(b, x);
                                Folhas.insert(b);
                                InFolhas[b] = 1;
                            }
                        }
                    }
                }
                if(NewT.Grau(x) < 3 && InBV[x] == 1)
                {
                    BV.erase(x);
                    InBV[x] = 0;
                }
                if(NewT.Grau(a) < 3 && InBV[a] == 1)
                {
                    BV.erase(a);
                    InBV[a] = 0;
                }
                if(NewT.Grau(b) < 3 && InBV[b] == 1)
                {
                    BV.erase(b);
                    InBV[b] = 0;
                }
                NewT.AdicionarAresta(v, u);
                break;
            }
        }
        Fila.push(w);
        while(Fila.empty() == false)
        {
            int v = Fila.front();
            Fila.pop();
            for(int u : NewT.Adjacentes(v))
            {
                vector<int> auxiliar;
                if(u != Pai[v])
                {
                    N[u] = N[v] + 1;
                    Pai[u] = v;
                    for(int i : Cr[v])
                    {
                        auxiliar.push_back(i);
                    }
                    Cr[u] = auxiliar;
                    Cr[u].push_back(u);
                    Fila.push(u);
                }
            }
        }
    }

    for(int i : G.ArticulacoesW2)
    {
        BV.insert(i);
        InBV[i] = 1;
    }
}
