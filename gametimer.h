#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QElapsedTimer>
#include <QTimer>
#include <QString>

#include<cmath>

class GameTimer:public QObject
{
    Q_OBJECT
public:
    GameTimer(QObject *parent=nullptr, int autoStopCycle = 5000 ,qint16 updateCycle = 10);
    void start();
    void pause();
    void resume();
    void stop();
    void reset();

    bool isStarted(){return _isStarted;}
    bool isPaused(){return _isPaused;}

    qint64 getGameTime();
    qint64 getGameTimeSec(){
        return std::floor(getGameTime()/1000.0);
    }
    QString getGameTime_str();
    QString getGameTime_str2();

    void setRoundDirection(bool isFloor){_isRoundFloor = isFloor;}
public slots:
    void updateSlot(){
        emit update(getGameTime_str());
        emit update2(getGameTime_str2());
        if(_isRoundFloor){
            emit updateSec(QString::asprintf("%3d",(int)std::floor(getGameTime()/1000.0)));
        }else{
            emit updateSec(QString::asprintf("%3d",(int)std::ceil(getGameTime()/1000.0)));
        }
    };

    void autoStopSlot(){
        autoStopTimer->stop();
        this->stop();
        emit autoStop();
    }
signals:
    void update(QString str);
    void update2(QString str);
    void updateSec(QString str);
    void autoStop();

private:
    QElapsedTimer *gameTime;
    QElapsedTimer *pauseTime;
    qint64 pauseTimeSum;

    QTimer *updateTimer;
    QTimer *autoStopTimer;

    bool _isStarted;
    bool _isPaused;
    bool _isRoundFloor;

    qint16 updateCycle;
    int stopCycle;

};

#endif // GAMETIMER_H
