#include "keyhelper.h"

#include <QDebug>
#include <QSettings>

QList<Key> KeyHelper::getKeys(QString filePath) {
    QList<Key> result;
    QSettings configFile(filePath, QSettings::IniFormat);

    configFile.beginGroup("Keyboard");
    for(QString keyName : configFile.childKeys()) {
        result.push_back(Key(keyName,configFile.value(keyName).toString().toInt(NULL,16),KeyType::KEYBOARD));
    }
    configFile.endGroup();

    configFile.beginGroup("Mouse");
    for(QString keyName : configFile.childKeys()) {
        result.push_back(Key(keyName,configFile.value(keyName).toString().toInt(NULL,16),KeyType::MOUSE));
    }
    configFile.endGroup();

    return result;
}
