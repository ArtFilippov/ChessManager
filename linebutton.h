#ifndef LINEBUTTON_H
#define LINEBUTTON_H

#include "line.h"

#include <QWidget>

class ILineButton : public QWidget
{
    Q_OBJECT
protected:
    QPushButton *button;
    QHBoxLayout *layout;
    Line::ptr line_;
    enum {SIZE = 45};
public:
    ILineButton(Line::ptr line);
    virtual ~ILineButton() = default;
    QWidget* widget();
public slots:
    void hide_button();
    void show_button();
};

class LineButton : public ILineButton
{
    Q_OBJECT

    bool is_ok{1};
public:
    LineButton(QWidget *controller, QWidget *view, Line::ptr line);
signals:
    void click_on(Player::ptr);
    void click_off(Player::ptr);
public slots:
    void click();
};

class GameLineButton : public ILineButton
{
    Q_OBJECT

    bool is_ok{1};
public:
    GameLineButton(QWidget *controller, QWidget *view, Line::ptr line);
public slots:
    void click();
};

#endif // LINEBUTTON_H
