
#include "autoplotbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <cassert>

AutoPlotButton::AutoPlotButton(QWidget *parent)
    : QWidget{parent}
{
    this->setParent(parent);
}

AutoPlotButton::AutoPlotButton()
{

}

void AutoPlotButton::paintEvent(QPaintEvent* ev)
{
    //Initializing painter to draw auto plot button
    QPainter painter(this);
    QColor bordercol(21, 21, 21, 255);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(bordercol, 0.1));

    //Depends on status it differently draws the button
    if(this->status == AutoPlotButton::on)
    {
        //Adding background color and drawing button
        painter.setBrush(QColor(this->OnBgCol));
        painter.drawRoundedRect(QRectF(25, 10, 40, 20), 10, 10);

        //Adding main color and drawing slider
        painter.setBrush(QColor(this->OnCol));
        painter.drawEllipse(QRectF(48, 11, 18, 18));
    }

    else
    {
        painter.setBrush(QColor(this->OffBgCol));
        painter.drawRoundedRect(QRectF(25, 10, 40, 20), 10, 10);

        painter.setBrush(QColor(this->OffCol));
        painter.drawEllipse(QRectF(27, 11, 18, 18));
    }

}

QSize AutoPlotButton::sizeHint() const
{
    return QSize(50, 20);
}

void AutoPlotButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(this->status == AutoPlotButton::on) this->status = AutoPlotButton::off;
        else this->status = AutoPlotButton::on;

        repaint();
    }

    emit this->clicked(event);
}

int AutoPlotButton::GetStatus() const
{
    return status;
}

void AutoPlotButton::SetStatus(int val)
{
    status = val;
    repaint();
}

void AutoPlotButton::SetColors(QVector<QString> cols)
{
    //Require for vector with colors being size of 4 elements
    //cols[0] - off background, cols[1] - off main, cols[3] - on background, cols[4] - on main
    assert(cols.size() == 4);

    OffBgCol = cols[0], OffCol = cols[1], OnBgCol = cols[2], OnCol = cols[3];
}
