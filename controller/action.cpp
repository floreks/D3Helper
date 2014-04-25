#include "action.h"

#include <QDebug>

Action::Action(Key key, int delay) {
    this->key = key;
    this->delay = delay;
}

void Action::setKey(Key key) {
    this->key = key;
}

void Action::setDelay(int delay) {
    this->delay = delay;
}

void Action::setFinish(bool finish) {
    this->finish = finish;
}

void Action::run() {

    while(!finish) {
        qDebug() << key.getKeyName();
        msleep(delay);
    }

    qDebug() << "Finish";
}
