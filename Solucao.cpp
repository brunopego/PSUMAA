#include "Solucao.h"
#include "Tarefa.h"
#include "Problema.h"

//using namespace std;

Solucao::Solucao(Problema* prob) {
    this->prob = prob;
    for (int i = 1; i <= this->prob->getQtd_tarefas() ; ++i) {
        this->jobs.push_back(Job(i));
    }
}

vector<Job> &Solucao::getJobs() {
    return jobs;
}

int Solucao::getAntecipacao(const Job& job) const {
    int fim = job.getInicio() + prob->getTarefas().at(job.getId()-1).getTp();
    int e = prob->getTarefas().at(job.getId()-1).getE();
    if(fim < e) {
        return (e - fim);
    }

    return 0;
}

int Solucao::getAtraso(const Job& job) const {
    int fim = job.getInicio() + prob->getTarefas().at(job.getId()-1).getTp();
    int t = prob->getTarefas().at(job.getId()-1).getT();
    if(fim > t) {
        return (fim - t);
    }

    return 0;
}

int Solucao::getCusto() const {
    int total = 0;
    for(auto &job : Solucao::jobs){
        int job_alfa = prob->getTarefas().at(job.getId()-1).getAlfa();
        int job_beta = prob->getTarefas().at(job.getId()-1).getBeta();
        int job_antecipacao = getAntecipacao(job);
        int job_atraso = getAtraso(job);
        total += (job_alfa * job_antecipacao) + (job_beta * job_atraso);
    }
    return total;
}
