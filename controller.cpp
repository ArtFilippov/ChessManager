#include "controller.h"


#include <exception>
#include <iostream>

Controller::Controller(QWidget *parent) : QWidget(parent), view(new View(this, "instruction")), settings(new QHBoxLayout), system(new QComboBox(this)), total_rounds(new QComboBox(this)),
    buttons(new QHBoxLayout), viewport(new QScrollArea(this))
{
    system->addItem("Swiss");
    system->addItem("Round");

    total_rounds->addItem("auto");
    total_rounds->addItem("8");

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
    if (system->currentText() == "Swiss") {
        if (total_rounds->currentText() == "auto") {
            tournament = ChessTournament::ptr(new SwissTournament(view));
        } else {
            tournament = ChessTournament::ptr(new SwissTournament(view, std::stoi(total_rounds->currentText().toStdString())));
        }
    } else if (system->currentText() == "Round") {
        tournament = ChessTournament::ptr(new RoundTournament(view));
    }

    QPushButton *done = new QPushButton("done", this);
    connect(done, SIGNAL(clicked()), this, SLOT(start_tournament()));
    auto *old = buttons->itemAt(0);

    buttons->replaceWidget(old->widget(), done);
    old->widget()->close();
    delete old;

    view->start_adding_players();
}


void Controller::add_player(Player::ptr player)
{
    try {
        tournament->add_player(player);
    } catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
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

    tournament->make_pairs();
}

void Controller::standings()
{

}
