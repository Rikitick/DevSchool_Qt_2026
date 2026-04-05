#include <QTimer>
#include <QPushButton>
#include <QPropertyAnimation>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    static constexpr int minAppearanceInterval = 100;
    static constexpr int maxAppearanceInterval = 1000;
    static constexpr int sizeButton = 40;
    static constexpr int fps = 1000 / 60;
    static int appearanceTime = 1000;
    static int gameLoopTimer = 0;

    std::srand(std::time(nullptr));
    resize(300, 600);
    m_timer = new QTimer(this);
    m_timer->start(fps);
    connect(m_timer, &QTimer::timeout, this, [this](){
        gameLoopTimer += fps;
        if (gameLoopTimer < appearanceTime)
            return;
        gameLoopTimer = 0;
        appearanceTime = minAppearanceInterval +
                         (std::rand() % (maxAppearanceInterval - minAppearanceInterval));
        QPushButton* btn = new QPushButton("*", this);
        btn->resize(sizeButton, sizeButton);
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
    });
}

MainWindow::~MainWindow()
{
}
