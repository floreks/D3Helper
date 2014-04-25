#include "action.h"

#include <QDebug>
#include "controller/gamewindow.h"

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
        delay = delay == 0 ? 100 : delay;
        GameWindow::simulateClick(key,shiftClicked,pos);
        msleep(delay);
    }
}

void Action::setShift(bool click) {
    this->shiftClicked = click;
}

void Action::setMousePos(POINT p) {
    this->pos = p;
}
