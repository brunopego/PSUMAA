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

    // Destrutor da classe, a memoria alocada para a matriz e liberada
    ~Problema();

    // retorna o vetor de tarefas contido no problema
    vector<Tarefa> &getTarefas();

    // adiciona uma tarefa ao problema
    void addTarefa(const Tarefa &tarefas);

    // retorna o nome do arquivo que contem o problema
    const string &getNome_arq() const;

    // altera o nome do arquivo que contem o problema
    void setNome_arq(const string &nome_arq);

    // retorna a quantidade de tarefas que contem no problema
    int getQtd_tarefas() const;

    // altera a quantidade de tarefas que contem no problema
    void setQtd_tarefas(int qtd_tarefas);

    // retorna o custo do problema (OBS: Utilizar a funcao correspondente na classe Solucao)
    int getCusto() const;

    // altera o tempo de setup entre uma tarefa e outra
    void setTempoSetup(const int& x, const int& y, const int& valor);

    // retorna o tempo de setup entre uma tarefa e outra
    int getTempoSetup(const int& x, const int& y);

};


#endif //PSUMAA_ARQUIVO_H
