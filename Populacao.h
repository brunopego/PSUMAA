#ifndef PSUMAA_POPULACAO_H
#define PSUMAA_POPULACAO_H

#include "Solucao.h"
#include <vector>
#include <unordered_set>
#include <string>
#include <iostream>
#include "Job.h"

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
    unordered_set<Solucao, HashSolucao> populacao;

public:

    void insere(Solucao& solucao);


};


#endif //PSUMAA_POPULACAO_H
