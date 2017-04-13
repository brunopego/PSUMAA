#include "Job.h"

Job::Job() {}

Job::Job(Problema *prob, const int &id) {
    this->prob = prob;
    this->id = id;
}

Job::Job(Problema *prob, const int &id, const int &inicio) {
    this->prob = prob;
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
