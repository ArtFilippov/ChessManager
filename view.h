#ifndef VIEW_H
#define VIEW_H

#include "player.h"
#include "line.h"

#include <QWidget>
#include <memory>
#include <vector>

class IView
{
public:
    typedef std::shared_ptr<IView> ptr;

    virtual ~IView() = default;
    virtual void show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>>&) = 0;
    virtual void show_standings(std::vector<std::pair<Player::ptr, float>>&, int round, int total_rounds) = 0;
    virtual void start_adding_players() = 0;
    virtual void add_regline() = 0;
    virtual void remove_line(Player::ptr) = 0;
    virtual void restart(std::vector<Player::ptr>&) = 0;
    virtual QWidget* widget() = 0;
};

class View : public QWidget, public IView
{
    Q_OBJECT

    std::vector<Line::ptr> lines{};
    QVBoxLayout* layout;
    QWidget *controller_;
public:
    View(QWidget *controller, std::string instruction);
    void show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>>&) override;
    void show_standings(std::vector<std::pair<Player::ptr, float>>&, int round, int total_rounds) override;
    void start_adding_players() override;
    void restart(std::vector<Player::ptr>&) override;

    QWidget* widget() override;

private:
    void clear_rows();
    void show_adding_players();
    void align_lines();
public slots:
    void add_regline() override;
    void remove_line(Player::ptr) override;
    void set_lines_height(int from);
    void enter_person(Player::ptr);
};

#endif // VIEW_H
