#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap backgroundMap("D:/Programming Projects/Beanfinder/Application/Beanfinder/assets/background");
    QPixmap logoMap("D:/Programming Projects/Beanfinder/Application/Beanfinder/assets/logo");

    const int backgroundWidth{ ui->background->width() };
    const int backgroundHeight{ ui->background->height() };
    ui->background->setPixmap( backgroundMap.scaled( backgroundWidth, backgroundHeight, Qt::KeepAspectRatio ) );

    const int logoWidth{ ui->logo->width() };
    const int logoHeight{ ui->logo->height() };
    ui->logo->setPixmap( logoMap.scaled( logoWidth, logoHeight, Qt::KeepAspectRatio ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

