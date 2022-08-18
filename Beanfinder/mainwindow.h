#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "Widgets\characterlistitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *aParent = nullptr);
    ~MainWindow();

public slots:
    void onCharacterListSelectionChanged(QListWidgetItem* current, QListWidgetItem* previous);

private:
    Ui::MainWindow *ui;

    CharacterListItem* selectedCharacter;

private slots:
    void onExitButtonClicked();

    void onDeleteButtonClicked();

    void refreshCharacterList();
};
#endif // MAINWINDOW_H
