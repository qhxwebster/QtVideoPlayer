#ifndef FILETREEVIEW_H
#define FILETREEVIEW_H

#include<QWidget>
#include<QTreeView>
#include<QString>
#include<QMouseEvent>
#include<QFileSystemModel>

//获得系统文件目录
class FileTreeView : public QTreeView
{
    Q_OBJECT
public:
    FileTreeView();
    void mousePressEvent(QMouseEvent *event);
private:
    QFileSystemModel *model;
signals:
    void signalFilePathSelected(QString string);
};

#endif // FILETREEVIEW_H
