#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QString>
#include <QDateTime>
#include <QElapsedTimer>
#include <QSoundEffect>
#include <QUrl>

#include "gametimer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_released();

    void on_continueButton_released();

    void on_stopButton_released();

    void setTimerText(QString str);

    void setTimerTextSecond(QString str);

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QSoundEffect *soundEffect;
    GameTimer *gameTimer;
    GameTimer *gameSecondTimer;
};
#endif // MAINWINDOW_H
