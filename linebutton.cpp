#include "linebutton.h"

ILineButton::ILineButton(Line::ptr line) : button(new QPushButton("+")), line_(line)
{
    button->setFixedSize(SIZE, SIZE);

    layout = new QHBoxLayout;
    layout->addWidget(button);

    layout->addWidget(line_->widget());

    this->setLayout(layout);
}

void ILineButton::hide_button()
{
    layout->takeAt(0);
    layout->insertSpacing(0, button->size().width());
    button->hide();
}

void ILineButton::show_button()
{
    layout->takeAt(0);
    layout->insertWidget(0, button);
    button->hide();
}

QWidget* ILineButton::widget()
{
    return dynamic_cast<QWidget*>(this);
}


// LineButton
LineButton::LineButton(QWidget *controller, QWidget *view, Line::ptr line) : ILineButton(line)
{
    connect(button, &QPushButton::clicked, this, &LineButton::click, Qt::DirectConnection);
    connect(this, SIGNAL(click_on(Player::ptr)), controller, SLOT(add_player(Player::ptr)), Qt::DirectConnection);
    connect(this, SIGNAL(click_off(Player::ptr)), controller, SLOT(remove_player(Player::ptr)), Qt::DirectConnection);
    connect(this, SIGNAL(click_on(Player::ptr)), view, SLOT(add_regline()), Qt::DirectConnection);
    connect(this, SIGNAL(click_off(Player::ptr)), view, SLOT(remove_line(Player::ptr)), Qt::DirectConnection);
}

void LineButton::click()
{
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

// GameLineButton
GameLineButton::GameLineButton(QWidget *controller, QWidget *view, Line::ptr line) : ILineButton(line)
{
    connect(button, &QPushButton::clicked, this, &GameLineButton::click, Qt::DirectConnection);
}

void GameLineButton::click()
{
    if (is_ok && line_->on()) {
        is_ok = 0;
        button->setText("-");
    } else if (!is_ok && line_->off()) {
        is_ok = 1;
        button->setText("+");
    }
}

