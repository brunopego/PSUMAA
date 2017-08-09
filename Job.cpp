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

int Job::getFim() const {
    return this->inicio + this->t->getTp();
}


bool Job::operator==(const Job &job) const {
    return this->id == job.id;
}

bool Job::operator!=(const Job &job) const {
    return this->id != job.id;
}

Job& Job::operator=(Job job) {

    this->id = job.getId();
    this->inicio = job.getInicio();
    this->t = job.t;

    return *this;
}