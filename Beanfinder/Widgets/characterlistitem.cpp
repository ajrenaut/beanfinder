#include "characterlistitem.h"
#include "ui_characterlistitem.h"

CharacterListItem::CharacterListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterListItem)
{
    ui->setupUi(this);

    connect(this, SIGNAL(sendRemoveItem(const QString &)), parent, SLOT(removeItem(const QString &)));
}

CharacterListItem::~CharacterListItem()
{
    delete ui;
}

void CharacterListItem::setName(const QString &text) {
    ui->labelName->setText(text);
}

void CharacterListItem::setRaceClass(const QString &text) {
    ui->labelRaceClass->setText(text);
}

void CharacterListItem::onToolButtonClicked()
{
    emit sendRemoveItem(ui->labelName->text());
}

QString CharacterListItem::getName() {
    return ui->labelName->text();
}

QString CharacterListItem::getRaceClass() {
    return ui->labelRaceClass->text();
}

QSize CharacterListItem::sizeHint() const {
    return QSize(300, 90);
}

QSize CharacterListItem::minimumSizeHint() const {
    return QSize(300, 90);
}
