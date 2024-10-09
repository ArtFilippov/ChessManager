#include "view.h"

#include "linebutton.h"

#include <algorithm>
#include <format>

View::View(QWidget *controller, std::string instruction) : layout(new QVBoxLayout(this)), controller_(controller), server(new ServerView(this))
{
    lines.push_back(Line::ptr(new TextLine(this, instruction)));

    for (auto x : lines) {
        x->setFixedHeight(x->fontMetrics().lineSpacing() * 2.7);
        layout->addWidget(x->widget());
    }

    layout->addWidget(server->widget());
    layout->addSpacerItem(new QSpacerItem(0, 400, QSizePolicy::Expanding));

    this->setLayout(layout);
}

void View::start_adding_players()
{
    clear_rows();
    lines.push_back(Line::ptr(new RegLine(this, "name", "elo")));
    lines.push_back(Line::ptr(new RegLine(this)));
    show_adding_players();
}

void View::show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>> &pairs)
{
    server->show_pairs(pairs);

    clear_rows();

    lines.push_back(Line::ptr(new GameLine(this, "num", "Player name", "score", "score", "Player name")));
    ILineButton *line = new GameLineButton(controller_, this, lines.back());
    layout->insertWidget(0, line->widget());
    line->hide_button();

    for (size_t i = 0; i < pairs.size(); ++i) {
        lines.push_back(Line::ptr(new GameLine(this, i + 1, pairs[i].first, pairs[i].second)));
        ILineButton *line = new GameLineButton(controller_, this, lines.back());
        layout->insertWidget(i + 1, line->widget());
    }

    set_lines_height(0);
    align_lines();
}

void View::show_standings(std::vector<std::pair<Player::ptr, float>> &player_and_coeff, int round, int total_rounds)
{
    server->show_standings(player_and_coeff, round, total_rounds);

    clear_rows();

    lines.push_back(Line::ptr(new TextLine(this, std::format("Standings {}/{}", round, total_rounds))));
    lines.push_back(Line::ptr(new StandLine(this, "num", "name", "score", "coeff", "elo")));
    layout->insertWidget(0, lines[0]->widget());
    layout->insertWidget(1, lines[1]->widget());

    for (size_t i = 0; i < player_and_coeff.size(); ++i) {
        lines.push_back(Line::ptr(new StandLine(this, i + 1, player_and_coeff[i].first, player_and_coeff[i].second)));
        layout->insertWidget(i + 2, lines.back()->widget());
    }

    set_lines_height(0);
}

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
        ILineButton *line = new LineButton(controller_, this, lines[i]);
        layout->insertWidget(i, line->widget());

        if (i == 0) {
            line->hide_button();
        }
    }

    set_lines_height(0);
}

void View::restart(std::vector<Player::ptr>& players)
{
    start_adding_players();
    for (auto p : players) {
        enter_person(p);
    }
}

void View::enter_person(Player::ptr player)
{
    std::vector<std::string> fields;
    fields.push_back(player->get_name());
    fields.push_back(std::to_string(player->get_elo()));

    lines.back()->set_fields(fields);
    LineButton *button = dynamic_cast<LineButton*>(layout->itemAt(lines.size() - 1)->widget());
    button->click();
}

void View::add_regline()
{
    lines.push_back(Line::ptr(new RegLine(this)));
    QWidget *line = new LineButton(controller_, this, lines.back());
    layout->insertWidget(lines.size() - 1, line);

    set_lines_height(lines.size() - 1);
}

void View::remove_line(Player::ptr player)
{
    if (lines.size() < 2) {
        return;
    }

    for (size_t i = lines.size() - 2; i >= 0; --i) {
        if (lines[i]->off()->get_name() == player->get_name()) {
            auto wid = layout->takeAt(i);
            wid->widget()->close();
            delete wid;
            lines.erase(lines.begin() + i);
            return;
        }
    }
}

void View::set_lines_height(int from)
{
    for (size_t i = from; i < lines.size(); ++i) {
        lines[i]->setFixedHeight(lines[0]->fontMetrics().lineSpacing() * 2.7);
    }
}

void View::align_lines()
{
    std::vector<std::size_t> sizes;
    lines[0]->get_sizes(sizes);
    for (auto line : lines) {
        line->set_sizes(sizes);
    }
}

