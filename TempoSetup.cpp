#include "TempoSetup.h"
#include <iostream>
#include <exception>

using namespace std;


TempoSetup::TempoSetup() {}

TempoSetup::TempoSetup(const int &t) : tam(t) {
    try {
        this->matriz_ts = new int*[this->tam];

        for(int i = 0; i < this->tam; i++){
            try {
                   this->matriz_ts[i] = new int[this->tam];
            } catch(exception& e){
                cout << "[2] ERRO AO TENTAR ALOCAR A MATRIZ" << endl;
            }
        }
    } catch(exception& e){
        cout << "[1] ERRO AO TENTAR ALOCAR A MATRIZ" << endl;
    }

}

TempoSetup::~TempoSetup() {
    for (int i = 0; i < this->tam; ++i) {
        delete[] TempoSetup::matriz_ts[i];
    }
    delete[] TempoSetup::matriz_ts;
}

void TempoSetup::setTempoSetup(const int &x, const int &y, const int &valor) {
    this->matriz_ts[x][y] = valor;
}

int TempoSetup::getTempoSetup(const int &x, const int &y) {
    return this->matriz_ts[x][y];
}