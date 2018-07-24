#include "InCaptureLabel.h"


#include<QDebug>

InCaptureLabel::InCaptureLabel(QWidget *parent) : QLabel(parent)
{

    this->setCursor(QCursor(Qt::ArrowCursor));
}


void InCaptureLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftPressDown)  //
    {
         emit signalMovePoint(event->globalPos()-dragPosition);
    }
}

void InCaptureLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        this->releaseMouse();

    }
}

void InCaptureLabel::mousePressEvent(QMouseEvent *event)
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

