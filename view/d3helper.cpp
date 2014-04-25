#include "d3helper.h"
#include "ui_d3helper.h"

#include "controller/keyhelper.h"
#include <QVariant>

D3Helper::D3Helper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::D3Helper)
{
    ui->setupUi(this);
    this->setWindowTitle("D3Helper");
    this->setBaseSize(this->size());

    // Connect slots
    connect(ui->buttonComboBox,SIGNAL(activated(int)),this,SLOT(buttonChosen(int)));
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addButtonClicked()));
    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeButtonClicked()));
    connect(ui->enabledCheckBox,SIGNAL(clicked(bool)),this,SLOT(enabledClicked(bool)));
    connect(ui->shiftCheckBox,SIGNAL(clicked(bool)),this,SLOT(shiftClicked(bool)));
    connect(ui->delayLineEdit,SIGNAL(textEdited(QString)),this,SLOT(delayChanged(QString)));

    initialize();
}

D3Helper::~D3Helper()
{
    delete ui;
}


// ======================== PRIVATE ========================== //

void D3Helper::initialize() {
    manager.addLayout(ui->groupBox);

    for(Key key : KeyHelper::getKeys()) {
        QVariant keyVariant;
        keyVariant.setValue(key);
        ui->buttonComboBox->addItem(key.getKeyName(),QVariant(keyVariant));
    }
}

void D3Helper::connectWidgets(QList<QWidget*> widgets) {
    for(QObject *obj : widgets) {
        if(obj->objectName().contains("lineedit",Qt::CaseInsensitive)) {
            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(obj);
            connect(lineEdit,SIGNAL(textEdited(QString)),this,SLOT(delayChanged(QString)));
        } else if(obj->objectName().contains("enabledcheckbox",Qt::CaseInsensitive)) {
            QCheckBox *checkBox = qobject_cast<QCheckBox*>(obj);
            connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(enabledClicked(bool)));
        } else if(obj->objectName().contains("shiftcheckbox",Qt::CaseInsensitive)) {
            QCheckBox *checkBox = qobject_cast<QCheckBox*>(obj);
            connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(shiftClicked(bool)));
        } else if(obj->objectName().contains("combobox",Qt::CaseInsensitive)) {
            QComboBox *comboBox = qobject_cast<QComboBox*>(obj);
            connect(comboBox,SIGNAL(activated(int)),this,SLOT(buttonChosen(int)));
        }
    }
}

// ======================== SLOTS ========================== //

void D3Helper::addButtonClicked() {
    QGroupBox *frame = new QGroupBox(ui->centralwidget);
    manager.addLayout(frame);
    frame->setGeometry(manager.getNextPosition());
    connectWidgets(manager.copyWidgets(frame));

    this->resize(this->width(),this->baseSize().height()+(51*(manager.layoutsCount()-2)));
    frame->show();
    this->show();
}

void D3Helper::removeButtonClicked() {
    manager.removeLast();
    this->resize(this->width(),this->baseSize().height()+(51*(manager.layoutsCount()-2)));
}

void D3Helper::enabledClicked(bool isChecked) {
    QStringList toSplit = QObject::sender()->objectName().split(" ");
    int boxNr = 1;

    if(toSplit.size() > 1) {
        boxNr = toSplit[1].toInt();
    }

    if(isChecked) {
        QComboBox *box = manager.getComboBoxAt(boxNr);
        QLineEdit *line = manager.getLineBoxAt(boxNr);
        QCheckBox *shift = manager.getShiftBoxAt(boxNr);
        Key key = box->currentData().value<Key>();
        int delay = line->text().toInt();

        actions.insert(boxNr,new Action(key,delay));
        actions.find(boxNr).value()->start();
    } else {
        actions.find(boxNr).value()->setFinish(true);
        actions.remove(boxNr);
    }
}

void D3Helper::shiftClicked(bool isChecked) {
    qDebug() << QObject::sender()->objectName();
}

void D3Helper::delayChanged(QString delayString) {
    qDebug() << QObject::sender()->objectName();
}

void D3Helper::buttonChosen(int i) {
    qDebug() << QObject::sender()->objectName();
}
