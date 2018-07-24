#include "BottomWidget.h"
#include<QDebug>
#include<QEvent>
BottomWidget::BottomWidget(QWidget *parent) : QWidget(parent)
{

}

void BottomWidget::enterEvent(QEvent *event)
{

}
void BottomWidget::leaveEvent(QEvent *event)
{

}

void BottomWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint topLeftPoint (0, this->height()-140);
    QPoint rightBottomPoint(this->width(), this->height());
    topLeftPoint  = this->mapToGlobal(topLeftPoint);
    rightBottomPoint = this->mapToGlobal(rightBottomPoint);
    QPoint mouseGlobalPoint = this->mapToGlobal(event->pos());

    if(isLeftPressDown)  //
    {
         emit signalMovePoint(event->globalPos()-dragPosition);
    }
}

void BottomWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        this->releaseMouse();

    }
}

void BottomWidget::mousePressEvent(QMouseEvent *event)
{

    switch(event->button()) {
    case Qt::LeftButton:
    {
        isLeftPressDown = true;
        emit signalLeftPressDown();
        dragPosition = event->globalPos();
        break;
    }
    case Qt::RightButton:
        break;
    default:
        break;
    }
}

void BottomWidget::mouseDoubleClickEvent(QMouseEvent* event)
{

    if(event->button() == Qt::LeftButton)
    {
        qDebug()<<"emit signalDoubleClicked";
        emit signalDoubleClicked();
    }

}
