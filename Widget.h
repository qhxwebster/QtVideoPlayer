#ifndef WIDGET_H
#define WIDGET_H

#include"VideoWidget.h"
#include"MainSlider.h"
#include"BottomWidget.h"
#include"VolumeSlider.h"
#include"ListWidget.h"
#include <QWidget>
#include<QMouseEvent>
#include<QPoint>
#include<QRect>
#include<QGroupBox>
#include<QString>
#include<QMap>
#include<QPushButton>
#include<QModelIndex>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QComboBox>
#include<QLabel>
#include<QSlider>
#include<QEvent>
#include<QTimer>
#include<QObject>
#include<QMouseEvent>
#include<QMenu>
#include<QVector>
#include<QPair>
#include<QMultiMap>
#include<QListWidget>
#include<QAction>
#include<QSqlTableModel>
#include<QMediaPlaylist>
namespace Ui {
class Widget;
}

//界面的主窗口
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);
    bool eventFilter(QObject* target, QEvent * event);

    void setThreeButton();    //初始化右上角三个按钮

    int getWindowIniWidth() const {return windowIniWidth;}
    int getWindowIniHeight()const {return windowIniHeight; }
    void region(const QPoint &cursorGlobalPoint);       //按照九宫格的思想判断鼠标现在的位置
    QString getNameFromPath(const QString &fileName);   //从路径中获取文件名
    QString digitalToTime(const int& number);                      //把时间转换为标准格式
    QString removeIndexFromAppend( QString name);        //移除append序号
    void iniDatabase();                              //从数据库读数据到窗体
    void updateToDataBase();                  //根据vector更新数据库
    void addFile(const QString fileName);   //根据路径名添加文件
private:
    Ui::Widget *ui;

    enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };  //九宫格方向
    const int PADDING ;               //用于边缘判断
    const int windowIniWidth;    //窗口初始化的宽度
    const int windowIniHeight;   //窗口初始化的高度
    static QPoint Position;           //通过bottomWidget或者videoWidget移动窗体时，记录窗体移动前的位置

    //窗体
    QRect normalRect;        //保存最大化以前的大小，因为最小化以前this->rect()已经变成了全屏时的rect()
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;    // 窗口移动拖动时需要记住的点
    Direction dir;                 // 窗口大小改变时，记录改变方向
    QPushButton * closeButton;            //关闭按钮
    QPushButton * minimumButton ;   //最小化按钮
    QPushButton * maximumButton ;  //最大化按钮
    QWidget  * groupBox;                     //将videoWidget放在此上面
    BottomWidget  * bottomWidget;  //底部控件，用于放下一曲上一曲等
    ListWidget * listWidget;                 //显示列表控件

    //用来保存文件目录 文件名
    QVector<QPair<QPair<QString, QString>, QString > > vector;   //name  fileName  nameAppendIndex

    const int screenWidth;       //屏幕的宽度
    const int screenHeight;      //屏幕的高度
    int clickCount;                     //用来最大化按钮点击判断

    QLabel *  titleLabel;                               //标题栏
    bool volumeWidgetEntered;                 //声音控件进入的标志
    bool playModeWidgetEntered;            //播放模式控件进入的标志
    bool inBottomRegion;                           //底部区域进入的标志，若为真，底部控件显示
    bool inRightRegion;                              //右侧区域进入的标志，若为真，隐藏按钮显示
    QListWidget* playModeListWidget;    //播放模式控件
    QPoint mouseGlobalPos;                      //鼠标全局坐标
    QPushButton * hideButton;                  //播放列表的隐藏按钮

    int playingIndex;           //当前正在播放视频的序号(从0开始)
    enum PlayingMode{CurrentItemOnce,CurrentItemInLoop, Sequential, Loop,Random};   //播放模式
    PlayingMode playingMode;   //播放模式

    //菜单
    QPushButton * menuButton;
    QMenu* menu;
    QAction * openAction;

    //播放器控件
    QMediaPlayer  *  mediaPlayer0;     //播放者
    VideoWidget *  videoWidget0;       //显示视频
    QLabel *mainLabel;    //用于视频暂停时显示画面，从而 避免移动时黑屏

    QPushButton    *  openButton;
    QPushButton    *  stopButton;
    QPushButton    *  lastVideoButton;
    QPushButton    *  nextVideoButton;
    QPushButton    *  playButton;
    QPushButton    *  playModeButton;
    QPushButton    *  volumeButton;
    QWidget * volumeWidget;
    VolumeSlider * volumeSlider;
    MainSlider * slider;
    QLabel  * totalTimeLabel;
    QLabel  * presentTimeLabel;


signals:
    void signalInRegion();
    void signalOutRegion();

public slots:
   void slotSetButton();
   void slotOpenFile();
   void slotSetValue(int value);
   void slotStateChanged(QMediaPlayer::State);
   void slotDurationChanged(qint64);
   void slotPositionChanged(qint64);
   void slotPlayOrPause();
   void slotNextVideo();
   void slotLastVideo();
   void slotStopVideo();
   void slotVolumeTimer();
   void slotPlayModeTimer();
   void slotPlayModeListWidget();
   void slotInBottomRegion();
   void slotOutBottomRegion();
   void slotOutBottomRegionTimer();
   void slotSignalPressPosition(qint64 position);
   void slotPressVolumePosition(qint64 position);
   void slotListWidgetItemDoubleClick(QString name);
   void slotListWidgetItemDeleted(int n);
   void slotSignalMovePoint(QPoint );
   void slotVideoWidgetMouseLeftDown();
   void slotHandleError();
   void slotVideoWidgetDoubleClicked();
   void slotListWidgetClearAll();
   void slotListWidgetActionOpen();
   void slotHideButton();
   void slotInRightRegion();
   void slotOutRightRegion();
   void slotOutRightRegionTimer();
   void slotCloseWidget();
   void slotVideoWidgetDropedList(QList<QUrl>urls);
   void slotListWidgetClearValidItem();
   void slotListWidgetOpenDirectory(int n);
   void slotVideoWidgetActionInfo();
   void slotVideoWidgetActionCapture();
   void slotBottomWidgetDoubleClicked();
};



#endif // WIDGET_H
