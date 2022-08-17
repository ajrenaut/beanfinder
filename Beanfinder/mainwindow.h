#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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

private slots:
    void onExitButtonClicked();
};
#endif // MAINWINDOW_H
