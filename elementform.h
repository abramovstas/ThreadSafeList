#ifndef ELEMENTFORM_H
#define ELEMENTFORM_H

#include <QDialog>

#include "listelement.h"

namespace Ui {
class ElementForm;
}

class ElementForm : public QDialog
{
    Q_OBJECT

public:
    explicit ElementForm(ListElement *element, QDialog *parent = nullptr);
    ~ElementForm();

    ListElement *element() const { return m_element; }

private slots:
    void on_btn_close_clicked();

    void on_btn_save_clicked();

private:
    Ui::ElementForm *ui;
    ListElement *m_element;

};

#endif // ELEMENTFORM_H
