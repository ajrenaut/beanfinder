#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QListWidgetItem>
#include <QWidget>

#include "Widgets\characterlistitem.h"

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = nullptr);
    ~LoginScreen();

signals:
    void selectCharacterClicked( std::string aCharacterName );

public slots:
    void onCharacterListSelectionChanged(QListWidgetItem* current, QListWidgetItem* previous);

private:
    Ui::LoginScreen *ui;

    CharacterListItem* selectedCharacter;

private slots:
    void onExitButtonClicked();

    void onDeleteButtonClicked();

    void refreshCharacterList();
};

#endif // LOGINSCREEN_H
