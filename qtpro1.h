#ifndef QTPRO1_H
#define QTPRO1_H

#include <QtGui/QMainWindow>
#include <QtGui/qfiledialog.h>
#include "ui_qtpro1.h"
#include "imageDisplayer.h"


class QtPro1 : public QMainWindow
{
	Q_OBJECT

public:
	QtPro1(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QtPro1();

public slots:
	void on_actionOpen_Image_triggered();
private:
	Ui::QtPro1Class ui;
};

#endif // QTPRO1_H
