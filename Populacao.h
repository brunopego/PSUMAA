#ifndef PSUMAA_POPULACAO_H
#define PSUMAA_POPULACAO_H

#include <vector>
#include <list>
#include <unordered_set>
#include <string>
#include <iostream>

#include "Job.h"
#include "Solucao.h"
#include "Problema.h"

using namespace std;

struct HashSolucao {
    std::size_t operator()(Solucao solucao) const {
        std::size_t ret = 0;
        for (auto i : solucao.getJobs())
            ret ^= std::hash<int>()(i.getId());
        return ret;
    }
};


class Populacao {

private:
    unordered_set<Solucao, HashSolucao> populacao_set;
    list<Solucao> populacao;
    Problema *prob; // referencia para o problema
    int mi; // numero de pais selecionados
    int lambda; // numero de filhos gerados
    /*
     * tipo 1 = edd
     * tipo 2 = tdd
     * tipo 3 = spt
     * tipo >3 = aleatorio
     */
    int tipo;

public:

    Populacao(int mi, int lambda, int tipo, Problema* prob);

    void insereIndividuo(Solucao& solucao);

    list<Solucao> &getPopulacao();

    void ordernarPopulacao();

    void imprimePopulacao();

    void estrategiaEvolutiva();


};


#endif //PSUMAA_POPULACAO_H
