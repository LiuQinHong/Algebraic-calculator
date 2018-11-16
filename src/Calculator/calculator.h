#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QPainter>   //画家类
#include <QPaintEvent>//绘制事件
#include <QImage>     //图片加载器
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_equal_clicked();

    void on_pushButton_del_clicked();

private:
    Ui::Calculator *ui;
    QImage      image;
    QLabel      *nameLabel;
    QLabel      *inputLbael;
    QTextEdit   *displayTextEdit;
    QTextEdit   *inputTextEdit;

};

#endif // CALCULATOR_H
