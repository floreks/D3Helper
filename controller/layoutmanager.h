#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

#include <QGroupBox>
#include <QList>
#include <QRect>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>

class LayoutManager
{
    QList<QGroupBox*> keyLayouts;
    QRect pos;
public:
    LayoutManager() {}

    void addLayout(QGroupBox *layout);
    void removeLast();
    QComboBox* getComboBoxAt(int i);
    QCheckBox* getShiftBoxAt(int i);
    QCheckBox* getEnabledBoxAt(int i);
    QLineEdit* getLineBoxAt(int i);
    QList<QWidget*> copyWidgets(QGroupBox *box);
    QRect getNextPosition();
    short int layoutsCount()const;

private:
    QLabel* copyLabel(QObject* obj);
    QComboBox* copyComboBox(QObject* obj);
    QCheckBox* copyCheckBox(QObject* obj);
    QLineEdit* copyLineEdit(QObject* obj);
};

#endif // LAYOUTMANAGER_H
