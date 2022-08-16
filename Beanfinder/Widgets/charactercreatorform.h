#ifndef CHARACTERCREATORFORM_H
#define CHARACTERCREATORFORM_H

#include <QWidget>
#include <vector>
#include <map>

namespace Ui {
class CharacterCreatorForm;
}

class CharacterCreatorForm : public QWidget
{
    Q_OBJECT

public:
    // Types
    enum class Faction
    {
        Alliance,
        Horde
    };

    enum class Race
    {
        Human,
        Dwarf,
        NightElf,
        Gnome,
        Draenei,
        Orc,
        Undead,
        Tauren,
        Troll,
        BloodElf
    };

    // The classes are ordered as they appear in the in-game
    // character creator, going left to right.
    enum class Class
    {
        Warrior,
        Paladin,
        Hunter,
        Rogue,
        Priest,
        DeathKnight,
        Shaman,
        Mage,
        Warlock,
        Druid
    };

    // Functions
    explicit CharacterCreatorForm(QWidget *parent = nullptr);
    ~CharacterCreatorForm();

    QSize buttonSizeHint() const;

public slots:
    void onCreateCharacterClicked();

    void onFactionClicked( Faction aFaction );

    void onRaceClicked( Race aRace );

private:
    // Types
    static constexpr int RACE_COUNT{ 5 };
    static constexpr int CLASS_COUNT{ 10 };
    // Functions
    void initMaps();

    //void resetPage();

    void updateRaceList( Faction aFaction );

    void updateClassList( Race aRace );

    std::vector<CharacterCreatorForm::Class> getAvailableClasses( Race aRace );

    // Variables
    Ui::CharacterCreatorForm *ui;

    std::map<Race, QString> raceMap;

    std::map<Class, QString> classMap;

private slots:
    void onBackButtonClicked();
};

#endif // CHARACTERCREATORFORM_H
