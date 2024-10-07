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
    virtual ~Database() = default;

    virtual std::optional<std::tuple<int, std::string, int>> find_person(std::string name) = 0;
    virtual void add_preson(std::string name, int elo) = 0;
    virtual void update_person(std::string name, int elo) = 0;
};

class SQLite : public Database, public std::enable_shared_from_this<SQLite>
{
    QSqlDatabase db;

    SQLite();
public:
    static std::shared_ptr<SQLite> create_connection();
    ~SQLite();

    std::optional<std::tuple<int, std::string, int>> find_person(std::string name) override;
    void add_preson(std::string name, int elo) override;
    void update_person(std::string name, int elo) override;
};

#endif // DATABASE_H
