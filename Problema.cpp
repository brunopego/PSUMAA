#include "Problema.h"
#include "Tarefa.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Problema::Problema(const string& nome_arq) {

    ifstream reader(nome_arq);

    reader >> this->qtd_tarefas;

    try {
        this->matriz_ts = new int*[this->qtd_tarefas];

        for(int i = 0; i < this->qtd_tarefas; i++){
            try {
                this->matriz_ts[i] = new int[this->qtd_tarefas];
            } catch(exception& e){
                cout << "[2] ERRO AO TENTAR ALOCAR A MATRIZ" << endl;
            }
        }
    } catch(exception& e){
        cout << "[1] ERRO AO TENTAR ALOCAR A MATRIZ" << endl;
    }

    // Campos tarefa:
    int id; // id da tarefa
    int tp; // tempo necessario para processamento da tarefa
    int e; // e -> earliness, data de inicio da janela
    int t; // t -> tardiness, data final da janela
    int alfa; // custo de antecipacao
    int beta; // custo de atraso


    for (int i = 0; i < qtd_tarefas; ++i) {
        reader >> id >> tp >> e >> t >> alfa >> beta;
        Tarefa tar(id, tp, e, t, alfa, beta);
        this->addTarefa(tar);
    }

    int valor = 0;
    for (int i = 0; i < qtd_tarefas; ++i) {
        for (int j = 0; j < qtd_tarefas; ++j) {
            reader >> valor;
            this->setTempoSetup(i, j, valor);
        }
    }

    reader.close();

}

Problema::~Problema() {
    for (int i = 0; i < this->qtd_tarefas; ++i) {
        delete[] Problema::matriz_ts[i];
    }
    delete[] Problema::matriz_ts;
}

vector<Tarefa> Problema::getTarefas() const {
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
        total += (tarefa.getAlfa() * tarefa.getAntecipacao()) + (tarefa.getBeta() * tarefa.getAtraso());
    }
    return 0;
}

void Problema::setTempoSetup(const int &x, const int &y, const int &valor) {
    this->matriz_ts[x][y] = valor;
}

int Problema::getTempoSetup(const int &x, const int &y) {
    return this->matriz_ts[x-1][y-1];
}