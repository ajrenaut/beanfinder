#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu( std::string aCharacterName, QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    ui->welcomeLabel->setText( QString( "Welcome %1!" ).arg( aCharacterName.c_str() ) );

    connect( ui->logoutButton, &QPushButton::clicked, this, &MainMenu::logout );
}

MainMenu::~MainMenu()
{
    delete ui;
}
