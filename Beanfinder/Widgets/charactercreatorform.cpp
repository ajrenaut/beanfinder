#include "charactercreatorform.h"
#include "ui_charactercreatorform.h"

#include <QDebug>

#include "databasemanager.h"

using namespace std;

CharacterCreatorForm::CharacterCreatorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterCreatorForm),
    currentRace{ Race::INVALID_RACE },
    currentClass{ Class::INVALID_CLASS }
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
    ui->allianceButton->click();

    connect(ui->doneButton, &QPushButton::clicked, this, &CharacterCreatorForm::onDoneButtonClicked);
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

        // TODO: There's no need to do this every time the class list is updated. Move this elsewhere.
        currentButton->disconnect();
        connect( currentButton, &QPushButton::clicked, [=] {
            emit onClassClicked( static_cast<Class>( i ) );
        });
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
        default:
            // Ignore all of our problems
            break;
    }

    return availableClasses;
}

void CharacterCreatorForm::onFactionClicked( Faction aFaction )
{
    updateRaceList( aFaction );
    if( aFaction == Faction::Alliance )
    {
        auto currentButton{ findChild<QPushButton*>(QString("hordeButton")) };
        currentButton->setChecked( false );
    }
    else
    {
        auto currentButton{ findChild<QPushButton*>(QString("allianceButton")) };
        currentButton->setChecked( false );
    }
}

void CharacterCreatorForm::onRaceClicked( Race aRace )
{
    currentRace = aRace;

    updateClassList( aRace );
    for(int i{ 0 }; i < RACE_COUNT; i++)
    {
        auto currentButton{ findChild<QPushButton*>(QString("race%1").arg(i)) };
        if( currentButton->text() != raceMap.find( aRace )->second )
        {
            currentButton->setChecked( false );
        }
    }
}

void CharacterCreatorForm::onClassClicked( Class aClass )
{
    currentClass = aClass;

    for(int i{ 0 }; i < CLASS_COUNT; i++)
    {
        auto currentButton{ findChild<QPushButton*>(QString("class%1").arg(i)) };
        if( currentButton->text() != classMap.find( aClass )->second )
        {
            currentButton->setChecked( false );
        }
    }
}

void CharacterCreatorForm::onDoneButtonClicked()
{
    // TODO: A helper function to condense the race / class translation would be nice.
    const auto characterName{ ui->characterName->displayText() };

    auto db{ DatabaseManager() };
    if( !db.addCharacter(characterName.toStdString(), raceMap.find(currentRace)->second.toStdString(), classMap.find(currentClass)->second.toStdString() ) )
    {
        qDebug() << "Failed to add character to DB!";
    }
    else
    {
        characterAdded();
    }
}
