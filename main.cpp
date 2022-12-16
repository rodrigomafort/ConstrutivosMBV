#include <iostream>
#include <set>
#include <vector>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "AndersonV4.h"
#include "Rodrigo.h"
#include "Algoritmo3.h"
#include "BuscaLocal.h"

using namespace std;

int main(int argc, char *argv[]){
    if (argc < 2){
		cout << "Nome do arquivo não recebido" << endl;
		return 1;
	}

	Grafo G = Grafo::LerArquivo(argv[1]);
	//Grafo G2 = Grafo::LerArquivo(argv[1]);
	//Grafo G3 = Grafo::LerArquivo(argv[1]);
	/*
    double time_spent = 0.0;
    clock_t start1 = clock();

    AndersonV4 alg = AndersonV4(G);
    alg.Oliveira();

    clock_t end1 = clock();
    time_spent += (double)(end1 - start1) / CLOCKS_PER_SEC;

    double time_spent2 = 0.0;
    clock_t start2 = clock();

    Rodrigo alg2 = Rodrigo(G);
    alg2.Oliveira();

    clock_t end2 = clock();
    time_spent2 += (double)(end2 - start2) / CLOCKS_PER_SEC;

    double time_spent3 = 0.0;
    clock_t start3 = clock();

    Algoritmo3 alg3 = Algoritmo3(G);
    alg3.Oliveira();

    clock_t end3 = clock();
    time_spent3 += (double)(end3 - start3) / CLOCKS_PER_SEC;*/

    vector<int> BT100a;
    int BTaMin = 1001;
    int BTaMax = 0;
    vector<int> BT100b;
    int BTbMin = 1001;
    int BTbMax = 0;
    vector<int> BT100c;
    int BTcMin = 1001;
    int BTcMax = 0;

    Grafo T;
    vector<int> BT;
    Grafo T2;
    vector<int> BT2;
    Grafo T3;
    vector<int> BT3;
    for(int i=0; i<10; i++)
    {
        AndersonV4 alg = AndersonV4(G);
        alg.Oliveira();
        T = alg.ObterArvore();
        BT = alg.ObterBranches();
        //vector<int> GrauBT = alg.ObterGrauBT();
        BT100a.push_back(BT.size());
        if(BT.size() < BTaMin)
            BTaMin = BT.size();
        if(BT.size() > BTaMax)
            BTaMax = BT.size();

        Rodrigo alg2 = Rodrigo(G);
        alg2.Oliveira();
        T2 = alg2.ObterArvore();
        BT2 = alg2.ObterBranches();
        //vector<int> GrauBT2 = alg2.ObterGrauBT();
        BT100b.push_back(BT2.size());
        if(BT2.size() < BTbMin)
            BTbMin = BT2.size();
        if(BT2.size() > BTbMax)
            BTbMax = BT2.size();

        Algoritmo3 alg3 = Algoritmo3(G);
        alg3.Oliveira();
        T3 = alg3.ObterArvore();
        BT3 = alg3.ObterBranches();
        //vector<int> GrauBT3 = alg3.ObterGrauBT();
        BT100c.push_back(BT3.size());
        if(BT3.size() < BTcMin)
            BTcMin = BT3.size();
        if(BT3.size() > BTcMax)
            BTcMax = BT3.size();
    }
    cout << argv[1] << endl;
    int soma = 0;
    for(int i : BT100a)
       soma = soma + i;
    cout << "AndersonV4 - Min: " << BTaMin << " Max: " << BTaMax << " Media: " << soma/10 << " Atual: " << BT.size() << endl;

    soma = 0;
    for(int i : BT100b)
       soma = soma + i;
    cout << "Rodrigo - Min: " << BTbMin << " Max: " << BTbMax << " Media: " << soma/10 << " Atual: " << BT2.size() << endl;

    soma = 0;
    for(int i : BT100c)
       soma = soma + i;
    cout << "Algoritmo3 - Min: " << BTcMin << " Max: " << BTcMax << " Media: " << soma/10 << " Atual: " << BT3.size() << endl << endl;


    BuscaLocal bl = BuscaLocal(G, T, BT);
    bl.ConectaFolhas();
    set<int> BTL = bl.ObterBranches();
    cout << BTL.size() << "\t ";

    BuscaLocal bl2 = BuscaLocal(G, T2, BT2);
    bl2.ConectaFolhas();
    set<int> BTL2 = bl2.ObterBranches();
    cout << BTL2.size() << "\t ";

    BuscaLocal bl3 = BuscaLocal(G, T3, BT3);
    bl3.ConectaFolhas();
    set<int> BTL3 = bl3.ObterBranches();
    cout << BTL3.size() << endl;

    /*
    vector<int> BV;
    vector<int> BV2;
    vector<int> BV3;

    int grau;
    for(int v : T.V)
    {
        grau = 0;
        for(pair<int,int> ij : T.E)
        {
            int i = ij.first;
            int j = ij.second;
            if(i == v or j == v)
            {
                grau += 1;
            }
        }
        if(grau > 2)
        {
            BV.push_back(v);
        }
    }
    grau = 0;
    for(int v : T2.V)
    {
        grau = 0;
        for(pair<int,int> ij : T2.E)
        {
            int i = ij.first;
            int j = ij.second;
            if(i == v or j == v)
            {
                grau += 1;
            }
        }
        if(grau > 2)
        {
            BV2.push_back(v);
        }
    }
    grau = 0;
    for(int v : T3.V)
    {
        grau = 0;
        for(pair<int,int> ij : T3.E)
        {
            int i = ij.first;
            int j = ij.second;
            if(i == v or j == v)
            {
                grau += 1;
            }
        }
        if(grau > 2)
        {
            BV3.push_back(v);
        }
    }

    string verificado;
    string verificado2;
    string verificado3;

    if(T.ValidarArvore() == true && T.V.size() == G.V.size() && BT.size() == BV.size())
        verificado = "True";
    else
       verificado = "False";

    if(T2.ValidarArvore() == true && T2.V.size() == G.V.size() && BT2.size() == BV2.size())
        verificado2 = "True";
    else
       verificado2 = "False";

    if(T3.ValidarArvore() == true && T3.V.size() == G.V.size() && BT3.size() == BV3.size())
        verificado3 = "True";
    else
       verificado3 = "False";

    float somaGrau = 0;

    cout << argv[1] << "\t " << BT.size() << "\t ";
    cout << std::fixed << std::setprecision(10) << time_spent << "\t " << verificado << "\t ";

    for (int v : GrauBT)
    {
        somaGrau = somaGrau + v;
    }
    if (GrauBT.size() == 0)
    {
        cout << "0";
    }
    else
    {
        float mediaGrau = somaGrau / GrauBT.size();
        cout << mediaGrau;
    }

    cout << "\t " << BT2.size() << "\t ";
    cout << std::fixed << std::setprecision(10) << time_spent2 << "\t " << verificado2 << "\t ";
    somaGrau = 0;
    for (int v : GrauBT2)
    {
        somaGrau = somaGrau + v;
    }
    if (GrauBT2.size() == 0)
    {
        cout << "0";
    }
    else
    {
        float mediaGrau = somaGrau / GrauBT2.size();
        cout << mediaGrau;
    }

    cout << "\t " << BT3.size() << "\t ";
    cout << std::fixed << std::setprecision(10) << time_spent3 << "\t " << verificado3 << "\t ";
    somaGrau = 0;
    for (int v : GrauBT3)
    {
        somaGrau = somaGrau + v;
    }
    if (GrauBT3.size() == 0)
    {
        cout << "0";
    }
    else
    {
        float mediaGrau = somaGrau / GrauBT3.size();
        cout << mediaGrau;
    }
    cout << endl;*/
    return 0;
}
