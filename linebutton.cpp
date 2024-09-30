#include "linebutton.h"


LineButton::LineButton(QWidget *controller, QWidget *view, Line::ptr line) : button(new QPushButton("+")), line_(line)
{
    button->setFixedSize(50, 50);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button);

    line_->setFixedHeight(line_->fontMetrics().lineSpacing() * 2.7);
    layout->addWidget(line_->widget());

    this->setLayout(layout);

    connect(button, &QPushButton::clicked, this, &LineButton::click, Qt::DirectConnection);
    connect(this, SIGNAL(click_on(Player::ptr)), controller, SLOT(add_player(Player::ptr)), Qt::DirectConnection);
    connect(this, SIGNAL(click_off(Player::ptr)), controller, SLOT(remove_player(Player::ptr)), Qt::DirectConnection);
    connect(this, SIGNAL(click_on(Player::ptr)), view, SLOT(add_regline()), Qt::DirectConnection);
    connect(this, SIGNAL(click_off(Player::ptr)), view, SLOT(remove_line(Player::ptr)), Qt::DirectConnection);
}

void LineButton::click()
{
    Player::ptr player;
    if (is_ok && line_->on()) {
        is_ok = 0;
        button->setText("-");
        emit click_on(line_->on());
    } else if (!is_ok && line_->off()) {
        is_ok = 1;
        button->setText("+");
        emit click_off(line_->off());
    }
}
