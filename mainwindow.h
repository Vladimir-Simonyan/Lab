#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *elem[25][25];



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void Change();
    void Update();
    void Reset();
    void Demo();
    void Demo1();
    void Up();
    void Down();
    void Left();
    void Right();

    void keyPressEvent(QKeyEvent *event);
    void DemoStep();


    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
};

#endif // MAINWINDOW_H
