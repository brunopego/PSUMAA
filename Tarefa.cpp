#include "Tarefa.h"

Tarefa::Tarefa(int id, int tp, int e, int t, int alfa, int beta){
    this->id = id;
    this->tp = tp;
    this->e = e;
    this->t = t;
    this->alfa = alfa;
    this->beta = beta;
}

int Tarefa::getId() const {
    return id;
}

void Tarefa::setId(int id) {
    Tarefa::id = id;
}

int Tarefa::getTp() const {
    return tp;
}

void Tarefa::setTp(int tp) {
    Tarefa::tp = tp;
}

int Tarefa::getE() const {
    return e;
}

void Tarefa::setE(int e) {
    Tarefa::e = e;
}

int Tarefa::getT() const {
    return t;
}

void Tarefa::setT(int t) {
    Tarefa::t = t;
}

int Tarefa::getAlfa() const {
    return alfa;
}

void Tarefa::setAlfa(int alfa) {
    Tarefa::alfa = alfa;
}

int Tarefa::getBeta() const {
    return beta;
}

void Tarefa::setBeta(int beta) {
    Tarefa::beta = beta;
}