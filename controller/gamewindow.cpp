#include "gamewindow.h"

#include <QDebug>

HWND GameWindow::windowHandle;

bool GameWindow::setWindowName(QString windowName) {
    windowHandle = FindWindowA(NULL,windowName.toStdString().c_str());
    return windowHandle != NULL;
}

void GameWindow::simulateClick(Key key, bool shiftClicked, POINT mousePos) {
    PostMessage(windowHandle,WM_MOUSEMOVE,WM_MOUSEMOVE,MAKELPARAM(mousePos.x,mousePos.y));

    if(key.isKeyboardKey()) {
        if(shiftClicked) PostMessage(windowHandle,WM_KEYDOWN,VK_SHIFT,0);
        PostMessage(windowHandle,WM_KEYDOWN,key.getKeyCode(),0);

        PostMessage(windowHandle,WM_KEYUP,key.getKeyCode(),0);
        if(shiftClicked) PostMessage(windowHandle,WM_KEYUP,VK_SHIFT,0);
    } else {
        if(shiftClicked) PostMessage(windowHandle,WM_KEYDOWN,VK_SHIFT,0);
        if(VK_LBUTTON == key.getKeyCode()) PostMessage(windowHandle,WM_LBUTTONDOWN,WM_LBUTTONDOWN,MAKELPARAM(mousePos.x,mousePos.y));
        else PostMessage(windowHandle,WM_RBUTTONDOWN,WM_RBUTTONDOWN,MAKELPARAM(mousePos.x,mousePos.y));

        if(VK_LBUTTON == key.getKeyCode()) PostMessage(windowHandle,WM_LBUTTONDOWN,WM_LBUTTONDOWN,MAKELPARAM(mousePos.x,mousePos.y));
        else PostMessage(windowHandle,WM_RBUTTONDOWN,WM_RBUTTONDOWN,MAKELPARAM(mousePos.x,mousePos.y));
        if(shiftClicked) PostMessage(windowHandle,WM_KEYUP,VK_SHIFT,0);
    }
}
