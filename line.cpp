#include "line.h"

TextLine::TextLine(QWidget *parent, std::string s) : Line(parent)
{
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(s))));
    layout->addWidget(row[0]);
    this->setLayout(layout);
}

Player::ptr TextLine::on()
{
    return Player::ptr(nullptr);
}

Player::ptr TextLine::off()
{
    return Player::ptr(nullptr);
}


// RegLine
RegLine::RegLine(QWidget *parent) : Line(parent), is_done(0)
{
    row.push_back(dynamic_cast<QWidget*>(new QTextEdit));
    row.push_back(dynamic_cast<QWidget*>(new QTextEdit));
    layout->addWidget(row[0]);
    layout->addWidget(row[1]);
    this->setLayout(layout);
}

RegLine::RegLine(QWidget *parent, std::string s1, std::string s2) : Line(parent), is_done(1)
{
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(s1))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(s2))));
    layout->addWidget(row[0]);
    layout->addWidget(row[1]);
    this->setLayout(layout);
}

Player::ptr RegLine::on()
{
    if (is_done) {
        return player;
    }

    std::vector<std::string> data = Line::get_data();
    if (data[0] == "" || data[1] == "") {
        return player;
    }

    on_row();

    player = Player::ptr(new Player(data[0], std::stoi(data[1])));
    is_done = true;
    return player;
}

Player::ptr RegLine::off()
{
    return player;
}

// GameLine

GameLine::GameLine(QWidget *parent, std::string s1, std::string s2, std::string s3, std::string s4) : Line(parent), player_1(nullptr), player_2(nullptr), is_done(1)
{
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(s1))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(s2))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(s3))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(s4))));
    layout->addWidget(row[0]);
    layout->addWidget(row[1]);
    layout->addWidget(row[2]);
    layout->addWidget(row[3]);
    this->setLayout(layout);
}

GameLine::GameLine(QWidget *parent, Player::ptr p1, Player::ptr p2) : Line(parent), player_1(p1), player_2(p2), is_done(0)
{
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(player_1->get_name()))));
    row.push_back(dynamic_cast<QWidget*>(new QTextEdit));
    row.push_back(dynamic_cast<QWidget*>(new QTextEdit));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(player_1->get_name()))));
    layout->addWidget(row[0]);
    layout->addWidget(row[1]);
    layout->addWidget(row[2]);
    layout->addWidget(row[3]);
    this->setLayout(layout);
}

Player::ptr GameLine::on()
{
    if (is_done) {
        return player_1;
    }

    std::vector<std::string> data = Line::get_data();
    if (data[0] == "" || data[1] == "") {
        return player_1;
    }

    on_row();

    player_1->add_game_result(player_2, std::stoi(data[0]), Player::WHITE);
    player_2->add_game_result(player_1, std::stoi(data[1]), Player::BLACK);
    is_done = true;
    return player_1;
}

Player::ptr GameLine::off()
{
    if (!is_done) {
        return player_2;
    }

    if (player_1 && player_2) {
        player_1->remove_game_result(player_2);
        player_2->remove_game_result(player_1);

        off_row();
        is_done = false;
    }

    return player_2;
}

void GameLine::off_row()
{
    for (size_t i = 1; i < 3; ++i) {
        QWidget *new_widget = new QTextEdit;

        auto *old = layout->itemAt(i);
        layout->replaceWidget(old->widget(), new_widget);
        old->widget()->close();
        delete old;

        row[i] = new_widget;
    }
}
