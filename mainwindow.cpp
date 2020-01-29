#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>

#include "listelement.h"
#include "elementform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QStandardItemModel),
    edited_element(nullptr)
{
    ui->setupUi(this);

    for (int var = 0; var <= 5; ++var)
            on_sbox_count_valueChanged(var);

    connect(&m_list, &ThreadSafeList::dataChanged, this, &MainWindow::updateModel);

    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    foreach (const auto &thread, threads_vec) {
        thread->quit();
        thread->wait();
    }
    delete model;
    delete ui;
}

void MainWindow::updateModel()
{
    model->clear();
    foreach (ListElement* item, m_list.list_pull())
        //  Имя класса + Текст пользователя + Данные потока
        model->appendRow(new QStandardItem(item->className() + " " +
                                           item->userData() + " " +
                                           QString::number(item->threadCounter())));

    m_list.list_push();
}

void MainWindow::on_sbox_interval_valueChanged(int arg1)
{
    emit setInterval(arg1);
}

void MainWindow::on_btn_add_clicked()
{
    ListElement *element = nullptr;
    ElementForm *form = new ElementForm(element);
    if (form->exec() == QDialog::Accepted && form->element()) {
        m_list.append(form->element());
        updateModel();
    }
    form->close();
}

void MainWindow::on_btn_edit_clicked()
{
    lockSelected();

    if (edited_element) {
        ElementForm *form = new ElementForm(edited_element);
        if (form->exec() == QDialog::Accepted && form->element()) {
            m_list.push(form->element());
            edited_element = nullptr;
            updateModel();
        }
    }
}

void MainWindow::on_btn_remove_clicked()
{
    lockSelected();

    if (edited_element) {
        m_list.removeOne(edited_element);
        m_list.push(edited_element);
        edited_element = nullptr;
        updateModel();
    }
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}

void MainWindow::on_sbox_count_valueChanged(int arg1)
{
    if (threads_vec.size() == arg1)
        return ;

    if (threads_vec.size() < arg1)
        addThread(arg1);
    else delThread();
}

void MainWindow::lockSelected()
{
    QList<ListElement *> list = m_list.list_pull();
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if (index.isValid()) {
        ListElement *element = list.at(index.row());
        if (element) {
            edited_element = element;
            m_list.lockElement(element);
        }
    }
    m_list.list_push();
}

void MainWindow::addThread(int thread_index)
{
    if (thread_index > 0) {
        QThread *thread = new QThread;
        threads_vec.append(thread);
        MyWorker *worker = new MyWorker(ui->sbox_interval->value(), &m_list);
        worker->moveToThread(thread);
        QObject::connect(thread, SIGNAL(started()), worker, SLOT(slotDoWork()));
        connect(this, &MainWindow::setInterval, worker, &MyWorker::setInterval);
        thread->start();
    }
    return ;
}

void MainWindow::delThread()
{
    if (!threads_vec.empty()) {
        QThread *thread = threads_vec.last();
        thread->quit();
        thread->wait();
        threads_vec.removeLast();
    }
}
