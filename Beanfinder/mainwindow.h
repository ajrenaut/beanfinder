#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Widgets\loginscreen.h"
#include "Widgets\mainmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *aParent = nullptr);
    ~MainWindow();

private:
    // Functions
    void showLoginScreen();

    void showMainMenu
        (
        const std::string& aCharacterName
        );

    // Variables
    Ui::MainWindow *ui;

    std::shared_ptr<LoginScreen> mLoginScreen;

    std::shared_ptr<MainMenu> mMainMenu;

private slots:
    void onLogIn( std::string aCharacterName );

    void onLogOut();

};
#endif // MAINWINDOW_H
