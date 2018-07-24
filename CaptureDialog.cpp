#include "CaptureDialog.h"
#include"inCaptureWidget.h"
#include "FileSystemDialog.h"
#include<QDir>
#include<QString>
#include<QApplication>
#include<QCursor>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QAbstractItemView>
#include<QClipboard>
#include<QDebug>
#include<QDialog>
#include<QSpacerItem>
#include<QTreeView>
#include<QPushButton>
#include<QGroupBox>
#include<QApplication>
#include<QStandardPaths>
#include<QDesktopWidget>
#include<QFileSystemModel>

QPoint CaptureDialog::Position(QPoint(0,0));


CaptureDialog::CaptureDialog(QWidget *parent) :
    QWidget(parent), PADDING(2), buttonHeight(20),buttonWidth(20),  clickCount(1),isLeftPressDown(false),
    dir(NONE)
{

    this->setAutoFillBackground(true);
    this->setStyleSheet("QWidget{background-color:rgb(229,229,229)}");
    setWindowOpacity(1);//设置透明度
    this->setMinimumHeight(400);
    this->setMinimumWidth(600);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint); // 设置成无边框对话框
    this->setMouseTracking(true);
    this->setCursor(QCursor(Qt::ArrowCursor));

}

CaptureDialog::~CaptureDialog()
{

}

 void CaptureDialog::setGroupBoxSize(QSize size)
 {
     videoWidgetSize = size;
     normalRect.setHeight(size.height()*23/30+70);
     normalRect.setWidth(size.width()*23/30);


     groupBox = new QGroupBox(this);

     groupBox->setGeometry(1, 1, normalRect.width()-2,   normalRect.height()-76);
     groupBox->setStyleSheet("QGroupBox{ border-top-left-radius:0px;  border-top-right-radius:0px;  background-color:rgb(54,54,54)}");
     label = new InCaptureLabel(groupBox);
     connect(label, SIGNAL(signalMovePoint(QPoint)), this, SLOT(slotSignalMovePoint(QPoint)));
     connect(label, SIGNAL(signalLeftPressDown()), this, SLOT(slotBottomWidgetMouseLeftDown()));
     label->setCursor(QCursor(Qt::ArrowCursor));
     label->setGeometry(0,0,groupBox->size().width(), groupBox->size().height());
     label->setStyleSheet("QLabel{background-color:rgb(0,0,0)}");

     bottomWidget = new InCaptureWidget(this);
     bottomWidget->setGeometry(1,normalRect.height()-75, normalRect.width()-2, 74);

     connect(bottomWidget, SIGNAL(signalMovePoint(QPoint)), this, SLOT(slotSignalMovePoint(QPoint)));
     connect(bottomWidget, SIGNAL(signalLeftPressDown()), this, SLOT(slotBottomWidgetMouseLeftDown()));

     saveDirLable = new QLabel(bottomWidget);
     saveDirLable->setText("保存目录");
     saveDirLable->setGeometry(50,10,60,20);
     saveDirLable->setStyleSheet("QLabel{color:rgb(25,25,25); border:none; padding-left:2px; padding-right:2px;  background-color:rgb(229,229,229)}"
                                                      );

     lineEdit = new QLineEdit(bottomWidget);
     lineEdit->setStyleSheet("QLineEdit{color:rgb(25,25,25); background-color:rgb(229,229,229); border: 2px solid grey; border-radius:3px;"
                                              "QLineEdit:hover{background-color:rgb(255,255,255); }");
     lineEdit->setText(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
     lineEdit->setGeometry(120, 10, 150, 20);


     browseButton = new QPushButton(bottomWidget);
     browseButton->setText("浏览");
     browseButton->setStyleSheet("QPushButton{border:none; color:rgb(25,25,25); background-color:rgb(249,249,249)}"
                                                        "QPushButton::hover{border:2px; border-color:rgb(0,0,0); background-color:rgb(255, 255, 255)}");
     browseButton->setGeometry(280, 10, 50, 20);
     connect(browseButton,&QPushButton::clicked, this , &CaptureDialog::slotBrowseButtonClicked);

     saveTypeLabel = new QLabel(bottomWidget);
     saveTypeLabel->setText("保存类型");
     saveTypeLabel->setStyleSheet("QLabel{color:rgb(25,25,25); border:none; padding-left:2px; padding-right:2px;  background-color:rgb(229,229,229)}"
                                                      );
     saveTypeLabel->setGeometry(360, 10, 60, 20);

     typeComboBox = new QComboBox(bottomWidget);
     typeComboBox->addItem("jpg");
     typeComboBox->addItem("png");
     typeComboBox->setGeometry(430, 10, 70, 20);
     typeComboBox->setStyleSheet("QComboBox{background-color:rgb(255,255,255); border: 1px solid gray;border-radius: 3px;  padding: 1px 2px 1px 2px; }"
                                                           "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right; width: 20px;"
                                                                                                       "border-left-width: 0px; image:url(dropDown.jpg);"
                                                                                                       "border-top-right-radius: 3px; border-bottom-right-radius: 3px; }"
                                 "QComboBox QAbstractItemView::item{background-color:rgb(200,200,200); height:30px; }");

     saveNameLabel =new QLabel(bottomWidget);
     saveNameLabel->setText("保存名称");
     saveNameLabel->setGeometry(50, 45, 60, 20);
     saveNameLabel->setStyleSheet("QLabel{color:rgb(25,25,25); border:none; padding-left:2px; padding-right:2px;  background-color:rgb(229,229,229)}"
                                                      );

     saveNameLineEdit = new QLineEdit(bottomWidget);
     saveNameLineEdit->setStyleSheet("QLineEdit{color:rgb(25,25,25)}  QLineEdit::hover{background-color:rgb(255,255,255)}");
     saveNameLineEdit->setText("picture");
     saveNameLineEdit->setGeometry(120, 45, 100, 20);

     saveButton  =new QPushButton(bottomWidget);
     saveButton->setText("保存截图");
     saveButton->setStyleSheet("QPushButton{border:none; color:rgb(25,25,25); background-color:rgb(249,249,249)}"
                                                    "QPushButton::hover{border:2px; border-color:rgb(0,0,0); background-color:rgb(255, 255, 255)}");
     saveButton->setGeometry(bottomWidget->width()-220, 45, 60, 20);
     connect(saveButton, &QPushButton::clicked, this, &CaptureDialog::slotSaveBottonClicked);

     saveToClipBoard = new QPushButton(bottomWidget);
     saveToClipBoard->setText("保存至剪切板");
     saveToClipBoard->setStyleSheet("QPushButton{border:none; color:rgb(25,25,25); background-color:rgb(249,249,249)}"
                                                    "QPushButton::hover{border:2px; border-color:rgb(0,0,0); background-color:rgb(255, 255, 255)}");
     saveToClipBoard->setGeometry(bottomWidget->width()-140, 45, 100, 20);
     connect(saveToClipBoard, &QPushButton::clicked, this, &CaptureDialog::slotSaveToClipBoard);
     setButton();


 }

 void CaptureDialog::slotBrowseButtonClicked()
 {
     FileSystemDialog * dialog = new FileSystemDialog;
     connect(dialog, &FileSystemDialog::signalPathSelected, [this](QString filePath){ lineEdit->setText(filePath); });
     dialog->exec();
 }


 void CaptureDialog::slotBottomWidgetMouseLeftDown()
 {
         Position=this->pos();
 }

 //保存至剪切板
void CaptureDialog::slotSaveToClipBoard()
{
    qDebug()<<"slotSaveToClipBoard";
    QClipboard * clipBoard =  QApplication::clipboard();
    clipBoard->setPixmap(pixmap);

}

//使用videoWidget0移动窗体
 void CaptureDialog::slotSignalMovePoint(QPoint point)
 {
         this->move(point+Position);
 }

void CaptureDialog::region(const QPoint &cursorGlobalPoint)
{

    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y())
    {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void CaptureDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

void CaptureDialog::mousePressEvent(QMouseEvent *event)
{
    switch(event->button()) {
    case Qt::LeftButton:
        isLeftPressDown = true;
        if(dir != NONE)
        {
            this->mouseGrabber();
        }
        else
        {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        break;
    case Qt::RightButton:
        this->close();
        break;
    default:
       // QMouseEvent::mousePressEvent(event);
        break;
    }
}

void CaptureDialog::setPixmap(QPixmap pixmap)
{
    this->pixmap = pixmap;
    pixmap = pixmap.scaled(label->size());
    label->setPixmap(pixmap);

}

void CaptureDialog::mouseMoveEvent(QMouseEvent *event)
{

    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown)
    {
        this->region(gloPoint);
    }
    else
    {
        if(dir != NONE) {
            QRect rMove(tl, rb);

            switch(dir) {
            case LEFT:
              if(rb.x() - gloPoint.x() <= this->minimumWidth())
                   rMove.setX(tl.x());
              else
                  rMove.setX(gloPoint.x());
             //   rMove.setWidth(rb.x()-gloPoint.x());    //以右边界为标准变化， 左边不变，所以不能用
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());

                break;
            case UP:
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());

                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());                   //以上边界为标准变化， 左边不变，所以不能用
                break;
            case LEFTTOP:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
               rMove.setWidth(gloPoint.x() - tl.x());
               if(rb.y() - gloPoint.y() <= this->minimumHeight())
                   rMove.setY(tl.y());
               else
               rMove.setY(gloPoint.y());    //May change the height, but will never change the bottom edge of the rectangle.

                break;
            case LEFTBOTTOM:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                     rMove.setX(tl.x());
                else
                     rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());

                break;
            default:
                break;
            }
            this->setGeometry(rMove);
            qDebug()<<"size "<<this->size();
        }
        else
        {
            move(event->globalPos()-dragPosition );
        }
        int a=this->rect().topRight().x();
        normalRect = this->rect();

        groupBox->setGeometry(1, 1, normalRect.width()-2, normalRect.height()-76);    //设置主窗口
        label->setGeometry(0,0,groupBox->size().width(), groupBox->size().height());
        label->setPixmap(this->pixmap.scaled(label->width(), label->height()));

        bottomWidget->setGeometry(1,normalRect.height()-75, normalRect.width()-2, 74);
        saveButton->setGeometry(bottomWidget->width()-220, 45, 60, 20);
        saveToClipBoard->setGeometry(bottomWidget->width()-140, 45, 100, 20);
        closeButton->setGeometry(a-34, 10, 28, 20);     //将关闭按钮放在最右上角
        minimumButton->setGeometry(a-68,10, 28, 20);
    }

}

void CaptureDialog::setButton()
{
    //设置三个按钮
    closeButton=new QPushButton(this);
    minimumButton = new QPushButton(this);
    closeButton->setFixedSize(30,20);
    minimumButton->setFixedSize(30,20);

    int a = normalRect.width();
    closeButton->setGeometry(a-40, 10, 20, 20);     //将关闭按钮放在最右上角
    closeButton->setCursor(QCursor(Qt::ArrowCursor));
    minimumButton->setGeometry(a-74,10, 20, 20);
    minimumButton->setCursor(QCursor(Qt::ArrowCursor));

    QString name = QDir::currentPath();
    QPixmap closeIcon((name+"/close.png"));
    closeButton->setIcon(closeIcon);
    QPixmap minimumIcon((name + "/minimize.png"));
    minimumButton->setIcon(minimumIcon);
    closeButton->setStyleSheet("QPushButton{border-radius:8px; background-color:rgb(0,0,0);image:url(:/close.png);}"
                                                  "QPushButton::hover{background-color:rgb(54,54,54);image:url(:/close.png);}");
    minimumButton->setStyleSheet("QPushButton{image:url(:/minimize.png); border-radius:8px; background-color:rgb(0,0,0);}"
                                                         "QPushButton:hover{image:url(minimizeHovered.png); background-color:rgb(54,54,54);image:url(:/minimize.png);}");
    closeButton->setToolTip("关闭");
    minimumButton->setToolTip("最小化");

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(minimumButton, SIGNAL(clicked()), this, SLOT(showMinimized()) );

}

void CaptureDialog::slotSaveBottonClicked()
{
    QString fileName  =  lineEdit->text().append("/").append(saveNameLineEdit->text().append(".").append(typeComboBox->currentText()));
    //qDebug()<<fileName;
    this->pixmap.save(fileName);
}
