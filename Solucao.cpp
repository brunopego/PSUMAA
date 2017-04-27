#include "Solucao.h"
#include "Tarefa.h"
#include "Problema.h"

#include <algorithm>

//using namespace std;

Solucao::Solucao(Problema* prob) {
    this->prob = prob;

    for (int i = 1; i <= prob->getQtd_tarefas() ; ++i) {
        this->jobs.push_back(Job(&(prob->getTarefas()[i-1]), i));
    }
}

vector<Job> &Solucao::getJobs() {
    return jobs;
}

int Solucao::getAntecipacao(const Job& job) const {
    int fim = job.getInicio() + job.t->getTp();
    int e = job.t->getE();
    if(fim < e) {
        return (e - fim);
    }

    return 0;
}

int Solucao::getAtraso(const Job& job) const {
    int fim = job.getInicio() + job.t->getTp();

    int t = job.t->getT();
    if(fim > t) {
        return (fim - t);
    }

    return 0;
}

int Solucao::getCusto() const {
    int total = 0;
    for(auto job : jobs){
        int job_alfa = job.t->getAlfa();
        int job_beta = job.t->getBeta();
        int job_antecipacao = getAntecipacao(job);
        int job_atraso = getAtraso(job);
        total += (job_alfa * job_antecipacao) + (job_beta * job_atraso);
        std::cout << "job_alfa " << job_alfa << std::endl;
        std::cout << "job_beta " << job_beta << std::endl;
        std::cout << "job_antecipacao " << job_antecipacao << std::endl;
        std::cout << "job_atraso " << job_atraso << std::endl << std::endl;
    }
    return total;
}


bool edd_funcao(const Job &j, const Job& q) {
    int jEarliness = j.t->getE();
    int qEarliness = q.t->getE();
    return (jEarliness < qEarliness);
}

bool tdd_funcao(const Job &j, const Job& q) {
    int jTardiness = j.t->getT();
    int qTardiness = q.t->getT();
    return (jTardiness > qTardiness);
}

bool spt_funcao(const Job &j, const Job& q) {
    int jTempoProcessamento = j.t->getTp();
    int qTempoProcessamento = q.t->getTp();
    return (jTempoProcessamento < qTempoProcessamento);
}

void Solucao::edd_ordena() {
    sort(jobs.begin(), jobs.end(), edd_funcao);
}

void Solucao::tdd_ordena() {
    sort(jobs.begin(), jobs.end(), tdd_funcao);
}

void Solucao::spt_ordena() {
    sort(jobs.begin(), jobs.end(), spt_funcao);
}

