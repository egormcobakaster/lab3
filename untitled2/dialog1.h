#ifndef DIALOG1_H
#define DIALOG1_H
#include "Header.h"
#include <QDialog>
#include"Sorter.h"
namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    int size;
    Graph<int>* seq;
    explicit Dialog1(QWidget *parent = nullptr, Graph<int>* Seq=nullptr, int Size=0);
    ~Dialog1();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Dialog1 *ui;
};

#endif // DIALOG1_H
