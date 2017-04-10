#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Tarefa.h"
#include "Problema.h"
#include "TempoSetup.h"

using namespace std;


void ler_arquivo(const string& nome_arq, Problema *p);

TempoSetup tempo_setup;


int main() {

    string nome_arq = "instancias/dados/INST0703.dat";
    Problema p;

    ler_arquivo(nome_arq, &p);

    //cout << "coisa" << endl;


    // ----------------------------------------------------------
    tempo_setup.~TempoSetup();
    return 0;
}

void ler_arquivo(const string& nome_arq, Problema *p) {

    int qtd_tarefas;

    ifstream reader(nome_arq);
    
    reader >> qtd_tarefas;
    tempo_setup = qtd_tarefas;

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
        p->addTarefa(tar);
    }

    int valor = 0;
    for (int i = 0; i < qtd_tarefas; ++i) {
        for (int j = 0; j < qtd_tarefas; ++j) {
            reader >> valor;
            tempo_setup.setTempoSetup(i, j, valor);
        }
    }

    reader.close();

}