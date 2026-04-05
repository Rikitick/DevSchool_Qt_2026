#include <QPushButton>
#include <QTimer>
#include <QPropertyAnimation>
#include <iostream>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    std::srand(std::time(nullptr));
    resize(300, 600);
    m_timer = new QTimer(this);
    int appearanceTime = 100 + (std::rand() % 900);
    connect(m_timer, &QTimer::timeout, this, [this, &appearanceTime](){
        QPushButton* btn = new QPushButton("*", this);
        btn->resize(40, 40);
        btn->show();

        int randX = std::rand() % (this->width() - btn->width());
        int randY = std::rand() % 100;
        int randDuration = 5000 + (std::rand() % 5000);

        QPropertyAnimation* anim = new QPropertyAnimation(btn, "pos", this);
        anim->setDuration(randDuration);
        anim->setStartValue(QPoint(randX, randY));
        anim->setEndValue(QPoint(randX, this->height()));
        connect(btn, &QPushButton::clicked, this, [btn, anim](){
            anim->stop();
            btn->deleteLater();
            anim->deleteLater();
        });
        connect(anim, &QPropertyAnimation::finished, this, [btn, anim, this](){
            this->setWindowTitle("you LOSE!!!");
            this->setStyleSheet("QMainWindow { background-color: red; }");
            btn->deleteLater();
            anim->deleteLater();
        });

        anim->start();
        appearanceTime = 100 + (std::rand() % 900);
        m_timer->start(appearanceTime);
    });
    m_timer->start(appearanceTime);
}

MainWindow::~MainWindow()
{
}
