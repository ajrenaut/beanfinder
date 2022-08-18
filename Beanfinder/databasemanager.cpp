#include "databasemanager.h"

#include <QDebug>
#include <QSqlQuery>

static std::shared_ptr<DatabaseManager> sInstance;

DatabaseManager::DatabaseManager()
{
    mDatabase = QSqlDatabase::addDatabase("QSQLITE" , "CONNECTION NAME");
    mDatabase.setDatabaseName("..\\Beanfinder\\data\\beanfinder_db.sqlite");
    if(!mDatabase.open())
    {
        qDebug() << "Cannot open DB!";
    }

    //init DB function
    QSqlQuery query(mDatabase);
    query.prepare
        (
        "CREATE TABLE IF NOT EXISTS CharacterTable ("
            "name TEXT NOT NULL UNIQUE PRIMARY KEY, "
            "race TEXT NOT NULL, "
            "class TEXT NOT NULL );"
        );
    query.exec();
}

std::shared_ptr<DatabaseManager> DatabaseManager::getInstance()
{
    if( sInstance == nullptr )
    {
        sInstance.reset( new DatabaseManager );
    }
    return sInstance;
}

bool DatabaseManager::addCharacter
    (
    const std::string& aName,
    const std::string& aRace,
    const std::string& aClass
    )
{
    bool success{ true };

    QSqlQuery query{ mDatabase };
    auto queryString{ QString( "INSERT INTO CharacterTable (name, race, class) VALUES (\"%1\", \"%2\", \"%3\");").arg(aName.c_str(), aRace.c_str(), aClass.c_str() ) };
    query.prepare( queryString );
    success = query.exec();

    return success;
}

bool DatabaseManager::deleteCharacter
    (
    const std::string& aName
    )
{
    bool success{ true };

    QSqlQuery query{ mDatabase };
    auto queryString{ QString( "DELETE FROM CharacterTable WHERE name = \"%1\"").arg( aName.c_str() ) };
    query.prepare( queryString );
    success = query.exec();

    return success;

}

QSqlQuery DatabaseManager::getCharacters()
{
    QSqlQuery query{ mDatabase };
    auto queryString{ QString( "SELECT * FROM CharacterTable" ) };
    query.prepare( queryString );
    query.exec();

    return query;
}
