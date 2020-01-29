#include "elementform.h"
#include "ui_elementform.h"
#include <QDebug>

ElementForm::ElementForm(ListElement *element, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ElementForm),
    m_element(element)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);
    ui->cbox_classNames->addItems( QStringList{
                                       ListElement().className(),
                                       ListElement1().className(),
                                       ListElement2().className()
                                   });
    if (element) {
        if (element->className() == ListElement().className())
            ui->cbox_classNames->setCurrentIndex(0);
        if (element->className() == ListElement1().className())
            ui->cbox_classNames->setCurrentIndex(1);
        if (element->className() == ListElement2().className())
            ui->cbox_classNames->setCurrentIndex(2);

        ui->le_userData->setText(element->userData());
        ui->sbox_threadCounter->setValue(element->threadCounter());
    }
}

ElementForm::~ElementForm()
{
    delete ui;
}

void ElementForm::on_btn_close_clicked()
{
    this->reject();
}

void ElementForm::on_btn_save_clicked()
{
    if (!m_element) {
        switch (ui->cbox_classNames->currentIndex()) {
        case 0:
            m_element = new ListElement();
            break;
        case 1:
            m_element = new ListElement1();
            break;
        case 2:
            m_element = new ListElement2();
            break;
        }
    }
    if (m_element) {
        m_element->setUserData(ui->le_userData->text());
        m_element->setThreadCounter(ui->sbox_threadCounter->value());
    }
    this->accept();
}

