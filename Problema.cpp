#include "Problema.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Problema::Problema() {}

const vector<Tarefa> &Problema::getTarefas() const {
    return tarefas;
}

void Problema::addTarefa(const Tarefa &tarefa) {
    Problema::tarefas.push_back(tarefa);
}

const string &Problema::getNome_arq() const {
    return nome_arq;
}

void Problema::setNome_arq(const string &nome_arq) {
    Problema::nome_arq = nome_arq;
}

int Problema::getQtd_tarefas() const {
    return qtd_tarefas;
}

void Problema::setQtd_tarefas(int qtd_tarefas) {
    Problema::qtd_tarefas = qtd_tarefas;
}

int Problema::getCusto() const {
    int total = 0;
    for(auto &tarefa : Problema::tarefas){
        total += (tarefa.getAlfa() * tarefa.getAntecipacao()) + (tarefa.getBeta() * tarefa.getAntecipacao());
    }
    return 0;
}

