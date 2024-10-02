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

    virtual void set_fields(std::vector<std::string> &data)
    {
        size_t j = 0;
        for (std::size_t i = 0; i < row.size() && j < data.size(); ++i) {
            if (QTextEdit *text = dynamic_cast<QTextEdit*>(row[i])) {
                text->setText(QString::fromStdString(data[j++]));
            }
        }

        layout->update();
    }

    virtual void get_sizes(std::vector<std::size_t> &res)
    {
        res.clear();
        for (std::size_t i = 0; i < row.size(); ++i) {
            res.push_back(row[i]->size().width());
        }
    }

    virtual void set_sizes(std::vector<std::size_t> &sizes)
    {
        for (std::size_t i = 0; i < row.size() && i < sizes.size(); ++i) {
            layout->setStretch(i, sizes[i]);
        }

        layout->update();
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

class StandLine : public Line
{
    bool is_done;
    Player::ptr player;
public:
    StandLine(QWidget *parent, std::string num, std::string name, std::string points, std::string coeff, std::string elo);
    StandLine(QWidget *parent, int num, Player::ptr p1, float coeff);

    Player::ptr on() override;
    Player::ptr off() override;
private:
    void off_row();
};

#endif // REGLINE_H
