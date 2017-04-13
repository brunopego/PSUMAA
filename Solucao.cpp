#include "Solucao.h"
#include "Tarefa.h"
#include "Problema.h"

#include <algorithm>

//using namespace std;

Solucao::Solucao(Problema* prob) {
    this->prob = prob;
    for (int i = 1; i <= this->prob->getQtd_tarefas() ; ++i) {
        this->jobs.push_back(Job(prob, i));
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

bool Solucao::edd_funcao(const Job &j, const Job& q) {
    int jEarliness = prob->getTarefas().at(j.getId()-1).getE();
    int qEarliness = prob->getTarefas().at(q.getId()-1).getE();
    return (jEarliness < qEarliness);
}

bool Solucao::tdd_funcao(const Job &j, const Job& q) {
    int jTardiness = prob->getTarefas().at(j.getId()-1).getT();
    int qTardiness = prob->getTarefas().at(q.getId()-1).getT();
    return (jTardiness > qTardiness);
}

bool Solucao::spt_funcao(const Job &j, const Job& q) {
    int jTempoProcessamento = prob->getTarefas().at(j.getId()-1).getTp();
    int qTempoProcessamento = prob->getTarefas().at(q.getId()-1).getTp();
    return (jTempoProcessamento < qTempoProcessamento);
}

void Solucao::edd_ordena() {
    sort(jobs.begin(), jobs.end(), edd_funcao);
}

void Solucao::tdd_ordena() {
    sort(jobs.begin(), jobs.end(), tdd_funcao);
}

void Solucao::stp_ordena() {
    sort(jobs.begin(), jobs.end(), spt_funcao);
}
