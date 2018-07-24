#include "FileSystemDialog.h"
#include "FileTreeView.h"
#include<QPushButton>
#include<QDialog>
#include<QFileSystemModel>
#include<QTreeView>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QModelIndex>
#include<QMouseEvent>
#include<QPoint>
#include<QDebug>

FileSystemDialog::FileSystemDialog()
{

    this->setModal(true);
    this->setWindowTitle("浏览文件夹");

    treeView =new FileTreeView;

    treeView->setColumnHidden(1,true);
    treeView->setColumnHidden(2,true);
    treeView->setColumnHidden(3,true);

    QPushButton * okButton = new QPushButton("确定");
    okButton->setFixedSize(70,26);
    connect(okButton, &QPushButton::clicked, [this](){emit signalPathSelected(path); this->close(); });

    QPushButton * cancelButton = new QPushButton("取消");
    cancelButton->setFixedSize(70,26);
    connect(cancelButton, &QPushButton::clicked, this, &FileSystemDialog::close);

    QHBoxLayout * hBoxLayout= new QHBoxLayout;
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(okButton);
    hBoxLayout->addWidget(cancelButton);

    QVBoxLayout *vBoxLayout  = new QVBoxLayout;
    vBoxLayout->addWidget(treeView);
    vBoxLayout->addLayout(hBoxLayout);
    this->setLayout(vBoxLayout);
    connect(treeView, &FileTreeView::signalFilePathSelected, [this](QString filePath){this->path = filePath; });
}

