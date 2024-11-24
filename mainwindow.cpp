#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameTimer = new GameTimer(this, (int)((60*3+0.5)*1000));
    gameSecondTimer = new GameTimer(this, (int)((60*2+0.5)*1000));

    connect(this->gameTimer, &GameTimer::update2, this, &MainWindow::setTimerText);
    connect(this->gameSecondTimer, &GameTimer::update2, this, &MainWindow::setTimerTextSecond);

    ui->label->setText("start");


    // soundEffect = new QSoundEffect(this);
    // soundEffect->setSource(QUrl("/home/ohya/ProjectQt/syougakusei_robo/tone_880hz_1000ms.mp3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_released()
{
    gameSecondTimer->stop();
    gameTimer->start();
    // soundEffect->play();
}


void MainWindow::on_continueButton_released()
{
    gameTimer->stop();
    gameSecondTimer->start();
}


void MainWindow::on_stopButton_released()
{
    gameTimer->stop();
    gameSecondTimer->stop();
    ui->label->setText("Timer Stoped");
    ui->timer->setText("00:00");
}

void MainWindow::setTimerText(QString str){
    ui->timer->setText(str);
    auto tt = QString::asprintf("%1d台目の時間だよ",(int)std::floor(gameTimer->getGameTimeSec()/60.0)+1);
    ui->label->setText(tt);
}

void MainWindow::setTimerTextSecond(QString str){
    ui->timer->setText(str);
    ui->label->setText("みんなでがんばろう");
}
