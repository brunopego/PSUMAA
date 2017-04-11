#ifndef PSUMAA_SOLUCAO_H
#define PSUMAA_SOLUCAO_H


#include "Job.h"
#include "Problema.h"
#include <vector>

using namespace std;

class Solucao {

private:
    vector<Job> jobs; // vetor com os dados de cada tarefa do problema
    Problema *prob;
    //int qtd_tarefas; // quantidade de jobs/tarefas

public:
    Solucao(Problema* prob);

    vector<Job> &getJobs();

    int getCusto() const;

    int getAntecipacao(const Job& job) const;

    int getAtraso(const Job& job) const;

};


#endif //PSUMAA_SOLUCAO_H
