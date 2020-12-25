#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"
#include <QDialog>
#include "Header.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    int size;

    Graph<int>* seq;
    explicit Dialog(QWidget *parent = nullptr,Graph<int>* Seq= nullptr, int Size= 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public slots:
    void resirvedText(QString str);
public:

    QString elem;
private:
    Ui::Dialog *ui;
signals:
    void sendText(QString str);
};

#endif // DIALOG_H
