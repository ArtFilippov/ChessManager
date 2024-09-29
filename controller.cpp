#include "controller.h"

#include <exception>
#include <iostream>

Controller::Controller(QWidget *parent) : QWidget(parent), view(new View(this, "instruction")), settings(new QHBoxLayout), system(new QComboBox(this)), total_rounds(new QComboBox(this)),
    buttons(new QHBoxLayout), viewport(new QScrollArea(this))
{
    system->addItem("Swiss");
    system->addItem("Round");

    total_rounds->addItem("auto");

    settings->addWidget(system);
    settings->addWidget(new QLabel("system"));
    settings->addWidget(total_rounds);
    settings->addWidget(new QLabel("rounds"));

    QPushButton *start = new QPushButton("start");
    connect(start, SIGNAL(clicked()), this, SLOT(start_tournament()));
    buttons->addWidget(start);

    viewport->setWidgetResizable(true);
    viewport->setWidget(view->widget());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(settings);
    layout->addWidget(viewport);
    layout->addLayout(buttons);

    this->setLayout(layout);
}

void Controller::start_tournament()
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
