#include "loginscreen.h"
#include "ui_loginscreen.h"

#include <QObject>
#include <QSqlQuery>

#include "databasemanager.h"
#include "Widgets\characterlistitem.h"
#include "Widgets\charactercreatorform.h"

LoginScreen::LoginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);

    QPixmap logoMap("D:/Programming Projects/Beanfinder/Application/Beanfinder/assets/logo");
    const int logoWidth{ ui->logo->width() };
    const int logoHeight{ ui->logo->height() };
    ui->logo->setPixmap( logoMap.scaled( logoWidth, logoHeight, Qt::KeepAspectRatio ) );

    connect(ui->characterList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(onCharacterListSelectionChanged(QListWidgetItem*, QListWidgetItem*)));

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
            this, &LoginScreen::onDeleteButtonClicked );

    connect(ui->exitButton, &QPushButton::clicked, this, &LoginScreen::onExitButtonClicked);

    connect( characterCreatorWidget, &CharacterCreatorForm::characterAdded, this, &LoginScreen::refreshCharacterList );
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::onCharacterListSelectionChanged(QListWidgetItem* current, QListWidgetItem* previous)
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

void LoginScreen::onExitButtonClicked()
{
    qApp->quit();
}

void LoginScreen::onDeleteButtonClicked()
{
    auto db{ DatabaseManager::getInstance() };
    db->deleteCharacter( selectedCharacter->getName().toStdString() );

    refreshCharacterList();
}

void LoginScreen::refreshCharacterList()
{
    auto db{ DatabaseManager::getInstance() };
    auto queryResults{ db->getCharacters() };

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
