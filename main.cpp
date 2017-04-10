#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Tarefa.h"
#include "Problema.h"
#include "TempoSetup.h"

TempoSetup ler_arquivo(const string& nome_arq, Problema *p);

using namespace std;

int main() {

    string nome_arq = "/instancias/dados/INST0703.dat";
    Problema p;

    ler_arquivo(nome_arq, &p);


    return 0;
}

TempoSetup ler_arquivo(const string& nome_arq, Problema *p) {

    int qtd_tarefas;

    ifstream reader(nome_arq);
    cout << nome_arq << endl;
    reader.close();

    return NULL;
}