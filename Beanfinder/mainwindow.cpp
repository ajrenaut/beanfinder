#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets\characterlistitem.h"

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

    auto item1{ new QListWidgetItem() };
    auto widget1{ new CharacterListItem(this) };
    widget1->setName(QString("Beancounter"));
    widget1->setRaceClass(QString("Blood Elf Paladin"));
    item1->setSizeHint(widget1->sizeHint());
    ui->characterList->addItem(item1);
    ui->characterList->setItemWidget(item1, widget1);

    auto item2{ new QListWidgetItem() };
    auto widget2{ new CharacterListItem(this) };
    widget2->setName(QString("Beanpruner"));
    widget2->setRaceClass(QString("Tauren Druid"));
    item2->setSizeHint(widget2->sizeHint());
    ui->characterList->addItem(item2);
    ui->characterList->setItemWidget(item2, widget2);

    auto item3{ new QListWidgetItem() };
    auto widget3{ new CharacterListItem(this) };
    widget3->setName(QString("Zugmanuts"));
    widget3->setRaceClass(QString("Orc Warrior"));
    item3->setSizeHint(widget3->sizeHint());
    ui->characterList->addItem(item3);
    ui->characterList->setItemWidget(item3, widget3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

