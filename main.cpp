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

using namespace std;

int main(int argc, char *argv[]){
    if (argc < 2){
		cout << "Nome do arquivo não recebido" << endl;
		return 1;
	}

	Grafo G = Grafo::LerArquivo(argv[1]);
	Grafo G2 = Grafo::LerArquivo(argv[1]);
	Grafo G3 = Grafo::LerArquivo(argv[1]);

    double time_spent = 0.0;
    clock_t start1 = clock();

    AndersonV4 alg = AndersonV4(G);
    alg.Oliveira();

    clock_t end1 = clock();
    time_spent += (double)(end1 - start1) / CLOCKS_PER_SEC;

    double time_spent2 = 0.0;
    clock_t start2 = clock();

    Rodrigo alg2 = Rodrigo(G2);
    alg2.Oliveira();

    clock_t end2 = clock();
    time_spent2 += (double)(end2 - start2) / CLOCKS_PER_SEC;

    double time_spent3 = 0.0;
    clock_t start3 = clock();

    Algoritmo3 alg3 = Algoritmo3(G3);
    alg3.Oliveira();

    clock_t end3 = clock();
    time_spent3 += (double)(end3 - start3) / CLOCKS_PER_SEC;

    Grafo T = alg.ObterArvore();
    vector<int> BT = alg.ObterBranches();
    vector<int> GrauBT = alg.ObterGrauBT();

    Grafo T2 = alg2.ObterArvore();
    vector<int> BT2 = alg2.ObterBranches();
    vector<int> GrauBT2 = alg2.ObterGrauBT();

    Grafo T3 = alg3.ObterArvore();
    vector<int> BT3 = alg3.ObterBranches();
    vector<int> GrauBT3 = alg3.ObterGrauBT();

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

    if(T2.ValidarArvore() == true && T2.V.size() == G2.V.size() && BT2.size() == BV2.size())
        verificado2 = "True";
    else
       verificado2 = "False";

    if(T3.ValidarArvore() == true && T3.V.size() == G3.V.size() && BT3.size() == BV3.size())
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
    cout << endl;
    return 0;
}
