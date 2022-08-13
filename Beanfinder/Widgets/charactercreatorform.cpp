#include "charactercreatorform.h"
#include "ui_charactercreatorform.h"

CharacterCreatorForm::CharacterCreatorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterCreatorForm)
{
    ui->setupUi(this);
}

CharacterCreatorForm::~CharacterCreatorForm()
{
    delete ui;
}
