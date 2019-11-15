//   Copyright 2019 | Vladimir Simonyan | simonyan.vlad@gmail.com   // 



#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"


const int N = 25, M = 25;
int player_i, player_j;
short lab[N][M];
int start_i, start_j, finish_i, finish_j;

//==========[Bot]===========
short int steps[5555][5];
int step_n = 1;
bool araj = true;
int step(int* tvac);
int shrjakayq[4];
//==========[/Bot]===========

//==========[Stack]===========
short int stack[5555][6];
int stack_tmp[6];
int top = 0;
void Push(int* u);
int* Pop();
//==========[/Stack]==========

void LabStexcum();
void LabAncum();
bool flag = false;
bool demo = false;
bool demo1 = true;
int demoSpeed = 0;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
          elem[i][j] = new QWidget(this);
          elem[i][j]->setGeometry(5+j*23,90+i*23,22,22);
        }
    }


    ui->setupUi(this);


    tmr = new QTimer;
    tmr->setInterval(250);
    connect(tmr, SIGNAL(timeout()), this, SLOT(DemoStep()));
    tmr->start();

    LabStexcum();
    LabAncum();
    MainWindow::Reset();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_8 || event->key() == Qt::Key_W) {MainWindow::Up();}
    else if(event->key() == Qt::Key_2 || event->key() == Qt::Key_S) {MainWindow::Down();}
    else if(event->key() == Qt::Key_6 || event->key() == Qt::Key_D) {MainWindow::Right();}
    else if(event->key() == Qt::Key_4 || event->key() == Qt::Key_A) {MainWindow::Left();}
    else if(event->key() == Qt::Key_0) {MainWindow::Demo1();}
    QMainWindow::keyPressEvent(event);
}


void MainWindow::on_pushButton_2_clicked()
{
    MainWindow::Change();
}

void MainWindow::on_pushButton_3_clicked()
{
    MainWindow::Reset();
}

void MainWindow::on_pushButton_4_clicked()
{
    MainWindow::Demo();
}

void MainWindow::on_pushButton_5_clicked()
{
    MainWindow::Up();
}

void MainWindow::on_pushButton_7_clicked()
{
    MainWindow::Down();
}

void MainWindow::on_pushButton_6_clicked()
{
    MainWindow::Left();
}

void MainWindow::on_pushButton_8_clicked()
{
    MainWindow::Right();
}

void MainWindow::on_pushButton_clicked()
{
    flag = !flag;
    MainWindow::Update();
}

void MainWindow::on_pushButton_9_clicked()
{
    MainWindow::Demo1();
}

void MainWindow::on_pushButton_10_clicked()
{
    demoSpeed = (demoSpeed+1)%3;
    if(demoSpeed == 0) { tmr->setInterval(250); }
    else if(demoSpeed == 1) { tmr->setInterval(500); }
    else if(demoSpeed == 2) { tmr->setInterval(750); }
}

//vachagan
void MainWindow::Change() {
    LabStexcum();
    LabAncum();
    MainWindow::Reset();
}

void MainWindow::Reset() {
    player_i = start_i;
    player_j = start_j;
    MainWindow::Update();
}

void MainWindow::DemoStep() {
    if (demo) { MainWindow::Demo1(); }
}

void MainWindow::Demo() {
    demo = !demo;
}

void MainWindow::Demo1() {
    //==========[Steki naxapatrastum]==========
    if(demo1) {
        for (int i = 0; i < 5555; i++) {
            for (int j = 0; j < 4; j++)
                steps[i][j] = 1;
            steps[i][4] = -1;
        }
        demo1 = false;
    }
    //==========[/Steki naxapatrastum]=========

    shrjakayq[0] = (lab[player_i + 1][player_j] == 0 || lab[player_i + 1][player_j] == 2) ? 1 : 0;                              // ↓
    shrjakayq[1] = (lab[player_i][player_j - 1] == 0 || lab[player_i][player_j - 1] == 2) ? 1 : 0;                              // ←
    shrjakayq[2] = ((lab[player_i - 1][player_j] == 0 || lab[player_i - 1][player_j] == 2) && player_i-1 != start_i) ? 1 : 0;	// ↑
    shrjakayq[3] = (lab[player_i][player_j + 1] == 0 || lab[player_i][player_j + 1] == 2) ? 1 : 0;                              // →

    int rt = step(shrjakayq);
    if (rt == 0) { player_i++; }
    else if (rt == 1) { player_j--; }
    else if (rt == 2) { player_i--; }
    else if (rt == 3) { player_j++; }
    MainWindow::Update();
}

void MainWindow::Up() {
    if(demo){ MainWindow::Demo(); }
    if (lab[player_i-1][player_j] == 0 || lab[player_i-1][player_j] == 2) {
        player_i--;
        MainWindow::Update();
    }
}

void MainWindow::Down() {
    if(demo){ MainWindow::Demo(); }
    if (lab[player_i+1][player_j] == 0 || lab[player_i+1][player_j] == 2) {
        player_i++;
        MainWindow::Update();
    }
}

void MainWindow::Left() {
    if(demo){ MainWindow::Demo(); }
    if (lab[player_i][player_j-1] == 0 || lab[player_i][player_j-1] == 2) {
        player_j--;
        MainWindow::Update();
    }
}

void MainWindow::Right() {
    if(demo){ MainWindow::Demo(); }
    if (lab[player_i][player_j+1] == 0 || lab[player_i][player_j+1] == 2) {
        player_j++;
        MainWindow::Update();
    }
}

void MainWindow::Update() {
    if (player_i == finish_i && player_j == finish_j) {
        //demo = false;             // Hajordin ancneluc Demo-n anjatel
        MainWindow::Change();
    } else {
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if(lab[i][j] == 0) {
                    elem[i][j]->setStyleSheet("background-color:lightgray;");
                }
                else if (lab[i][j] == 1) {
                    elem[i][j]->setStyleSheet("background-color:black;");
                }
                else if (lab[i][j] == 2) {
                    if(flag) elem[i][j]->setStyleSheet("background-color:lightgreen;");
                    else elem[i][j]->setStyleSheet("background-color:lightgray;");
                }
                if (i == player_i && j == player_j) {elem[i][j]->setStyleSheet("background-color:red;");}
                if (i == finish_i && j == finish_j) {elem[i][j]->setStyleSheet("background-color:green;");}
            }
        }
    } 
}
//vachagan

void LabStexcum() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lab[i][j] = 1;

    lab[1][1] = 0;
    int x = 1, y = 1;
    int qayl[4] = { 1, 0, 0, 1 };			// 1 0 0 1
    long int rd;
    int mul = 1;
    while (true) {
        rd = (rand()+mul++) % 4;
        if (qayl[rd] == 1) {
            int sum = 0;
            if (rd == 0) {						// ↓
                for (int i = 1; i <= 3; i++) {
                    if (x - 1 < 0 || x + 1 > M - 1 || y + i > N - 1) {
                        sum = 0;
                        break;
                    }
                    sum += lab[y + i][x - 1];
                    sum += lab[y + i][x];
                    sum += lab[y + i][x + 1];
                }
                if (sum == 9) {
                    lab[y + 1][x] = 0;
                    lab[y + 2][x] = 0;

                    stack_tmp[0] = x;
                    stack_tmp[1] = y;
                    y += 2;
                    stack_tmp[2] = qayl[0];
                    stack_tmp[3] = qayl[1];
                    stack_tmp[4] = qayl[2];
                    stack_tmp[5] = qayl[3];
                    Push(stack_tmp);
                    qayl[0] = 1;
                    qayl[1] = 1;
                    qayl[2] = 0;
                    qayl[3] = 1;
                }
                else {
                    sum = 0;
                    for (int i = 1; i <= 2; i++) {
                        if (x - 1 < 0 || x + 1 > M - 1 || y + i > N - 1) {
                            sum = 0;
                            break;
                        }
                        sum += lab[y + i][x - 1];
                        sum += lab[y + i][x];
                        sum += lab[y + i][x + 1];
                    }
                    if (sum == 6) {
                        lab[y + 1][x] = 0;

                        stack_tmp[0] = x;
                        stack_tmp[1] = y;
                        y += 1;
                        stack_tmp[2] = qayl[0];
                        stack_tmp[3] = qayl[1];
                        stack_tmp[4] = qayl[2];
                        stack_tmp[5] = qayl[3];
                        Push(stack_tmp);
                        qayl[0] = 1;
                        qayl[1] = 1;
                        qayl[2] = 0;
                        qayl[3] = 1;
                    }
                    else qayl[rd] = 0;
                }
                sum = 0;
            }
            else if (rd == 1) {					// ←
                for (int i = 1; i <= 3; i++) {
                    if (y - 1 < 0 || y + 1 > N - 1 || x - i < 0) {
                        sum = 0;
                        break;
                    }

                    sum += lab[y - 1][x - i];
                    sum += lab[y][x - i];
                    sum += lab[y + 1][x - i];
                }
                if (sum == 9) {
                    lab[y][x - 1] = 0;
                    lab[y][x - 2] = 0;

                    stack_tmp[0] = x;
                    stack_tmp[1] = y;
                    x -= 2;
                    stack_tmp[2] = qayl[0];
                    stack_tmp[3] = qayl[1];
                    stack_tmp[4] = qayl[2];
                    stack_tmp[5] = qayl[3];
                    Push(stack_tmp);
                    qayl[0] = 1;
                    qayl[1] = 1;
                    qayl[2] = 1;
                    qayl[3] = 0;
                }
                else {
                    sum = 0;
                    for (int i = 1; i <= 2; i++) {
                        if (y - 1 < 0 || y + 1 > N - 1 || x - i < 0) {
                            sum = 0;
                            break;
                        }
                        sum += lab[y - 1][x - i];
                        sum += lab[y][x - i];
                        sum += lab[y + 1][x - i];
                    }
                    if (sum == 6) {
                        lab[y][x - 1] = 0;

                        stack_tmp[0] = x;
                        stack_tmp[1] = y;
                        x -= 1;
                        stack_tmp[2] = qayl[0];
                        stack_tmp[3] = qayl[1];
                        stack_tmp[4] = qayl[2];
                        stack_tmp[5] = qayl[3];
                        Push(stack_tmp);
                        qayl[0] = 1;
                        qayl[1] = 1;
                        qayl[2] = 1;
                        qayl[3] = 0;
                    }
                    else qayl[rd] = 0;
                }
                sum = 0;
            }
            else if (rd == 2) {					// ↑
                for (int i = 1; i <= 3; i++) {
                    if (x - 1 < 0 || x + 1 > M - 1 || y - i < 0) {
                        sum = 0;
                        break;
                    }
                    sum += lab[y - i][x - 1];
                    sum += lab[y - i][x];
                    sum += lab[y - i][x + 1];
                }
                if (sum == 9) {
                    lab[y - 1][x] = 0;
                    lab[y - 2][x] = 0;

                    stack_tmp[0] = x;
                    stack_tmp[1] = y;
                    y -= 2;
                    stack_tmp[2] = qayl[0];
                    stack_tmp[3] = qayl[1];
                    stack_tmp[4] = qayl[2];
                    stack_tmp[5] = qayl[3];
                    Push(stack_tmp);
                    qayl[0] = 0;
                    qayl[1] = 1;
                    qayl[2] = 1;
                    qayl[3] = 1;
                }
                else {
                    sum = 0;
                    for (int i = 1; i <= 2; i++) {
                        if (x - 1 < 0 || x + 1 > M - 1 || y - i < 0) {
                            sum = 0;
                            break;
                        }
                        sum += lab[y - i][x - 1];
                        sum += lab[y - i][x];
                        sum += lab[y - i][x + 1];
                    }
                    if (sum == 6) {
                        lab[y - 1][x] = 0;

                        stack_tmp[0] = x;
                        stack_tmp[1] = y;
                        y -= 1;
                        stack_tmp[2] = qayl[0];
                        stack_tmp[3] = qayl[1];
                        stack_tmp[4] = qayl[2];
                        stack_tmp[5] = qayl[3];
                        Push(stack_tmp);
                        qayl[0] = 0;
                        qayl[1] = 1;
                        qayl[2] = 1;
                        qayl[3] = 1;
                    }
                    else qayl[rd] = 0;
                }
                sum = 0;
            }
            else if (rd == 3) {					// →
                for (int i = 1; i <= 3; i++) {
                    if (y - 1 < 0 || y + 1 > N - 1 || x + i > M - 1) {
                        sum = 0;
                        break;
                    }
                    sum += lab[y - 1][x + i];
                    sum += lab[y][x + i];
                    sum += lab[y + 1][x + i];
                }
                if (sum == 9) {
                    lab[y][x + 1] = 0;
                    lab[y][x + 2] = 0;

                    stack_tmp[0] = x;
                    stack_tmp[1] = y;
                    x += 2;
                    stack_tmp[2] = qayl[0];
                    stack_tmp[3] = qayl[1];
                    stack_tmp[4] = qayl[2];
                    stack_tmp[5] = qayl[3];
                    Push(stack_tmp);
                    qayl[0] = 1;
                    qayl[1] = 0;
                    qayl[2] = 1;
                    qayl[3] = 1;
                }
                else {
                    sum = 0;
                    for (int i = 1; i <= 2; i++) {
                        if (y - 1 < 0 || y + 1 > N - 1 || x + i > M - 1) {
                            sum = 0;
                            break;
                        }
                        sum += lab[y - 1][x + i];
                        sum += lab[y][x + i];
                        sum += lab[y + 1][x + i];
                    }
                    if (sum == 6) {
                        lab[y][x + 1] = 0;

                        stack_tmp[0] = x;
                        stack_tmp[1] = y;
                        x += 1;
                        stack_tmp[2] = qayl[0];
                        stack_tmp[3] = qayl[1];
                        stack_tmp[4] = qayl[2];
                        stack_tmp[5] = qayl[3];
                        Push(stack_tmp);
                        qayl[0] = 1;
                        qayl[1] = 0;
                        qayl[2] = 1;
                        qayl[3] = 1;
                    }
                    else qayl[rd] = 0;
                }
                sum = 0;
            }
        }
        else if (qayl[0] + qayl[1] + qayl[2] + qayl[3] == 0){
            int* tmp = Pop();
            x = tmp[0];
            y = tmp[1];
            for (int i = 0; i < 4; i++)
                qayl[i] = tmp[i + 2];
            if (x == 1 && y == 1) break;
        }
    }



    start_i = 0;
    while (true) {
        int tj = rand() % M - 1;
        if (lab[start_i + 1][tj] == 0) {
            start_j = tj;
            break;
        }
    }
    finish_i = N - 1;
    while (true) {
        int tj = rand() % M - 1;
        if (lab[finish_i - 1][tj] == 0) {
            finish_j = tj;
            break;
        }
    }
    lab[start_i][start_j] = 2;
    lab[finish_i][finish_j] = 2;
}


void LabAncum() {
    //==========[Steki naxapatrastum]==========
    for (int i = 0; i < 5555; i++) {
        for (int j = 0; j < 4; j++)
            steps[i][j] = 1;
        steps[i][4] = -1;
    }
    //==========[/Steki naxapatrastum]=========

    int shrjakayq[4] = { 1, 0, 0, 0 };
    int i = start_i, j = start_j;
    while (true) {
        int rt = step(shrjakayq);
        if (araj) { lab[i][j] = 2; }
        else { lab[i][j] = 0;}
        if (rt == 0) { i++; }
        else if (rt == 1) { j--; }
        else if (rt == 2) { i--; }
        else if (rt == 3) { j++; }
        else if (rt == -1) {  break; }
        if (i == finish_i && j == finish_j) { break; }
        shrjakayq[0] = (lab[i + 1][j] == 0 || lab[i + 1][j] == 2) ? 1 : 0;		// ↓
        shrjakayq[1] = (lab[i][j - 1] == 0 || lab[i][j - 1] == 2) ? 1 : 0;		// ←
        shrjakayq[2] = (lab[i - 1][j] == 0 || lab[i - 1][j] == 2) ? 1 : 0;		// ↑
        shrjakayq[3] = (lab[i][j + 1] == 0 || lab[i][j + 1] == 2) ? 1 : 0;		// →
    }
}


void Push(int* u) {
    for (int i = 0; i < 6; i++)
        stack[top][i] = u[i];
    top++;
}


int* Pop() {
    top--;
    for (int i = 0; i < 6; i++)
        stack_tmp[i] = stack[top][i];
    return stack_tmp;
}


int step(int* tvac) {
    int tmp[5];
    for (int i = 0; i < 4; i++)
        tmp[i] = steps[step_n][i];
    tmp[4] = steps[step_n - 1][4];

    if (tvac[0] * tmp[0] && tmp[4] != 2) {			// ↓
        tmp[0] = 0;
        tmp[4] = 0;
        for (int i = 0; i < 5; i++)
            steps[step_n][i] = tmp[i];
        step_n++;
        araj = true;
        return tmp[4];
    }
    else if (tvac[1] * tmp[1] && tmp[4] != 3) {		// ←
        tmp[1] = 0;
        tmp[4] = 1;
        for (int i = 0; i < 5; i++)
            steps[step_n][i] = tmp[i];
        step_n++;
        araj = true;
        return tmp[4];
    }
    else if (tvac[2] * tmp[2] && tmp[4] != 0) {		// ↑
        tmp[2] = 0;
        tmp[4] = 2;
        for (int i = 0; i < 5; i++)
            steps[step_n][i] = tmp[i];
        step_n++;
        araj = true;
        return tmp[4];
    }
    else if (tvac[3] * tmp[3] && tmp[4] != 1) {		// →
        tmp[3] = 0;
        tmp[4] = 3;
        for (int i = 0; i < 5; i++)
            steps[step_n][i] = tmp[i];
        step_n++;
        araj = true;
        return tmp[4];
    }
    else {											// ↨
        steps[step_n][0] = 1;
        steps[step_n][1] = 1;
        steps[step_n][2] = 1;
        steps[step_n][3] = 1;
        steps[step_n][4] = -1;
        step_n--;
        araj = false;
        if (tmp[4] < 0) {
            step_n = 1;
            return tmp[4];
        }
        return (tmp[4] + 2) % 4;
    }
}
