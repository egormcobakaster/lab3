#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "dialog1.h"
Dialog::Dialog(QWidget *parent, Graph<int>* Seq, int Size) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    size=Size;
    seq=Seq;
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::resirvedText(QString str)
{
    ui->resirvedText->setText(str);
}




void Dialog::on_pushButton_clicked()
{
    if (size>seq->E())
    {
        Edge<int>* e=new Edge<int>(ui->from->text().toInt(),ui->to->text().toInt(),ui->Wt->text().toInt());
        seq->insert(e);

    }
    ui->from->setText(" ");
    ui->to->setText(" ");
    ui->Wt->setText(" ");
    ui->resirvedText->setText(QString::number(this->size-seq->E()));

}

void Dialog::on_pushButton_2_clicked()
{
    hide();
    Dialog1 *fm = new Dialog1(this,seq,seq->E());
    fm->show();
}
