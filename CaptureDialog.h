#ifndef CAPTUREDIALOG_H
#define CAPTUREDIALOG_H
#include<InCaptureWidget.h>
#include"InCaptureLabel.h"
#include <QWidget>
#include<QMouseEvent>
#include<QPoint>
#include<QRect>
#include<QPixmap>
#include<QLineEdit>
#include<QLabel>
#include<QSize>
#include<QComboBox>
#include<QGroupBox>
#include<QPushButton>


//截图用的对话框
class CaptureDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureDialog(QWidget *parent = 0);
    ~CaptureDialog();

    void region(const QPoint &cursorGlobalPoint);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void setButton();
    void setPixmap(QPixmap pixmap);
    void setGroupBoxSize(QSize size);
    QRect getNormalRect(){return normalRect; }

private:

    enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
    const int PADDING ;
    const int buttonWidth ;
    const int buttonHeight ;

    QRect normalRect;       //保存最大化以前的大小，因为最小化以前this->rect()已经变成了全屏时的rect()
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;    // 窗口移动拖动时需要记住的点
    Direction dir;                // 窗口大小改变时，记录改变方向
    QPushButton * closeButton;
    QPushButton * minimumButton ;
    QPushButton * maximumButton ;
    QWidget* groupBox;

    int fullScreenWidth;
    int fullScreenHeight;
    int clickCount;
    InCaptureLabel * label;
    QPixmap pixmap;
    InCaptureWidget* bottomWidget;
    QLabel * saveDirLable;
    QLineEdit *lineEdit;
    QPushButton * browseButton;
    QLabel* saveTypeLabel;
    QComboBox * typeComboBox;
    QLabel* saveNameLabel;
    QLineEdit * saveNameLineEdit;
    QPushButton * saveButton;
    QPushButton * saveToClipBoard;

    static QPoint Position;
    QSize videoWidgetSize;
public slots:
  void slotSignalMovePoint(QPoint point);
  void slotBottomWidgetMouseLeftDown();
  void slotSaveBottonClicked();
  void slotSaveToClipBoard();
  void slotBrowseButtonClicked();
};



#endif // WIDGET_H
