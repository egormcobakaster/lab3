#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Header.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString elem;
    Graph<int>* Seq;
private slots:
    void on_pushButton_clicked();




signals:
    void sendText(QString str);
public slots:
    void resirvedelem(QString str);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
