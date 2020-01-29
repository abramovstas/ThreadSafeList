#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>

#include "myworker.h"
#include "listelement.h"
#include "threadsafelist.h"

namespace Ui {
class MainWindow;
}

class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void setInterval(int interval);

private slots:
    void updateModel();

    void on_sbox_interval_valueChanged(int arg1);

    void on_btn_add_clicked();

    void on_btn_edit_clicked();

    void on_btn_remove_clicked();

    void on_btn_exit_clicked();

    void on_sbox_count_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    ThreadSafeList m_list;
    QVector<QThread*> threads_vec;
    QStandardItemModel* model;
    ListElement *edited_element;
    void lockSelected();
    void addThread(int thread_index);
    void delThread();
};



#endif // MAINWINDOW_H
