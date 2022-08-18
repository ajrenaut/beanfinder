#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
public:
    static std::shared_ptr<DatabaseManager> getInstance();

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
    DatabaseManager();

    QSqlDatabase mDatabase;
};

#endif // DATABASEMANAGER_H
