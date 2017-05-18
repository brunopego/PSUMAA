#include "Tarefa.h"
#include <iostream>
using namespace std;

Tarefa::Tarefa() {}

Tarefa::Tarefa(int id, int tp, int e, int t, int alfa, int beta){
    this->id = id;
    this->tp = tp;
    this->e = e;
    this->t = t;
    this->alfa = alfa;
    this->beta = beta;
    this->inicio = 0;
    this->fim = this->inicio + this->tp;
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

int Tarefa::getInicio() const {
    return inicio;
}

void Tarefa::setInicio(int inicio) {
    Tarefa::inicio = inicio;
    this->fim = this->inicio + this->tp;
}

int Tarefa::getFim() const {
    return this->inicio + this->tp;
}

void Tarefa::setFim(int fim) {
    Tarefa::fim = fim;
}

int Tarefa::getAntecipacao() const {
    if(this->fim < this->e) {
        return ((this->e) - (this->fim));
    }

    return 0;
}

int Tarefa::getAtraso() const {
    if(this->fim > this->t) {
        return ((this->fim) - (this->t));
    }

    return 0;
}

