#ifndef CHARACTERLISTITEM_H
#define CHARACTERLISTITEM_H

#include <QWidget>

namespace Ui {
class CharacterListItem;
}

class CharacterListItem : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterListItem(QWidget *parent = nullptr);
    ~CharacterListItem();

    QString getName();
    void setName(const QString& text);
    QString getRaceClass();
    void setRaceClass(const QString& text);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
     void sendRemoveItem(const QString& text);

private slots:
     void onToolButtonClicked();

private:
    Ui::CharacterListItem *ui;

};

#endif // CHARACTERLISTITEM_H
