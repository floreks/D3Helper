#ifndef KEY_H
#define KEY_H

enum KeyType {
    MOUSE = 0x01,
    KEYBOARD = 0x02
};

#include <QString>
#include <QMetaType>

class Key
{
private:
    KeyType type;
    short int keyCode;
    QString keyName;
public:
    Key() {}
    Key(QString keyName, short int keyCode, KeyType type);

    short int getKeyCode()const;
    QString getKeyName()const;
    bool isKeyboardKey()const;
    bool isMouseKey()const;
};

Q_DECLARE_METATYPE(Key)

#endif // KEY_H
