#include "Problema.h"
#include "Tarefa.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Problema::Problema(const string& nome_arq) {
    this->nome_arq = nome_arq;
    ifstream reader(nome_arq);

    // le primeira informacao do aquivo que e a qtd de tarefas
    reader >> this->qtd_tarefas;


    // faz a alocacao da matriz necessaria para armazenar o tempo de setup das tarefas
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

    // le o id, tp, e, t, alfa  e beta do arquivo e carrega nas respectivas variaveis
    for (int i = 0; i < qtd_tarefas; ++i) {
        reader >> id >> tp >> e >> t >> alfa >> beta;
        Tarefa tar(id, tp, e, t, alfa, beta);
        this->addTarefa(tar);
    }

    // carrega a matriz alocada anteriormente com os respectivos valores
    int valor = 0;
    for (int i = 0; i < qtd_tarefas; ++i) {
        for (int j = 0; j < qtd_tarefas; ++j) {
            reader >> valor;
            /*
             * na linha i e coluna j contem o valor que representa o tempo de setup entre uma
             * tarefa i e uma tarefa j
             */
            this->setTempoSetup(i, j, valor);
        }
    }

    reader.close();

}

// Destrutor da classe, a memoria alocada para a matriz e liberada
Problema::~Problema() {
    for (int i = 0; i < this->qtd_tarefas; ++i) {
        delete[] Problema::matriz_ts[i];
    }
    delete[] Problema::matriz_ts;
}

// retorna o vetor de tarefas contido no problema
vector<Tarefa> &Problema::getTarefas() {
    return tarefas;
}

// adiciona uma tarefa ao problema
void Problema::addTarefa(const Tarefa &tarefa) {
    Problema::tarefas.push_back(tarefa);
}

// retorna o nome do arquivo que contem o problema
const string &Problema::getNome_arq() const {
    return nome_arq;
}

// altera o nome do arquivo que contem o problema
void Problema::setNome_arq(const string &nome_arq) {
    Problema::nome_arq = nome_arq;
}

// retorna a quantidade de tarefas que contem no problema
int Problema::getQtd_tarefas() const {
    return qtd_tarefas;
}

// altera a quantidade de tarefas que contem no problema
void Problema::setQtd_tarefas(int qtd_tarefas) {
    Problema::qtd_tarefas = qtd_tarefas;
}

// retorna o custo do problema (OBS: Utilizar a funcao correspondente na classe Solucao)
int Problema::getCusto() const {
    int total = 0;
    for(auto &tarefa : Problema::tarefas){
        total += (tarefa.getAlfa() * tarefa.getAntecipacao()) + (tarefa.getBeta() * tarefa.getAtraso());
    }
    return total;
}

// altera o tempo de setup entre uma tarefa e outra
void Problema::setTempoSetup(const int &x, const int &y, const int &valor) {
    this->matriz_ts[x][y] = valor;
}

// retorna o tempo de setup entre uma tarefa e outra
int Problema::getTempoSetup(const int &x, const int &y) {
    return this->matriz_ts[x-1][y-1];
}