#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setText(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QVector<QString> languages;
};
#endif // WIDGET_H
