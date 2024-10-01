#include "view.h"

#include "linebutton.h"

#include <algorithm>

View::View(QWidget *controller, std::string instruction) : layout(new QVBoxLayout(this)), controller_(controller)
{
    lines.push_back(Line::ptr(new TextLine(this, instruction)));

    for (auto x : lines) {
        x->setFixedHeight(x->fontMetrics().lineSpacing() * 2.7);
        layout->addWidget(x->widget());
    }

    layout->addSpacerItem(new QSpacerItem(0, 500, QSizePolicy::Expanding));

    this->setLayout(layout);
}


void View::start_adding_players()
{
    clear_rows();
    lines.push_back(Line::ptr(new RegLine(this, "name", "elo")));
    lines.push_back(Line::ptr(new RegLine(this)));
    show_adding_players();
}

void View::show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>> pairs)
{
    clear_rows();
    QWidget *line = new GameLineButton(controller_, this, Line::ptr(new GameLine(this, "Player name", "score", "score", "Player name")));
    layout->insertWidget(0, line);
    for (size_t i = 0; i < pairs.size(); ++i) {
        QWidget *line = new GameLineButton(controller_, this, Line::ptr(new GameLine(this, pairs[i].first, pairs[i].second)));
        layout->insertWidget(i + 1, line);
    }
}
void View::show_standings(std::vector<std::pair<Player::ptr, float>>) {}

QWidget* View::widget()
{
    return dynamic_cast<QWidget*>(this);
}

void View::clear_rows()
{
    for (size_t i = 0; i < lines.size(); ++i) {
        auto wid = layout->takeAt(0);
        wid->widget()->close();
        delete wid;
    }

    lines.clear();
}

void View::show_adding_players()
{
    for (size_t i = 0; i < lines.size(); ++i) {
        QWidget *line = new LineButton(controller_, this, lines[i]);
        layout->insertWidget(i, line);
    }
}

void View::add_regline()
{
    lines.push_back(Line::ptr(new RegLine(this)));
    QWidget *line = new LineButton(controller_, this, lines.back());
    layout->insertWidget(lines.size() - 1, line);
}

void View::remove_line(Player::ptr player)
{
    if (lines.size() < 2) {
        return;
    }

    for (size_t i = lines.size() - 2; i >= 0; ++i) {
        if (lines[i]->off()->get_name() == player->get_name()) {
            auto wid = layout->takeAt(i);
            wid->widget()->close();
            delete wid;
            lines.erase(lines.begin() + i);
            return;
        }
    }
}
