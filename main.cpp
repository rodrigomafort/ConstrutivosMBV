#include <iostream>
#include <set>
#include <vector>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "AndersonV4.h"

using namespace std;

int main(int argc, char *argv[]){
    if (argc < 2){
		cout << "Nome do arquivo não recebido" << endl;
		return 1;
	}

	Grafo G = Grafo::LerArquivo(argv[1]);

    double time_spent = 0.0;
    clock_t start = clock();

    //cout << "INI" << endl;
    AndersonV4 alg = AndersonV4(G);

    //cout << "ALG" << endl;
    alg.Oliveira();

    //cout << "OK" << endl;

    clock_t end = clock();
    time_spent += (double)(end - start) / CLOCKS_PER_SEC;

    Grafo T = alg.ObterArvore();
    vector<int> BT = alg.ObterBranches();

    vector<int> BV;
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

    string verificado;
    if(T.ValidarArvore() == true && T.V.size() == G.V.size() && BT.size() == BV.size())
        verificado = "True";
    else
       verificado = "False";

    cout << argv[1] << "\t " << BT.size() << "\t ";
    cout << std::fixed << std::setprecision(10) << time_spent << "\t " << verificado << endl;
    return 0;
}
/*
    vector<int> V;
    for(int i=0; i < 20; i++){
        V.push_back(i);
    }

    vector<pair<int,int>> E;

    E.push_back(make_pair(1-1, 9-1));
    E.push_back(make_pair(1-1, 13-1));
    E.push_back(make_pair(1-1, 19-1));
    E.push_back(make_pair(1-1, 20-1));
    E.push_back(make_pair(2-1, 12-1));
    E.push_back(make_pair(2-1, 13-1));
    E.push_back(make_pair(2-1, 14-1));
    E.push_back(make_pair(3-1, 12-1));
    E.push_back(make_pair(3-1, 20-1));
    E.push_back(make_pair(4-1, 13-1));
    E.push_back(make_pair(4-1, 15-1));
    E.push_back(make_pair(5-1, 9-1));
    E.push_back(make_pair(5-1, 16-1));
    E.push_back(make_pair(6-1,10-1));
    E.push_back(make_pair(7-1, 12-1));
    E.push_back(make_pair(7-1, 18-1));
    E.push_back(make_pair(8-1, 13-1));
    E.push_back(make_pair(8-1, 19-1));
    E.push_back(make_pair(9-1, 10-1));
    E.push_back(make_pair(9-1, 12-1));
    E.push_back(make_pair(10-1, 15-1));
    E.push_back(make_pair(10-1, 19-1));
    E.push_back(make_pair(11-1, 12-1));
    E.push_back(make_pair(12-1, 17-1));
    E.push_back(make_pair(14-1, 20-1));
    E.push_back(make_pair(15-1, 20-1));
    E.push_back(make_pair(18-1, 20-1));

    vector<vector<int>> adj(20);
    for(pair<int,int> ij : E){
        int i = ij.first;
        int j = ij.second;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    */
