#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets\characterlistitem.h"
#include "Widgets\charactercreatorform.h"

#include "databasemanager.h"

#include <QObject>
#include <QSqlQuery>

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

    refreshCharacterList();

    auto characterCreatorWidget{ new CharacterCreatorForm( this ) };
    characterCreatorWidget->setObjectName("characterCreatorWidget");
    characterCreatorWidget->setAutoFillBackground( true );
    characterCreatorWidget->move(320, 110);
    characterCreatorWidget->hide();

    // Probably should connect this to the character creator widget instead of the main window.
    connect(ui->createCharacterButton, &QPushButton::clicked,
            characterCreatorWidget, &CharacterCreatorForm::onCreateCharacterClicked);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &MainWindow::onDeleteButtonClicked );

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);

    connect( characterCreatorWidget, &CharacterCreatorForm::characterAdded, this, &MainWindow::refreshCharacterList );
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
        selectedCharacter = qobject_cast<CharacterListItem*>( ui->characterList->itemWidget(current) );
        selectedCharacter->onFocusChanged( true );
    }
}

void MainWindow::onExitButtonClicked()
{
    qApp->quit();
}

void MainWindow::onDeleteButtonClicked()
{
    // TODO: Should more properly iterate through the QList.
    auto db{ DatabaseManager() };
    db.deleteCharacter( selectedCharacter->getName().toStdString() );

    refreshCharacterList();
}

void MainWindow::refreshCharacterList()
{
    auto db{ DatabaseManager() };
    auto queryResults{ db.getCharacters() };

    ui->characterList->clear();
    int i{ 0 };
    while( queryResults.next() )
    {
        auto listItem{ new QListWidgetItem() };
        auto characterWidget{ new CharacterListItem( ui->characterList ) };
        characterWidget->setName( queryResults.value( 0 ).toString() );
        characterWidget->setRaceClass( queryResults.value( 1 ).toString() + " " + queryResults.value( 2 ).toString() );
        characterWidget->onFocusChanged( false );
        characterWidget->setObjectName( QString( "character%1" ).arg( i ) );
        listItem->setSizeHint( characterWidget->sizeHint() );
        ui->characterList->addItem( listItem );
        ui->characterList->setItemWidget( listItem, characterWidget );
        i++;
    }
}
