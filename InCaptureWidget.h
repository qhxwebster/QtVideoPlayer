#ifndef INCAPTUREWIDGET_H
#define INCAPTUREWIDGET_H

#include <QWidget>
#include<QMouseEvent>

//截图对话框底部的控件，安放保存等按钮，为了能直接拖动整个窗口进行了重载
class InCaptureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InCaptureWidget(QWidget *parent = 0);

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
