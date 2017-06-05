#include "Populacao.h"
#include <utility>

void Populacao::insere(Solucao &solucao) {

    pair<unordered_set<Solucao, HashSolucao>::iterator,bool> p;
    p = populacao.insert(solucao);
    if(p.second == false) cout << "Nao inseriu";

}
