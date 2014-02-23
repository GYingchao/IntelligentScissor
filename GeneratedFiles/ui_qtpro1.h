/********************************************************************************
** Form generated from reading UI file 'qtpro1.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPRO1_H
#define UI_QTPRO1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <imagedisplayer.h>

QT_BEGIN_NAMESPACE

class Ui_QtPro1Class
{
public:
    QAction *actionOpen_Image;
    QAction *actionSave_Contour;
    QAction *actionSave_mask;
    QAction *actionExit;
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionUndo;
    QWidget *centralWidget;
    ImageDisplayer *imageWidget;
    ImageDisplayer *test1;
    QLabel *MousePos;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAction;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtPro1Class)
    {
        if (QtPro1Class->objectName().isEmpty())
            QtPro1Class->setObjectName(QString::fromUtf8("QtPro1Class"));
        QtPro1Class->resize(1024, 750);
        actionOpen_Image = new QAction(QtPro1Class);
        actionOpen_Image->setObjectName(QString::fromUtf8("actionOpen_Image"));
        actionSave_Contour = new QAction(QtPro1Class);
        actionSave_Contour->setObjectName(QString::fromUtf8("actionSave_Contour"));
        actionSave_mask = new QAction(QtPro1Class);
        actionSave_mask->setObjectName(QString::fromUtf8("actionSave_mask"));
        actionExit = new QAction(QtPro1Class);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionStart = new QAction(QtPro1Class);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionStop = new QAction(QtPro1Class);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionUndo = new QAction(QtPro1Class);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        centralWidget = new QWidget(QtPro1Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        imageWidget = new ImageDisplayer(centralWidget);
        imageWidget->setObjectName(QString::fromUtf8("imageWidget"));
        imageWidget->setGeometry(QRect(-1, -1, 720, 640));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageWidget->sizePolicy().hasHeightForWidth());
        imageWidget->setSizePolicy(sizePolicy);
        imageWidget->setMouseTracking(true);
        imageWidget->setFocusPolicy(Qt::StrongFocus);
        test1 = new ImageDisplayer(centralWidget);
        test1->setObjectName(QString::fromUtf8("test1"));
        test1->setGeometry(QRect(730, 440, 281, 201));
        MousePos = new QLabel(centralWidget);
        MousePos->setObjectName(QString::fromUtf8("MousePos"));
        MousePos->setGeometry(QRect(0, 650, 121, 31));
        QtPro1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtPro1Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAction = new QMenu(menuBar);
        menuAction->setObjectName(QString::fromUtf8("menuAction"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        QtPro1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtPro1Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtPro1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtPro1Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtPro1Class->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAction->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_Image);
        menuFile->addAction(actionSave_Contour);
        menuFile->addAction(actionSave_mask);
        menuFile->addAction(actionExit);
        menuAction->addAction(actionStart);
        menuAction->addAction(actionStop);
        menuAction->addAction(actionUndo);

        retranslateUi(QtPro1Class);

        QMetaObject::connectSlotsByName(QtPro1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtPro1Class)
    {
        QtPro1Class->setWindowTitle(QApplication::translate("QtPro1Class", "QtPro1", 0, QApplication::UnicodeUTF8));
        actionOpen_Image->setText(QApplication::translate("QtPro1Class", "Open Image..", 0, QApplication::UnicodeUTF8));
        actionSave_Contour->setText(QApplication::translate("QtPro1Class", "Save Contour", 0, QApplication::UnicodeUTF8));
        actionSave_mask->setText(QApplication::translate("QtPro1Class", "Save mask", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("QtPro1Class", "Exit", 0, QApplication::UnicodeUTF8));
        actionStart->setText(QApplication::translate("QtPro1Class", "Start", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("QtPro1Class", "Stop", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("QtPro1Class", "Undo", 0, QApplication::UnicodeUTF8));
        MousePos->setText(QApplication::translate("QtPro1Class", "TextLabel", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("QtPro1Class", "File", 0, QApplication::UnicodeUTF8));
        menuAction->setTitle(QApplication::translate("QtPro1Class", "IScissor", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("QtPro1Class", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtPro1Class: public Ui_QtPro1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPRO1_H
