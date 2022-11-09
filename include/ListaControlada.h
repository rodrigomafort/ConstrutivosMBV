#ifndef LISTACONTROLADA_H
#define LISTACONTROLADA_H

#include <vector>

using namespace std;

class ListaControlada
{
    public:
        ListaControlada(int tamanho);
        virtual ~ListaControlada();

        void Inicializar();
        bool Verificar(int valor);
        bool AdicionarItem(int valor);
        bool RemoverItem(int valor);

    protected:
        int tamanho;
        vector<int> lista;
        vector<bool> controle;
    private:
};

#endif // LISTACONTROLADA_H
