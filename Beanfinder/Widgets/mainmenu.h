#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu( std::string aCharacterName, QWidget *parent = nullptr );
    ~MainMenu();

signals:
    void logout();

private:
    Ui::MainMenu *ui;

private slots:
};

#endif // MAINMENU_H
