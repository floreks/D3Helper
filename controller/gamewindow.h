#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QString>
#include <windows.h>
#include "model/key.h"

class GameWindow
{
private:
    static HWND windowHandle;
public:
    GameWindow() = delete;

    static bool setWindowName(QString windowName);

    static void simulateClick(Key key, bool shiftClicked, POINT mousePos);
};

#endif // GAMEWINDOW_H
