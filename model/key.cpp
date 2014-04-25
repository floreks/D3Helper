#include "key.h"

Key::Key(QString keyName, short keyCode, KeyType type) {
    this->keyCode = keyCode;
    this->type = type;
    this->keyName = keyName;
}

short int Key::getKeyCode()const {
    return keyCode;
}

QString Key::getKeyName()const {
    return keyName;
}

bool Key::isKeyboardKey()const {
    return type == KeyType::KEYBOARD;
}

bool Key::isMouseKey()const {
    return type == KeyType::MOUSE;
}
