#include "characterlistitem.h"
#include "ui_characterlistitem.h"
#include <QApplication>

CharacterListItem::CharacterListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterListItem)
{
    ui->setupUi(this);

    connect( ui->buttonLogin, &QPushButton::clicked, this, &CharacterListItem::onSelectCharacterClicked );
}

CharacterListItem::~CharacterListItem()
{
    delete ui;
}

void CharacterListItem::setName(const QString &text)
{
    ui->labelName->setText(text);
}

void CharacterListItem::setRaceClass(const QString &text)
{
    ui->labelRaceClass->setText(text);
}

QString CharacterListItem::getName()
{
    return ui->labelName->text();
}

QString CharacterListItem::getRaceClass()
{
    return ui->labelRaceClass->text();
}

QSize CharacterListItem::sizeHint() const
{
    return QSize(320, 90);
}

QSize CharacterListItem::minimumSizeHint() const
{
    return QSize(320, 90);
}

void CharacterListItem::onFocusChanged( const bool aIsFocused )
{
    ui->buttonLogin->setVisible( aIsFocused );
}

void CharacterListItem::onSelectCharacterClicked()
{
    auto charName{ this->getName().toStdString() };
    emit selectCharacterClicked( charName );
}
