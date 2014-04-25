#ifndef CONSTVALUES_H
#define CONSTVALUES_H

#include "QCoreApplication"
#include "QDir"


#define KEYMAP_FILENAME "mapping.ini"
#define KEYMAP_FILEPATH QCoreApplication::applicationDirPath() + QDir::separator() + KEYMAP_FILENAME

#endif // CONSTVALUES_H
