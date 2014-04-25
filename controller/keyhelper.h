#ifndef KEYHELPER_H
#define KEYHELPER_H

#include <QList>

#include "model/key.h"
#include "ConstValues.h"

class KeyHelper
{
public:
    KeyHelper() = delete;

    static QList<Key> getKeys(QString filePath = KEYMAP_FILEPATH);
};

#endif // KEYHELPER_H
