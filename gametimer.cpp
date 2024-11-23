#include "gametimer.h"

GameTimer::GameTimer(QObject *parent, int autoStopCycle, qint16 updateCycle)
    :QObject(parent),updateCycle(updateCycle)
{
    _isStarted = false;
    _isPaused = false;

    gameTime = new QElapsedTimer();
    gameTime->invalidate();

    pauseTime = new QElapsedTimer();
    pauseTime->invalidate();

    pauseTimeSum = 0;

    updateTimer = new QTimer();
    autoStopTimer = new QTimer();
    stopCycle = autoStopCycle;
    // autoStopTimer->setInterval(autoStopCycle);
    connect(this->updateTimer,&QTimer::timeout,this,&GameTimer::updateSlot);
    connect(this->autoStopTimer,&QTimer::timeout,this,&GameTimer::autoStopSlot);
}

void GameTimer::start(){
    if(_isPaused){
        pauseTimeSum += pauseTime->elapsed();
        pauseTime->invalidate();
        _isPaused = false;
    }else{
        if(_isStarted){
            return;
        }
        gameTime->start();
    }
    _isStarted = true;

    if(updateCycle > 0){
        updateTimer->start(updateCycle);
    }
    autoStopTimer->start(stopCycle);
}

void GameTimer::pause(){
    if(_isPaused == false && _isStarted){
        pauseTime->start();
        _isPaused = true;
    }

    updateTimer->stop();
}

void GameTimer::resume(){
    if(_isPaused && _isStarted){
        pauseTimeSum += pauseTime->elapsed();
        pauseTime->invalidate();

        _isPaused = false;

        if(updateCycle > 0){
            updateTimer->start(updateCycle);
        }
    }
}

void GameTimer::stop(){
    _isStarted = false;
    _isPaused = false;

    gameTime->invalidate();
    pauseTime->invalidate();

    pauseTimeSum = 0;

    updateTimer->stop();
    autoStopTimer->stop();
}

void GameTimer::reset(){
    _isStarted = false;
    _isPaused = false;

    gameTime->invalidate();
    pauseTime->invalidate();

    pauseTimeSum = 0;

    updateTimer->stop();
    emit update(getGameTime_str());
    emit updateSec("0");
}

qint64 GameTimer::getGameTime(){
    if(_isStarted){
        return gameTime->elapsed()-pauseTimeSum;
    }
    return 0;
}

QString GameTimer::getGameTime_str(){
    qint64 elapsed = getGameTime();
    return QString::asprintf("%02d:%02d.%02d",(elapsed/1000/60),(elapsed/1000)%60, (elapsed%1000)/10);
}

QString GameTimer::getGameTime_str2(){
    qint64 elapsed = getGameTime();
    return QString::asprintf("%02d:%02d",(elapsed/1000/60),(elapsed/1000)%60);
}
