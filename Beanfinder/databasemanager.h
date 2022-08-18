#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
public:
    DatabaseManager();

    bool addCharacter
        (
        const std::string& aName,
        const std::string& aRace,
        const std::string& aClass
        );

    bool deleteCharacter
        (
        const std::string& aName
        );

    QSqlQuery getCharacters();

private:
    QSqlDatabase mDatabase;
};

#endif // DATABASEMANAGER_H
