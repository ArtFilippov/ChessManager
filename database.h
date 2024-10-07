#ifndef DATABASE_H
#define DATABASE_H

#include <boost/noncopyable.hpp>

#include <memory>
#include <optional>
#include <tuple>

#include <QtSql/QSqlDatabase>


class SQLite;

class Database : boost::noncopyable
{
protected:
    Database() = default;
public:
    typedef std::shared_ptr<Database> ptr;
    static ptr connect();
    virtual ~Database();

    virtual std::optional<std::tuple<int, std::string, int>> find_person(std::string name) = 0;
    virtual void add_preson(std::string name, int elo) = 0;
    virtual void add_game_result(std::string black, std::string white, float result_1, float result_2, int elo_1, int elo_2) = 0;
};

class SQLite : public Database, public std::enable_shared_from_this<SQLite>
{
    static std::weak_ptr<SQLite> instance;
    QSqlDatabase db;

    SQLite();
public:
    static std::shared_ptr<SQLite> create_connection();
    ~SQLite();

    std::optional<std::tuple<int, std::string, int>> find_person(std::string name) override;
    void add_preson(std::string name, int elo) override;
    void add_game_result(std::string white, std::string black, float result_1, float result_2, int elo_1, int elo_2) override;
};



#endif // DATABASE_H
