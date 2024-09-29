#ifndef LINEBUTTON_H
#define LINEBUTTON_H

#include "line.h"

#include <QWidget>

class LineButton : public QWidget
{
    Q_OBJECT

    bool is_ok{1};
    QPushButton *button;
    Line::ptr line_;

public:
    LineButton(QWidget *controller, QWidget *view, Line::ptr line);
signals:
    void click_on(Player::ptr);
    void click_off(Player::ptr);
public slots:
    void click();
};

#endif // LINEBUTTON_H
