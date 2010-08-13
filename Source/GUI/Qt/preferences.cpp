#include "preferences.h"
#include "_Automated/ui_preferences.h"
#include <QtGui/QLabel>
#include "views.h"

Preferences::Preferences(QSettings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    this->settings=settings;
    ui->setupUi(this);
    ui->treeWidget->setColumnHidden(1,true);
    ui->treeWidget->expandAll();

    for(int v=VIEW_EASY;v<NB_VIEW;v++) {
        ui->comboBox_defaultview->addItem(nameView((ViewMode)v),v);
    }

    ui->showMenu->setChecked(settings->value("showMenu",true).toBool());
    ui->showToolbar->setChecked(settings->value("showToolbar",true).toBool());
    ui->closeAllBeforeOpen->setChecked(settings->value("closeBeforeOpen",true).toBool());
    ui->comboBox_defaultview->setCurrentIndex(settings->value("defaultView",VIEW_EASY).toInt());
    ui->checkForNewVersion->setChecked(settings->value("checkForNewVersion",true).toBool());
    ui->rememberToolBarPosition->setChecked(settings->value("rememberToolBarPosition",true).toBool());
    ui->rememberGeometry->setChecked(settings->value("rememberGeometry",false).toBool());

    QObject::connect(ui->showToolbar,SIGNAL(toggled(bool)),ui->rememberToolBarPosition,SLOT(setEnabled(bool)));
    QObject::connect(ui->showToolbar,SIGNAL(toggled(bool)),ui->showMenu,SLOT(setEnabled(bool)));
    QObject::connect(ui->showMenu,SIGNAL(toggled(bool)),ui->showToolbar,SLOT(setEnabled(bool)));
    QObject::connect(ui->showMenu,SIGNAL(toggled(bool)),ui->rememberToolBarPosition,SLOT(setEnabled(bool)));
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::saveSettings() {
    settings->setValue("showMenu",ui->showMenu->isChecked());
    settings->setValue("showToolbar",ui->showToolbar->isChecked());
    settings->setValue("closeBeforeOpen",ui->closeAllBeforeOpen->isChecked());
    settings->setValue("checkForNewVersion",ui->checkForNewVersion->isChecked());
    settings->setValue("defaultView",ui->comboBox_defaultview->currentIndex());
    settings->setValue("rememberToolBarPosition",ui->rememberToolBarPosition->isChecked());
    settings->setValue("rememberGeometry",ui->rememberGeometry->isChecked());
}

void Preferences::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Preferences::on_treeWidget_itemSelectionChanged()
{
    if(!ui->treeWidget->selectedItems().first()->data(1,Qt::DisplayRole).isNull())
        ui->stackedWidget->setCurrentIndex(ui->treeWidget->selectedItems().first()->data(1,Qt::DisplayRole).toInt());
}

void Preferences::on_showToolbar_toggled(bool checked)
{
}

void Preferences::on_showMenu_toggled(bool checked)
{
}

void Preferences::on_showToolbar_pressed()
{
}
