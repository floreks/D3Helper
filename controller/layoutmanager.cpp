#include "layoutmanager.h"

#include <QDebug>
#include <QHBoxLayout>

void LayoutManager::addLayout(QGroupBox *layout) {
    if(keyLayouts.size() == 0) {
        pos = layout->geometry();
    }
    keyLayouts.push_back(layout);
}

QRect LayoutManager::getNextPosition() {
    return QRect(pos.left(),pos.top()+51*(keyLayouts.size()-1),pos.width(),pos.height());
}

short int LayoutManager::layoutsCount()const {
    return keyLayouts.size();
}

QList<QWidget*> LayoutManager::copyWidgets(QGroupBox *box) {
    QList<QWidget*> result;
    for(QObject *obj : keyLayouts[0]->children()) {
        if(obj->objectName().contains("layout",Qt::CaseInsensitive)) {
            box->setLayout(new QHBoxLayout());
        } else if(obj->objectName().contains("label",Qt::CaseInsensitive)) {
            box->layout()->addWidget(copyLabel(obj));
        } else if(obj->objectName().contains("lineedit",Qt::CaseInsensitive)) {
            result.push_back(copyLineEdit(obj));
            box->layout()->addWidget(result.last());
        } else if(obj->objectName().contains("checkbox",Qt::CaseInsensitive)) {
            result.push_back(copyCheckBox(obj));
            box->layout()->addWidget(result.last());
        } else if(obj->objectName().contains("combobox",Qt::CaseInsensitive)) {
            result.push_back(copyComboBox(obj));
            box->layout()->addWidget(result.last());
        }
    }
    return result;
}

void LayoutManager::removeLast() {
    if(keyLayouts.size() > 1) {
        QGroupBox *box = keyLayouts.last();
        keyLayouts.pop_back();
        delete box;
    }
}

QComboBox* LayoutManager::getComboBoxAt(int i) {
    QComboBox *result;
    for(QObject *obj : keyLayouts.at(i-1)->children()) {
        if(obj->objectName().contains("combobox",Qt::CaseInsensitive)) {
            result = qobject_cast<QComboBox*>(obj);
        }
    }
    return result;
}

QCheckBox* LayoutManager::getShiftBoxAt(int i) {
    QCheckBox *result;
    for(QObject *obj : keyLayouts.at(i-1)->children()) {
        if(obj->objectName().contains("shiftcheckbox",Qt::CaseInsensitive)) {
            result = qobject_cast<QCheckBox*>(obj);
        }
    }
    return result;
}

QCheckBox* LayoutManager::getEnabledBoxAt(int i) {
    QCheckBox *result;
    for(QObject *obj : keyLayouts.at(i-1)->children()) {
        if(obj->objectName().contains("enabledcheckbox",Qt::CaseInsensitive)) {
            result = qobject_cast<QCheckBox*>(obj);
        }
    }
    return result;
}

QLineEdit* LayoutManager::getLineBoxAt(int i) {
    QLineEdit *result;
    for(QObject *obj : keyLayouts.at(i-1)->children()) {
        if(obj->objectName().contains("lineedit",Qt::CaseInsensitive)) {
            result = qobject_cast<QLineEdit*>(obj);
        }
    }
    return result;
}

// ======================== PRIVATE ========================== //

QLabel* LayoutManager::copyLabel(QObject *obj) {
    QLabel *oldLabel = qobject_cast<QLabel*>(obj);
    QLabel *newLabel = new QLabel();

    newLabel->setText(oldLabel->text());
    return newLabel;
}

QComboBox* LayoutManager::copyComboBox(QObject *obj) {
    QComboBox *oldComboBox = qobject_cast<QComboBox*>(obj);
    QComboBox *newComboBox = new QComboBox();

    for(int i=0;i<oldComboBox->count();i++) {
        newComboBox->addItem(oldComboBox->itemText(i),oldComboBox->itemData(i));
    }
    newComboBox->setObjectName(oldComboBox->objectName() + " " + QString::number(keyLayouts.size()));

    return newComboBox;
}

QCheckBox* LayoutManager::copyCheckBox(QObject* obj) {
    QCheckBox *oldCheckBox = qobject_cast<QCheckBox*>(obj);
    QCheckBox *newCheckBox = new QCheckBox();

    newCheckBox->setText(oldCheckBox->text());
    newCheckBox->setObjectName(oldCheckBox->objectName() + " " + QString::number(keyLayouts.size()));
    return newCheckBox;
}

QLineEdit* LayoutManager::copyLineEdit(QObject *obj) {
    QLineEdit *oldLineEdit = qobject_cast<QLineEdit*>(obj);
    QLineEdit *lineEdit = new QLineEdit();

    lineEdit->setObjectName(oldLineEdit->objectName() + " " + QString::number(keyLayouts.size()));
    return lineEdit;
}
