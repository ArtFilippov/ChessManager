#include "database.h"

#include <boost/algorithm/string.hpp>

#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

Database::ptr Database::connect()
{
    return SQLite::create_connection();
}

// SQLite

SQLite::SQLite() : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    db.setDatabaseName("ChessBase");
    if (!db.open()) {
        qDebug() << db.lastError();
        throw std::string("unable to connect to the database");
    }
}

SQLite::~SQLite()
{
    db.close();
}

std::shared_ptr<SQLite> SQLite::create_connection()
{
    static std::shared_ptr<SQLite> instance = std::shared_ptr<SQLite>(new SQLite);

    return instance;
}

std::optional<std::tuple<int, std::string, int>> SQLite::find_person(std::string name)
{
    boost::trim(name);

    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS Players (id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(255) NOT NULL UNIQUE, elo INT NOT NULL DEFAULT 1000)");
    if (!query.exec()) {
        qDebug() << query.lastError();
        throw std::string("can't get a table");
    }

    query.prepare("SELECT id, name, elo FROM Players where name = :name");
    query.bindValue(":name", QVariant(QString::fromStdString(name)));

    if (!query.exec()) {
        qDebug() << query.lastError();
        throw std::string("can't select from table");
    }

    if (query.first()) {
        int id = query.value(0).toInt();
        std::string actual_name = query.value(1).toString().toStdString();
        int actual_elo = query.value(2).toInt();

        return std::tuple{id, actual_name, actual_elo};
    } else {
        return {};
    }
}

void SQLite::add_preson(std::string name, int elo)
{
    boost::trim(name);

    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS Players (id INTEGER PRiMARY KEY AUTOINCREMENT, name VARCHAR(255) NOT NULL UNIQUE, elo INT NOT NULL DEFAULT 1000)");
    if (!query.exec()) {
        qDebug() << query.lastError();
        throw std::string("can't get a table");
    }

    query.prepare("INSERT INTO Players (name, elo) VALUES(?, ?)");
    query.addBindValue(QVariant(QString::fromStdString(name)));
    query.addBindValue(elo);

    if (!query.exec()) {
        qDebug() << query.lastError();
        throw std::string("can't insert into a Players");
    }
}

void SQLite::update_person(std::string name, int elo)
{
    auto person = find_person(name);
    if (person.has_value()) {
        auto [id, _1, _2] = person.value();

        QSqlQuery query(db);

        query.prepare("UPDATE Players SET elo = ? WHERE id = ?");
        query.addBindValue(elo);
        query.addBindValue(id);

        if (!query.exec()) {
            qDebug() << query.lastError();
            throw std::string("can't insert into a Players");
        }
    }
}
