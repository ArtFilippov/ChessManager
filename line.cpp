#include "line.h"
#include <iostream>
#include <QMessageBox>

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
    if (data[0] == "") {
        return player;
    }

    if (data[1] == "") {
        player = Player::ptr(new Player(data[0]));
    } else {
        int elo = 0;

        try {
            elo = std::stoi(data[1]);
        } catch(std::invalid_argument e) {
            std::cerr << e.what() << std::endl;
            QMessageBox::warning(0, "Incorrect Input ", "the field \"elo\" must be an integer");
            return player;
        } catch (std::out_of_range e) {
            std::cerr << e.what() << std::endl;
            QMessageBox::warning(0, "Incorrect Input ", "too many characters in \"elo\"");
            return player;
        }

        player = Player::ptr(new Player(data[0], elo));
    }

    on_row();

    is_done = true;
    return player;
}

Player::ptr RegLine::off()
{
    return player;
}

void RegLine::on_row()
{
    auto elo_field = dynamic_cast<QTextEdit*>(row[1]);
    elo_field->setText(QString::fromStdString(std::to_string(player->get_elo())));
    Line::on_row();
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
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(player_2->get_name()))));
    layout->addWidget(row[0]);
    layout->addWidget(row[1]);
    layout->addWidget(row[2]);
    layout->addWidget(row[3]);

    this->setLayout(layout);
}

Player::ptr GameLine::on() try
{
    if (is_done) {
        return Player::ptr(nullptr);
    }

    std::vector<std::string> data = Line::get_data();

    if (data[0] == "" && data[1] == "") {
        return Player::ptr(nullptr);
    }

    float result_1, result_2;
    if (data[0] == "" ) {
        result_2 = std::stof(data[1]);
        result_1 = 1 - result_2;
    } else if (data[1] == "") {
        result_1 = std::stof(data[0]);
        result_2 = 1 - result_1;
    } else {
        result_1 = std::stof(data[0]);
        result_2 = std::stof(data[1]);
    }

    int elo_1 = player_1->get_elo();
    int elo_2 = player_2->get_elo();

    player_1->add_game_result(player_2, result_1, Player::WHITE);
    player_2->add_game_result(player_1, result_2, Player::BLACK);

    player_1->update_elo(elo_2, result_1);
    player_2->update_elo(elo_1, result_2);

    on_row();

    is_done = true;
    return player_1;

} catch(std::invalid_argument e) {
    std::cerr << e.what() << std::endl;
    QMessageBox::warning(0, "Incorrect Input", "the field must be a number");
    return Player::ptr(nullptr);
} catch (std::out_of_range e) {
    std::cerr << e.what() << std::endl;
    QMessageBox::warning(0, "Incorrect Input", "too many characters");
    return Player::ptr(nullptr);
}

Player::ptr GameLine::off()
{
    if (!is_done) {
        return Player::ptr(nullptr);
    }

    if (player_1 && player_2) {
        player_1->remove_game_result(player_2);
        player_2->remove_game_result(player_1);

        off_row();
        is_done = false;
    }

    return player_2;
}

void GameLine::on_row()
{
    auto result_1 = dynamic_cast<QTextEdit*>(row[1]);
    result_1->setText(QString::fromStdString(std::to_string(player_1->result_of_game_with(player_2))));

    auto result_2 = dynamic_cast<QTextEdit*>(row[2]);
    result_2->setText(QString::fromStdString(std::to_string(player_2->result_of_game_with(player_1))));

    Line::on_row();
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


// StandLine

StandLine::StandLine(QWidget *parent, std::string num, std::string name, std::string points, std::string coeff, std::string elo) : Line(parent), player(nullptr), is_done(1)
{
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(num))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(name))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(points))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(coeff))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(elo))));

    layout->addWidget(row[0]);
    layout->addWidget(row[1]);
    layout->addWidget(row[2]);
    layout->addWidget(row[3]);
    layout->addWidget(row[4]);

    this->setLayout(layout);
}

StandLine::StandLine(QWidget *parent, int num, Player::ptr p1, float coeff) : Line(parent), player(p1), is_done(1)
{
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(std::to_string(num)))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(player->get_name()))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(std::to_string(player->get_points())))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(std::to_string(coeff)))));
    row.push_back(dynamic_cast<QWidget*>(new QLabel(QString::fromStdString(std::to_string(player->get_elo())))));

    layout->addWidget(row[0]);
    layout->addWidget(row[1]);
    layout->addWidget(row[2]);
    layout->addWidget(row[3]);
    layout->addWidget(row[4]);

    this->setLayout(layout);
}

Player::ptr StandLine::on()
{
    return player;
}

Player::ptr StandLine::off()
{
    return player;
}

