#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi( this );

    QPixmap backgroundMap( "..\\Beanfinder\\assets\\background" );
    const int backgroundWidth{ ui->background->width() };
    const int backgroundHeight{ ui->background->height() };
    ui->background->setPixmap( backgroundMap.scaled( backgroundWidth, backgroundHeight, Qt::KeepAspectRatio ) );

    showLoginScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginScreen()
{
    if( mLoginScreen == nullptr )
    {
        mLoginScreen = std::make_shared<LoginScreen>( this );
        connect( mLoginScreen.get(), &LoginScreen::selectCharacterClicked, this, &MainWindow::onLogIn );
    }
    mLoginScreen->move( 0, 0 );
    mLoginScreen->show();
}

void MainWindow::showMainMenu
    (
    const std::string& aCharacterName
    )
{
    mLoginScreen->hide();
    mMainMenu.reset( new MainMenu( aCharacterName, this ) );
    connect( mMainMenu.get(), &MainMenu::logout, this, &MainWindow::onLogOut );
    mMainMenu->move( 0, 0 );
    mMainMenu->show();
}

void MainWindow::onLogIn( std::string aCharacterName )
{
    showMainMenu( aCharacterName );
}

void MainWindow::onLogOut()
{
    mMainMenu->hide();
    mLoginScreen->show();
}
