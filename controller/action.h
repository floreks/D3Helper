#ifndef ACTION_H
#define ACTION_H

#include <QThread>
#include "model/key.h"
#include <windows.h>

class Action : public QThread
{
private:
    Key key;
    int delay;
    bool finish = false;
    bool shiftClicked = false;
    POINT pos;
public:
    Action() {}
    Action(Key key, int delay);

    void setKey(Key key);
    void setDelay(int delay);
    void setFinish(bool finish);
    void setShift(bool click);
    void setMousePos(POINT p);

    void run();
};

#endif // ACTION_H
