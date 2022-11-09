#include "ListaControlada.h"
#include <algorithm>

ListaControlada::ListaControlada(int ptamanho)
{
    //ctor
    tamanho = ptamanho;
    Inicializar();
}

ListaControlada::~ListaControlada()
{
    //dtor
}

void ListaControlada::Inicializar()
{
    lista.clear();
    controle = vector<bool>(tamanho,false);
}

bool ListaControlada::Verificar(int valor)
{
    if (valor < tamanho)
        return controle[valor];
    else
        return false;
}

bool ListaControlada::AdicionarItem(int valor)
{
    if (valor < tamanho && controle[valor] == false)
    {
        lista.push_back(valor);
        controle[valor] = true;
        return true;
    }
    else
    {
        return false;
    }

}

bool ListaControlada::RemoverItem(int valor)
{
    if (valor < tamanho && controle[valor] == true)
    {
        lista.erase(std::remove(lista.begin(), lista.end(), 8), lista.end());
        controle[valor] = false;
        return true;
    }
    else
    {
        return false;
    }
}
