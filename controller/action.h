#ifndef ACTION_H
#define ACTION_H

#include <QThread>
#include "model/key.h"

class Action : public QThread
{
private:
    Key key;
    int delay;
    bool finish = false;
public:
    Action() {}
    Action(Key key, int delay);

    void setKey(Key key);
    void setDelay(int delay);
    void setFinish(bool finish);

    void run();
};

#endif // ACTION_H
