#include "Job.h"

Job::Job() {}

Job::Job(Tarefa *t, const int &id) {
    this->t = t;
    this->id = id;
}

Job::Job(Tarefa *t, const int &id, const int &inicio) {
    this->t = t;
    this->id = id;
    this->inicio = inicio;
}

int Job::getId() const {
    return id;
}

void Job::setId(int id) {
    Job::id = id;
}

int Job::getInicio() const {
    return inicio;
}

void Job::setInicio(int inicio) {
    Job::inicio = inicio;
}
