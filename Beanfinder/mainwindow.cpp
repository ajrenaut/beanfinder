#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Widgets\loginscreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap backgroundMap("D:/Programming Projects/Beanfinder/Application/Beanfinder/assets/background");
    const int backgroundWidth{ ui->background->width() };
    const int backgroundHeight{ ui->background->height() };
    ui->background->setPixmap( backgroundMap.scaled( backgroundWidth, backgroundHeight, Qt::KeepAspectRatio ) );

    auto loginScreen{ new LoginScreen( this ) };
    loginScreen->move( 0, 0 );
    loginScreen->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
