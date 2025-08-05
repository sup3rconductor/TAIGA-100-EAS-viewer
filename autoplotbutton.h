
#ifndef AUTOPLOTBUTTON_H
#define AUTOPLOTBUTTON_H

#include <QVector>
#include <QWidget>


class AutoPlotButton : public QWidget
{
    Q_OBJECT
public:
    explicit AutoPlotButton(QWidget *parent = nullptr);
    AutoPlotButton();
    int GetStatus() const;
    void SetStatus(int val);
    void SetColors(QVector<QString> cols);
    QVector<QString> GetColors();

    QString OffBgCol = "#4b4b4b", OnBgCol = "#519fc7", OffCol = "#519fc7", OnCol = "#ffffff";

    static const int off = 0;
    static const int on = 1;

protected:
    virtual void paintEvent(QPaintEvent *ev);
    virtual QSize sizeHint() const;
    virtual void mousePressEvent(QMouseEvent* event);

private:
    int status = 0;

signals:
    void clicked(QMouseEvent *event);

};

#endif // AUTOPLOTBUTTON_H
