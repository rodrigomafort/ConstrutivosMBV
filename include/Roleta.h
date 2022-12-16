#ifndef ROLETA_H
#define ROLETA_H

#include <vector>
#include <random>
#include <iomanip>

#include "Grafo.h"

using namespace std;

class ItemRoleta
{
    public:
        double prob;
        double probCalc;
        double lowerBound;
        double upperBound;
        int key;

        ItemRoleta(int key, double prob);
};

class Roleta
{
    private:
        double soma;
        vector<ItemRoleta> itens;

    public:
        Roleta();
        ~Roleta();

        void Adicionar(int key, double probalilidade);
        int Sortear();
};

#endif // ROLETA_H
