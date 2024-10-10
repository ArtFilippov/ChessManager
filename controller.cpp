#include "controller.h"

#include <exception>
#include <iostream>

#include <QMessageBox>

Controller::Controller(QWidget *parent) : QWidget(parent), view(new View(this, "")), settings(new QHBoxLayout), system(new QComboBox(this)), total_rounds(new QComboBox(this)),
    buttons(new QHBoxLayout), viewport(new QScrollArea(this))
{
    system->addItem("Round");
    system->addItem("Swiss");

    total_rounds->addItem("auto");
    for (int i = 5; i <= 15; ++i) {
        total_rounds->addItem(QString::fromStdString(std::to_string(i)));
    }

    settings->addWidget(system);
    settings->addWidget(new QLabel("system"));
    settings->addWidget(total_rounds);
    settings->addWidget(new QLabel("rounds"));

    QPushButton *start = new QPushButton("start");
    connect(start, SIGNAL(clicked()), this, SLOT(new_tournament()));

    buttons->addWidget(start);

    viewport->setWidgetResizable(true);
    viewport->setWidget(view->widget());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(settings);
    layout->addWidget(viewport);
    layout->addLayout(buttons);

    this->setLayout(layout);
}


void Controller::new_tournament()
{
    tournament = make_tournament();

    QPushButton *done = new QPushButton("done", this);
    connect(done, SIGNAL(clicked()), this, SLOT(start_tournament()));
    auto *old = buttons->itemAt(0);

    buttons->replaceWidget(old->widget(), done);
    old->widget()->close();
    delete old;

    QPushButton *restart = new QPushButton("restart", this);
    connect(restart, SIGNAL(clicked()), this, SLOT(restart_tournament()));
    settings->addWidget(restart);

    view->start_adding_players();
}


void Controller::add_player(Player::ptr player)
{
    try {
        tournament->add_player(player);
    } catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
        QMessageBox::warning(0, "Incorrect Input", "There is already such a person");
        view->remove_line(player);
    }
}

void Controller::remove_player(Player::ptr player)
{
    tournament->remove_player(player);
}


void Controller::start_tournament()
{
    QPushButton *finish = new QPushButton("finish", this);
    connect(finish, SIGNAL(clicked()), this, SLOT(standings()));
    auto *old = buttons->itemAt(0);

    buttons->replaceWidget(old->widget(), finish);
    old->widget()->close();
    delete old;

    if (tournament->make_pairs())
    {
        auto *old = buttons->itemAt(0);
        old->widget()->hide();
    }
}

void Controller::standings()
{
    QPushButton *next = new QPushButton("next", this);
    connect(next, SIGNAL(clicked()), this, SLOT(start_tournament()));
    auto *old = buttons->itemAt(0);

    buttons->replaceWidget(old->widget(), next);
    old->widget()->close();
    delete old;

    tournament->standings();
}

void Controller::restart_tournament()
{
    std::vector<Player::ptr> players;
    tournament->get_players(players);

    tournament = make_tournament();

    QPushButton *done = new QPushButton("done", this);
    connect(done, SIGNAL(clicked()), this, SLOT(start_tournament()));
    auto *old = buttons->itemAt(0);

    buttons->replaceWidget(old->widget(), done);
    old->widget()->close();
    delete old;

    view->restart(players);
}

ChessTournament::ptr Controller::make_tournament()
{
    if (system->currentText() == "Swiss") {
        if (total_rounds->currentText() == "auto") {
            return ChessTournament::ptr(new SwissTournament(view));
        } else {
            return ChessTournament::ptr(new SwissTournament(view, std::stoi(total_rounds->currentText().toStdString())));
        }
    } else {
        total_rounds->setCurrentIndex(0);
        return ChessTournament::ptr(new RoundTournament(view));
    }
}
