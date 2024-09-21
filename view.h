#ifndef VIEW_H
#define VIEW_H

#include "player.h"

#include <QWidget>
#include <memory>
#include <vector>

class IView
{
public:
    typedef std::shared_ptr<IView> ptr;

    virtual ~IView() = default;
    virtual void show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>>) = 0;
    virtual void show_standings(std::vector<std::pair<Player::ptr, float>>) = 0;
};

class View : public QWidget, public IView
{
    Q_OBJECT
public:
    View();
};

#endif // VIEW_H
