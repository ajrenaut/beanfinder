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

    onFactionClicked( Faction::Alliance );

    connect(ui->allianceButton, &QPushButton::clicked, [=] {
        emit onFactionClicked( Faction::Alliance );
    });
    connect(ui->hordeButton, &QPushButton::clicked, [=] {
        emit onFactionClicked( Faction::Horde );
    });
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
    int startRace{ aFaction == Faction::Alliance ? static_cast<int>(Race::Human) : static_cast<int>(Race::Orc) };
    for(int i{ 0 }; i < RACE_COUNT; i++)
    {
        auto currentButton{ findChild<QPushButton*>(QString("race%1").arg(i)) };
        currentButton->setText( raceMap.find( static_cast<Race>( i + startRace ) )->second );
        currentButton->disconnect();

        connect( currentButton, &QPushButton::clicked, [=] {
            emit onRaceClicked( static_cast<Race>( i + startRace ) );
        });
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
    std::vector<Class> availableClasses = getAvailableClasses( aRace );
    for(int i{ 0 }; i < CLASS_COUNT; i++)
    {
        auto currentButton{ findChild<QPushButton*>(QString("class%1").arg(i)) };
        currentButton->setText( classMap.find( static_cast<Class>( i ) )->second );
        currentButton->disconnect();

        if( std::find(availableClasses.begin(), availableClasses.end(), static_cast<Class>(i)) != availableClasses.end())
        {
            currentButton->setEnabled( true );
        }
        else
        {
            currentButton->setEnabled( false );
        }
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
