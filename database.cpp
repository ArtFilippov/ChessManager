#include "database.h"

#include <boost/algorithm/string.hpp>

#include <QtSql/QSqlQuery>
#include <QVariant>

Database::ptr Database::connect()
{
    return SQLite::create_connection();
}

// SQLite
std::weak_ptr<SQLite> SQLite::instance = std::shared_ptr<SQLite>(new SQLite)->weak_from_this();

SQLite::SQLite() : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    db.setDatabaseName("ChessBase");
    if (!db.open()) {
        throw std::string("unable to connect to the database");
    }
}

SQLite::~SQLite()
{
    db.close();
}

std::shared_ptr<SQLite> SQLite::create_connection()
{
    return SQLite::instance.lock();
}

std::optional<std::tuple<int, std::string, int>> SQLite::find_person(std::string name)
{
    boost::trim(name);

    QSqlQuery query(db);
    query.prepare("SELECT id, name, elo FROM Players where name = \":name\"");
    query.bindValue(":name", QVariant(QString::fromStdString(name)));

    if (!query.exec()) {
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
    query.prepare("CREATE TABLE IF NOT EXISTS Players (id INT PTYMARY KEY, name VARCHAR(255) NOT NULL UNIQUE, elo INT NOT NULL DEFAULT 1000)");
    if (!query.exec()) {
        throw std::string("can't get a table");
    }

    query.prepare("INSERT INTO Players (id, name, elo) VALUES(NULL, :name, :elo)");
    query.bindValue(":name", QVariant(QString::fromStdString(name)));
    query.bindValue(":elo", elo);

    if (!query.exec()) {
        throw std::string("can't insert into a Players");
    }
}

void SQLite::add_game_result(std::string white, std::string black, float result_1, float result_2, int elo_1, int elo_2)
{
    if (is_repeated(white, black, result_1, result_2, elo_1, elo_2)) {
        return;
    }

    boost::trim(black);
    boost::trim(white);

    QSqlQuery query(db);

    auto black_person = find_person(black);
    if (!black_person.has_value()) {
        throw std::string("can't find the player black");
    }

    auto white_person = find_person(white);
    if (!black_person.has_value()) {
        throw std::string("can't find the player white");
    }

    query.prepare("CREATE TABLE IF NOT EXISTS Games (id INT PTYMARY KEY, white_id INT, white_elo INT, white_result FLOAT, "
                  "black_result FLOAT, black_elo INT, black_id INT, "
                  "FOREIGN KEY(white_id) REFERENCES Players(id), "
                  "FOREIGN KEY(black_id) REFERENCES Players(id))");
    if (!query.exec()) {
        throw std::string("can't get a table");
    }

    query.prepare("INSERT INTO Games (id, white_id, white_elo, white_result, black_result, black_elo, black_id) "
                  "VALUES(NULL, :white_id, :white_elo, :white_result, :black_result, :black_elo, :black_id)");

    {
        auto [white_id, _1, _2] = white_person.value();
        query.bindValue(":white_id", QVariant(white_id));
        query.bindValue(":white_elo", elo_1);
        query.bindValue(":white_result", result_1);
    }

    {
        auto [black_id, _1, _2] = black_person.value();
        query.bindValue(":black_id", QVariant(black_id));
        query.bindValue(":black_elo", elo_2);
        query.bindValue(":black_result", result_2);
    }

    if (!query.exec()) {
        throw std::string("can't insert into a Games");
    }
}

bool SQLite::is_repeated(std::string white, std::string black, float result_1, float result_2, int elo_1, int elo_2)
{
    boost::trim(black);
    boost::trim(white);

    QSqlQuery query(db);

    auto black_person = find_person(black);
    if (!black_person.has_value()) {
        throw std::string("can't find the player black");
    }

    auto white_person = find_person(white);
    if (!black_person.has_value()) {
        throw std::string("can't find the player white");
    }

    query.prepare("CREATE TABLE IF NOT EXISTS Games (id INT PTYMARY KEY, white_id INT, white_elo INT, white_result FLOAT, "
                  "black_result FLOAT, black_elo INT, black_id INT, "
                  "FOREIGN KEY(white_id) REFERENCES Players(id), "
                  "FOREIGN KEY(black_id) REFERENCES Players(id))");
    if (!query.exec()) {
        throw std::string("can't get a table");
    }

    query.prepare("SELECT id FROM Games WHERE"
                  "white_id = :white_id, white_elo = :white_elo, white_result = :white_result, "
                  "black_result = :black_result, black_elo = :black_elo, black_id = :black_id)");

    {
        auto [white_id, _1, _2] = white_person.value();
        query.bindValue(":white_id", QVariant(white_id));
        query.bindValue(":white_elo", elo_1);
        query.bindValue(":white_result", result_1);
    }

    {
        auto [black_id, _1, _2] = black_person.value();
        query.bindValue(":black_id", QVariant(black_id));
        query.bindValue(":black_elo", elo_2);
        query.bindValue(":black_result", result_2);
    }

    if (!query.exec()) {
        throw std::string("can't insert into a Games");
    }

    return query.first();
}
