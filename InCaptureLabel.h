#ifndef INCAPTURELABEL_H
#define INCAPTURELABEL_H

#include <QWidget>
#include<QLabel>
#include<QMouseEvent>


class InCaptureLabel : public QLabel
{
    Q_OBJECT
public:
    explicit InCaptureLabel(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void signalMovePoint(QPoint);
    void signalLeftPressDown();
    void signalDoubleClicked();
public slots:

private:
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;    // 窗口移动拖动时需要记住的点
};

#endif // GROUPBOX_H
