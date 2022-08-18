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

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void onFocusChanged( const bool aIsFocused );

signals:
    void selectCharacterClicked( std::string aCharacterName );

private:
// Variables
    Ui::CharacterListItem *ui;

private slots:
    void onSelectCharacterClicked();

};

#endif // CHARACTERLISTITEM_H
