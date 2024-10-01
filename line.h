#ifndef REGLINE_H
#define REGLINE_H


#include "player.h"

#include <QtWidgets>

#include <vector>
#include <string>
#include <memory>

class Line : public QWidget
{
    Q_OBJECT
protected:
    std::vector<QWidget*> row{};
    QHBoxLayout* layout;
public:
    typedef std::shared_ptr<Line> ptr;
    Line(QWidget *parent) : QWidget(parent), layout(new QHBoxLayout(this)) {}

    void on_row()
    {
        for (std::size_t i = 0; i < row.size(); ++i) {
            if (QTextEdit *text = dynamic_cast<QTextEdit*>(row[i])) {
                QString data = text->toPlainText();
                QWidget *new_widget = new QLabel(data);

                auto *old = layout->itemAt(i);
                layout->replaceWidget(old->widget(), new_widget);
                old->widget()->close();
                delete old;
            }
        }

        layout->update();
    }

    virtual Player::ptr on() = 0;
    virtual Player::ptr off() = 0;

    virtual std::vector<std::size_t> get_sizes()
    {
        std::vector<std::size_t> res(row.size());
        for (std::size_t i = 0; i < row.size(); ++i) {
            res.push_back(row[i]->size().width());
        }

        return res;
    }

    virtual void set_sizes(std::vector<std::size_t> sizes)
    {
        for (std::size_t i = 0; i < row.size() && i < sizes.size(); ++i) {
            row[i]->setMinimumWidth(sizes[i]);
        }
    }

    std::vector<std::string> get_data()
    {
        std::vector<std::string> data;
        for (std::size_t i = 0; i < row.size(); ++i) {
            if (QTextEdit *text = dynamic_cast<QTextEdit*>(row[i])) {
                data.push_back(text->toPlainText().toStdString());
            }
        }

        return data;
    }

    QWidget* widget()
    {
        return dynamic_cast<QWidget*>(this);
    }
};

class TextLine : public Line
{
    Player::ptr player{nullptr};
public:
    TextLine(QWidget *parent, std::string s);

    Player::ptr on() override;
    Player::ptr off() override;
};

class RegLine : public Line
{
    bool is_done;
    Player::ptr player{nullptr};
public:
    RegLine(QWidget *parent);
    RegLine(QWidget *parent, std::string s1, std::string s2);

    Player::ptr on() override;
    Player::ptr off() override;
};

class GameLine : public Line
{
    bool is_done;
    Player::ptr player_1;
    Player::ptr player_2;
public:
    GameLine(QWidget *parent, std::string s1, std::string s2, std::string s3, std::string s4);
    GameLine(QWidget *parent, Player::ptr p1, Player::ptr p2);

    Player::ptr on() override;
    Player::ptr off() override;
private:
    void off_row();
};

#endif // REGLINE_H
