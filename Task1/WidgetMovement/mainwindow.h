#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator64>
#include <vector>

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    static constexpr int minAppearanceInterval = 100;
    static constexpr int maxAppearanceInterval = 1000;
    static constexpr int minSpeed = 1;
    static constexpr int maxSpeed = 4;
    static constexpr int sizeButton = 40;
    static constexpr int fps = 1000 / 60;
    int appearanceTime = 1000;
    int gameLoopTimer = 0;
    std::vector<std::pair<std::unique_ptr<QPushButton>, int>> buttons;
    std::unique_ptr<QTimer> m_timer = nullptr;
};
#endif // MAINWINDOW_H
