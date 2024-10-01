#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "chesstournament.h"
#include "view.h"
#include "player.h"

#include <QWidget>

class Controller : public QWidget
{
    Q_OBJECT

    ChessTournament::ptr tournament{nullptr};
    IView *view;

    QHBoxLayout *settings;
    QScrollArea *viewport;
    QHBoxLayout *buttons;

    QComboBox *system;
    QComboBox *total_rounds;

public:
    Controller(QWidget *parent);
public slots:
    void add_player(Player::ptr);
    void remove_player(Player::ptr);
    void new_tournament();
    void start_tournament();
    void standings();
};

#endif // CONTROLLER_H
