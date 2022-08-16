#include "charactercreatorform.h"
#include "ui_charactercreatorform.h"

using namespace std;

CharacterCreatorForm::CharacterCreatorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterCreatorForm)
{
    ui->setupUi(this);
    initMaps();
    connect(ui->backButton, &QPushButton::clicked, this, &CharacterCreatorForm::onBackButtonClicked);

    connect(ui->allianceButton, &QPushButton::clicked, [=] {
        emit onFactionClicked( Faction::Alliance );
    });
    connect(ui->hordeButton, &QPushButton::clicked, [=] {
        emit onFactionClicked( Faction::Horde );
    });
    ui->raceList->setFlow( QListView::LeftToRight );
    ui->raceList->setSpacing(2);
    updateRaceList( Faction::Alliance );

    ui->classList->setFlow( QListView::LeftToRight );
    ui->classList->setSpacing(2);
    ui->classList->setViewMode(QListView::IconMode);
}

CharacterCreatorForm::~CharacterCreatorForm()
{
    delete ui;
}

QSize CharacterCreatorForm::buttonSizeHint() const
{
    return QSize(90, 90);
}

void CharacterCreatorForm::initMaps()
{
    raceMap =
    {
        {Race::Human, QString("Human")},
        {Race::Dwarf, QString("Dwarf")},
        {Race::NightElf, QString("Night Elf")},
        {Race::Gnome, QString("Gnome")},
        {Race::Draenei, QString("Draenei")},
        {Race::Orc, QString("Orc")},
        {Race::Undead, QString("Undead")},
        {Race::Tauren, QString("Tauren")},
        {Race::Troll, QString("Troll")},
        {Race::BloodElf, QString("Blood Elf")}
    };

    classMap =
    {
        {Class::Warrior, QString("Warrior")},
        {Class::Paladin, QString("Paladin")},
        {Class::Hunter, QString("Hunter")},
        {Class::Rogue, QString("Rogue")},
        {Class::Priest, QString("Priest")},
        {Class::DeathKnight, QString("Death Knight")},
        {Class::Shaman, QString("Shaman")},
        {Class::Mage, QString("Mage")},
        {Class::Warlock, QString("Warlock")},
        {Class::Druid, QString("Druid")}
    };
}

void CharacterCreatorForm::onCreateCharacterClicked()
{
    // TODO: Will probably need to clear/reset the form.
    this->show();
}

void CharacterCreatorForm::onBackButtonClicked()
{
    // TODO: Will probably need to clear/reset the form.
    this->hide();
}

void CharacterCreatorForm::updateRaceList( Faction aFaction )
{
    ui->raceList->clear();
    int startRace{ aFaction == Faction::Alliance ? static_cast<int>(Race::Human) : static_cast<int>(Race::Orc) };
    for(int i{ startRace }; i < RACE_COUNT + startRace; i++)
    {
        auto listItem{ new QListWidgetItem() };
        auto button{ new QPushButton(this) };
        listItem->setSizeHint(buttonSizeHint());
        button->setObjectName(QString("raceButton%1").arg(i));
        button->setText(raceMap.find(static_cast<Race>(i))->second);
        ui->raceList->addItem(listItem);
        ui->raceList->setItemWidget(listItem, button);
        button->show();
        /*
        connect(button, &QPushButton::clicked, [=] {
            emit onRaceClicked( static_cast<Race>(i) );
        });*/
    }

    if( aFaction == Faction::Alliance )
    {
        updateClassList( Race::Human );
    }
    else
    {
        updateClassList( Race::Orc );
    }
}

void CharacterCreatorForm::updateClassList( Race aRace )
{
    ui->classList->clear();
    std::vector<Class> availableClasses = getAvailableClasses( aRace );
    for(int i{ 0 }; i < CLASS_COUNT; i++)
    {
        auto listItem{ new QListWidgetItem() };
        auto button{ new QPushButton(this) };
        listItem->setSizeHint(buttonSizeHint());
        button->setObjectName(QString("classButton%1").arg(i));
        button->setText(classMap.find(static_cast<Class>(i))->second);
        ui->classList->addItem(listItem);
        ui->classList->setItemWidget(listItem, button);
        button->show();

        if( std::find(availableClasses.begin(), availableClasses.end(), static_cast<Class>(i)) != availableClasses.end())
        {
            button->setEnabled( true );
        }
        else
        {
            button->setEnabled( false );
        }
        printf("button dimensions %d x %d", button->height(), button->width());
    }
}

std::vector<CharacterCreatorForm::Class> CharacterCreatorForm::getAvailableClasses( Race aRace )
{
    std::vector<CharacterCreatorForm::Class> availableClasses;

    // Death Knight is available to all races, we can add it first.
    availableClasses.emplace_back( Class::DeathKnight );

    // This looks bad but it gets the job done.
    switch( aRace )
    {
        // Alliance
        case Race::Human:
            availableClasses.emplace_back( Class::Mage );
            availableClasses.emplace_back( Class::Paladin );
            availableClasses.emplace_back( Class::Priest );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Warlock );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::NightElf:
            availableClasses.emplace_back( Class::Druid );
            availableClasses.emplace_back( Class::Hunter );
            availableClasses.emplace_back( Class::Priest );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::Gnome:
            availableClasses.emplace_back( Class::Mage );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Warlock );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::Dwarf:
            availableClasses.emplace_back( Class::Hunter );
            availableClasses.emplace_back( Class::Paladin );
            availableClasses.emplace_back( Class::Priest );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::Draenei:
            availableClasses.emplace_back( Class::Hunter );
            availableClasses.emplace_back( Class::Mage );
            availableClasses.emplace_back( Class::Paladin );
            availableClasses.emplace_back( Class::Priest );
            availableClasses.emplace_back( Class::Shaman );
            availableClasses.emplace_back( Class::Warrior );
            break;
        // Horde
        case Race::Orc:
            availableClasses.emplace_back( Class::Hunter );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Shaman );
            availableClasses.emplace_back( Class::Warlock );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::Troll:
            availableClasses.emplace_back( Class::Hunter );
            availableClasses.emplace_back( Class::Mage );
            availableClasses.emplace_back( Class::Priest );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Shaman );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::Undead:
            availableClasses.emplace_back( Class::Mage );
            availableClasses.emplace_back( Class::Priest );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Warlock );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::Tauren:
            availableClasses.emplace_back( Class::Druid );
            availableClasses.emplace_back( Class::Hunter );
            availableClasses.emplace_back( Class::Shaman );
            availableClasses.emplace_back( Class::Warrior );
            break;
        case Race::BloodElf:
            availableClasses.emplace_back( Class::Hunter );
            availableClasses.emplace_back( Class::Mage );
            availableClasses.emplace_back( Class::Paladin );
            availableClasses.emplace_back( Class::Priest );
            availableClasses.emplace_back( Class::Rogue );
            availableClasses.emplace_back( Class::Warlock );
            break;
    }

    return availableClasses;
}

void CharacterCreatorForm::onFactionClicked( Faction aFaction )
{
    updateRaceList( aFaction );
}

void CharacterCreatorForm::onRaceClicked( Race aRace )
{
    updateClassList( aRace );
}
