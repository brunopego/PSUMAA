#ifndef PSUMAA_ARQUIVO_H
#define PSUMAA_ARQUIVO_H

#include <iostream>
#include <vector>
#include <string>
#include "Tarefa.h"

using namespace std;

class Problema {

private:
    vector<Tarefa> tarefas; // vetor com os dados de cada tarefa do problema
    string nome_arq; // nome do arquivo com as instancias
    int qtd_tarefas; // numero de tarefas a serem programadas
    int** matriz_ts = nullptr; // matriz com o tempo de setup

public:

    Problema(const string& nome_arq);

    ~Problema();

    vector<Tarefa> getTarefas() const;

    void addTarefa(const Tarefa &tarefas);

    const string &getNome_arq() const;

    void setNome_arq(const string &nome_arq);

    int getQtd_tarefas() const;

    void setQtd_tarefas(int qtd_tarefas);

    int getCusto() const;

    void setTempoSetup(const int& x, const int& y, const int& valor);

    int getTempoSetup(const int& x, const int& y);

};


#endif //PSUMAA_ARQUIVO_H
