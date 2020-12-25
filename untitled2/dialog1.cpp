#include "dialog1.h"
#include "ui_dialog1.h"
#include <QPixmap>

#include<chrono>
Dialog1::Dialog1(QWidget *parent,Graph<int>* Seq,int Size) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    size=Size;
    seq=Seq;

    ui->setupUi(this);
    QPixmap pix(":/resource/img/Leo.png");
    int w=ui->label->width();
    int h=ui->label->height();

    ui->label->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));




}

Dialog1::~Dialog1()
{
    delete ui;
}


void Dialog1::on_pushButton_clicked()
{
    QString str1;
    ArraySequence<Edge<int>*>* Ar =this->seq->Get(ui->Enter->text().toInt());
    for(int i=0;i<Ar->GetLength();i++)
    {
        str1=str1+" " + "{" + QString::number(Ar->Get(i)->to) + "(" + QString::number(Ar->Get(i)->wt) + ")" + "}";
    }
    this->ui->Out->setText(str1);

}

void Dialog1::on_pushButton_2_clicked()
{
    ArraySequence<int>* mas=new ArraySequence<int>(*this->seq->Dijkstra(this->ui->Dnum->text().toInt()));
    QString str1;
    for(int i=0;i<mas->GetLength();i++)
    {
        str1=str1+" " + "{" + QString::number(i) + "(" + QString::number(mas->Get(i)) + ")" + "}";
    }
    this->ui->Dij->setText(str1);

}

void Dialog1::on_pushButton_3_clicked()
{
    int res=this->seq->AllCyclic();
    QString str1=QString::number(res);
    this->ui->Cycle->setText(str1);
}

void Dialog1::on_pushButton_4_clicked()
{
    this->seq->tc();
}

void Dialog1::on_pushButton_5_clicked()
{
    Stack<int>* S=seq->topologicalSort();
    QString str;
    while(S->GetLength())
    {
        int k=S->Pop();
        str=str+" "+QString::number(k);
    }
    ui->TSort->setText(str);
}
