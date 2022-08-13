#ifndef CHARACTERCREATORFORM_H
#define CHARACTERCREATORFORM_H

#include <QWidget>

namespace Ui {
class CharacterCreatorForm;
}

class CharacterCreatorForm : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterCreatorForm(QWidget *parent = nullptr);
    ~CharacterCreatorForm();

private:
    Ui::CharacterCreatorForm *ui;
};

#endif // CHARACTERCREATORFORM_H
