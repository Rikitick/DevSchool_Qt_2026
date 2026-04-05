#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    std::srand(std::time(nullptr));
    resize(300, 600);
    m_timer = std::make_unique<QTimer>(this);
    m_timer->start(fps);
    connect(m_timer.get(), &QTimer::timeout, this, [this](){
        for (auto it = buttons.begin(); it != buttons.end(); ) {
            auto &btn = it->first;
            int speed = it->second;
            btn->move(btn->x(), btn->y() + speed);
            if (btn->y() + btn->height() > height()) {
                setWindowTitle(QStringLiteral("you LOSE!!!"));
                setStyleSheet(QStringLiteral("QMainWindow { background-color: red; }"));
                btn->deleteLater();
                it = buttons.erase(it);
            }
            else
                ++it;
        }
        if (gameLoopTimer > appearanceTime) {
            gameLoopTimer = 0;
            appearanceTime = QRandomGenerator64::global()->bounded(minAppearanceInterval, maxAppearanceInterval);
            std::unique_ptr<QPushButton> btn = std::make_unique<QPushButton>("*", this);
            btn->resize(sizeButton, sizeButton);
            int randX = QRandomGenerator64::global()->bounded(width() - btn->width());
            int randY = QRandomGenerator64::global()->bounded(100);
            btn->move(randX, randY);
            connect(btn.get(), &QPushButton::clicked, this, [this, curBtn = btn.get()](){
                for (auto it = buttons.begin(); it != buttons.end(); ++it) {
                    if (it->first.get() == curBtn) {
                        it->first->deleteLater();
                        buttons.erase(it);
                        break;
                    }
                }
            });
            btn->show();
            int randSpeed = QRandomGenerator64::global()->bounded(minSpeed, maxSpeed);
            buttons.push_back(std::make_pair(std::move(btn), randSpeed));
        }
        gameLoopTimer += fps;
    });
}

MainWindow::~MainWindow()
{
}
