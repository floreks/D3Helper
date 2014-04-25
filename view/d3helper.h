#ifndef D3HELPER_H
#define D3HELPER_H

#include <QMainWindow>
#include <controller/layoutmanager.h>
#include "controller/action.h"
#include <QDebug>
#include <QMap>

namespace Ui {
class D3Helper;
}

class D3Helper : public QMainWindow
{
    Q_OBJECT

public:
    explicit D3Helper(QWidget *parent = 0);
    ~D3Helper();

private:
    void initialize();
    void connectWidgets(QList<QWidget*> widgets);

    Ui::D3Helper *ui;
    LayoutManager manager;
    QMap<int,Action*> actions;

private Q_SLOTS:
    void buttonChosen(int);
    void enabledClicked(bool);
    void shiftClicked(bool);
    void delayChanged(QString);
    void addButtonClicked();
    void removeButtonClicked();
};

#endif // D3HELPER_H
