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
