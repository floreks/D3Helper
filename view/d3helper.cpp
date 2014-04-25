#include "d3helper.h"
#include "ui_d3helper.h"

#include "controller/keyhelper.h"
#include <QVariant>
#include <QShortcut>
#include <QMouseEvent>

D3Helper::D3Helper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::D3Helper)
{
    ui->setupUi(this);
    this->setWindowTitle("D3Helper");
    this->setBaseSize(this->size());

    // Connect slots
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addButtonClicked()));
    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeButtonClicked()));
    connect(ui->enabledCheckBox,SIGNAL(clicked(bool)),this,SLOT(enabledClicked(bool)));
    QShortcut *cursorCheck = new QShortcut(QKeySequence("SHIFT+F1"),this);
    connect(cursorCheck,SIGNAL(activated()),this,SLOT(saveCursorPos()));

    initialize();

    if(GameWindow::setWindowName("Diablo III")) {
        ui->statusBar->showMessage("Diablo III window found.",3000);
    } else {
        ui->statusBar->showMessage("ERROR: No game window found.",3000);
    }
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
        if(obj->objectName().contains("enabledcheckbox",Qt::CaseInsensitive)) {
            QCheckBox *checkBox = qobject_cast<QCheckBox*>(obj);
            connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(enabledClicked(bool)));
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
    QComboBox *box = manager.getComboBoxAt(boxNr);
    QLineEdit *line = manager.getLineBoxAt(boxNr);
    QCheckBox *checkBox = manager.getShiftBoxAt(boxNr);

    if(isChecked) {
        Key key = box->currentData().value<Key>();
        int delay = line->text().toInt();

        actions.insert(boxNr,new Action(key,delay));
        actions.find(boxNr).value()->setShift(checkBox->isChecked());
        actions.find(boxNr).value()->start();

        box->setEnabled(false);
        line->setEnabled(false);
        checkBox->setEnabled(false);
    } else {
        box->setEnabled(true);
        line->setEnabled(true);
        checkBox->setEnabled(true);
        actions.find(boxNr).value()->setFinish(true);
        actions.remove(boxNr);
    }
}

void D3Helper::saveCursorPos() {
    GetCursorPos(&mousePos);
    ui->statusBar->showMessage("Mouse captured at X: " + QString::number(mousePos.x) + " Y: " + QString::number(mousePos.y));

    foreach(Action *action , actions) {
        action->setMousePos(mousePos);
    }
}
