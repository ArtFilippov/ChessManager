#include "mainwindow.h"

#include "controller.h"

#include <QApplication>
#include <exception>
#include <QException>
#include <iostream>

int main(int argc, char *argv[]) try
{
    QApplication a(argc, argv);
    MainWindow w;

    Controller *control = new Controller(&w);

    QHBoxLayout *h_layout = new QHBoxLayout;
    h_layout->addWidget(control);

    QWidget *central_widget = new QWidget(&w);
    central_widget->setLayout(h_layout);

    w.setCentralWidget(central_widget);

    w.show();
    return a.exec();
} catch (std::exception e) {
    std::cerr << e.what() << std::endl;
}
