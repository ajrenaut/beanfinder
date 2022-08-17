#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets\characterlistitem.h"
#include "Widgets\charactercreatorform.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap backgroundMap("D:/Programming Projects/Beanfinder/Application/Beanfinder/assets/background");
    QPixmap logoMap("D:/Programming Projects/Beanfinder/Application/Beanfinder/assets/logo");

    // TODO: Update this to new connection syntax.
    connect(ui->characterList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(onCharacterListSelectionChanged(QListWidgetItem*, QListWidgetItem*)));

    const int backgroundWidth{ ui->background->width() };
    const int backgroundHeight{ ui->background->height() };
    ui->background->setPixmap( backgroundMap.scaled( backgroundWidth, backgroundHeight, Qt::KeepAspectRatio ) );

    const int logoWidth{ ui->logo->width() };
    const int logoHeight{ ui->logo->height() };
    ui->logo->setPixmap( logoMap.scaled( logoWidth, logoHeight, Qt::KeepAspectRatio ) );

    auto item1{ new QListWidgetItem() };
    auto widget1{ new CharacterListItem(ui->characterList) };
    widget1->setName(QString("Beancounter"));
    widget1->setRaceClass(QString("Blood Elf Paladin"));
    widget1->onFocusChanged( false );
    item1->setSizeHint(widget1->sizeHint());
    ui->characterList->addItem(item1);
    ui->characterList->setItemWidget(item1, widget1);

    auto item2{ new QListWidgetItem() };
    auto widget2{ new CharacterListItem(ui->characterList) };
    widget2->setName(QString("Beanpruner"));
    widget2->setRaceClass(QString("Tauren Druid"));
    widget2->onFocusChanged( false );
    item2->setSizeHint(widget2->sizeHint());
    ui->characterList->addItem(item2);
    ui->characterList->setItemWidget(item2, widget2);

    auto item3{ new QListWidgetItem() };
    auto widget3{ new CharacterListItem(ui->characterList) };
    widget3->onFocusChanged( false );
    widget3->setName(QString("Zugmanuts"));
    widget3->setRaceClass(QString("Orc Warrior"));
    item3->setSizeHint(widget3->sizeHint());
    ui->characterList->addItem(item3);
    ui->characterList->setItemWidget(item3, widget3);

    auto characterCreatorWidget{ new CharacterCreatorForm( this ) };
    characterCreatorWidget->setObjectName("characterCreatorWidget");
    characterCreatorWidget->setAutoFillBackground( true );
    characterCreatorWidget->move(320, 110);
    characterCreatorWidget->hide();

    // Probably should connect this to the character creator widget instead of the main window.
    connect(ui->createCharacterButton, &QPushButton::clicked,
            characterCreatorWidget, &CharacterCreatorForm::onCreateCharacterClicked);

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCharacterListSelectionChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    // Would like to get the selected button to hide if the list is unselected.
    if( previous && qobject_cast<CharacterListItem*>(ui->characterList->itemWidget(previous)) )
    {
        qobject_cast<CharacterListItem*>(ui->characterList->itemWidget(previous))->onFocusChanged( false );
    }
    if( current && qobject_cast<CharacterListItem*>(ui->characterList->itemWidget(current)) )
    {
        qobject_cast<CharacterListItem*>(ui->characterList->itemWidget(current))->onFocusChanged( true );
    }
}

void MainWindow::onExitButtonClicked()
{
    qApp->quit();
}
